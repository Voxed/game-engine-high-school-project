uniform mat4 projectionMatrix;
attribute vec2 vertexPos;
attribute vec2 textureCoords;
varying vec2 texCoords;

void main()
{
    texCoords = textureCoords;
    gl_Position = projectionMatrix * vec4(vertexPos, 0.0, 1.0);
}