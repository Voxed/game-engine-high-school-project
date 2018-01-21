#version 130

uniform sampler2D tex;
in vec2 texCoords;

void main()
{
  vec4 color = texture2D(tex, texCoords);
  if( color.a == 0.0 )
    discard;
  gl_FragColor = color;
}