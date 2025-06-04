#version 330 core

layout(location = 0) in vec3 aPos;       // pozíció
layout(location = 1) in vec3 aNormal;    // normál
layout(location = 2) in vec2 aTexCoords; // textúra koordináták

out vec3 FragPos;       // frag pozíció világ koordinátában (a fragment shadernek)
out vec3 Normal;        // normál világ koordinátában
out vec2 TexCoords;     // továbbítjuk a textúra koordinátákat

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}