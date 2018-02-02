#version 130

uniform sampler2D tex;
in vec2 texCoords;
in vec4 colorMod;

void main()
{
  vec4 color = texture2D(tex, texCoords)*colorMod;
  if( color.a == 0.0 )
    discard;
  gl_FragColor = color;
}