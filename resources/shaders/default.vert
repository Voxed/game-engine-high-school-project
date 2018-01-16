uniform mat4 projectionMatrix;
attribute vec3 vertexPos;
attribute vec2 textureCoords;
varying vec2 texCoords;

void main()
{
    texCoords = textureCoords;
    gl_Position = projectionMatrix * vec4(vertexPos, 1.0);
}