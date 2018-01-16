uniform sampler2D tex;
varying vec2 texCoords;

void main()
{
  vec4 color = texture2D(tex, texCoords);
  if( color.a == 0.0 )
    discard;
  gl_FragColor = color;
}