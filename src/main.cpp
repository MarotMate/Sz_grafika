
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// callback-ek és input kezelés deklarációk
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height);
void mouse_callback(GLFWwindow* /*window*/, double xpos, double ypos);
void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Interaktiv Szobor Kiallitás", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // egér kurzor elfogása
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    unsigned int myTexture = loadTexture("assets/textures/marble.jpg");

    glEnable(GL_DEPTH_TEST);

    Model ourModel("assets/sculpture.obj");

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Kamera és projekció beállítása
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // --- Világítás beállítása ---

        // Statikus fény komponensek
        shader.setVec3("objectLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        shader.setVec3("objectLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3("objectLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setFloat("objectLight.constant", 1.0f);
        shader.setFloat("objectLight.linear", 0.09f);
        shader.setFloat("objectLight.quadratic", 0.032f);

        // Mozgó fény pozíciója
        float radius = 3.0f;
        float x = sin(currentFrame) * radius;
        float z = cos(currentFrame) * radius;
        shader.setVec3("objectLight.position", glm::vec3(x, 2.0f, z));

        // Kamera pozíció átadása a shadernek
        shader.setVec3("viewPos", camera.Position);

        // Modell forgatása
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, currentFrame * glm::radians(20.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", model);

        // Modell kirajzolása
        ourModel.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* /*window*/, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
    camera.ProcessMouseScroll((float)yoffset);
}
