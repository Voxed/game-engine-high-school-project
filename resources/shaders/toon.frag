#version 130

uniform sampler2D tex;
in vec2 texCoords;

void main()
{
    vec4 color = texture2D(tex, texCoords);
    if( color.a == 0.0 )
    {
        int performance = 2;
        int size = 20;
        size = size/performance;
        float a = 0;
        for(int x = -size/2; x <= size/2; x++)
        {
            for(int y = -size/2; y <= size/2; y++)
            { 
                if(y != 0 && x != 0)
                {
                    vec4 color = texture2D(tex, texCoords + vec2(1.0f/720.0f*performance*float(x), 1.0f/480.0f*performance*float(y)));
                    a += color.a;
                }
            }
        }
        if(a != 0)
        {
            gl_FragColor = vec4(1.0,1.0,1.0,1.0);
        }
        else
        {
            discard;
        }
    }
    else
    {
            gl_FragColor = color;
    }
}