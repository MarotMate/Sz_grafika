#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>   // IDE be kell tenni az assimp scene fejléceket

#include "shader.h"

// Assimp típusok forward deklarációja (nem kötelező, de szokás)
// Ezeket megadhatod, de mivel include-oltuk a scene.h-t, nem szükséges
/*
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
*/

// Vertex és Texture struct-ok
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

class Model
{
public:
    Model(const std::string &path);
    void Draw(Shader &shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);

    // Használd az Assimp típusokat, ne void pointert
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#endif