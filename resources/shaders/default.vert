#version 130

uniform mat4 projectionMatrix;
in vec3 vertexPos;
in vec2 textureCoords;
out vec2 texCoords;

void main()
{
    texCoords = textureCoords;
    gl_Position = projectionMatrix * vec4(vertexPos, 1.0);
}