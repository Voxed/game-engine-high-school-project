#version 130

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
in vec3 vertexPos;
in vec2 textureCoords;
in vec4 colorModification;
out vec2 texCoords;
out vec4 colorMod;

void main()
{
    colorMod = colorModification;
    texCoords = textureCoords;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPos, 1.0);
}