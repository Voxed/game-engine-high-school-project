uniform sampler2D tex;
varying vec2 texCoords;

void main()
{
  gl_FragColor = texture2D(tex, texCoords);
}