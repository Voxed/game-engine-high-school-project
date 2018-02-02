#version 130

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
in vec3 vertexPos;
in vec2 textureCoords;
out vec2 texCoords;

void main()
{
    gl_FrontColor = gl_Color;
    texCoords = textureCoords;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPos, 1.0);
}