#version 130

uniform sampler2D tex;
uniform sampler2D lightMap;
in vec2 texCoords;

void main()
{
    vec4 color = texture2D(tex, texCoords);
    vec4 lightColor = texture2D(lightMap, texCoords);
        int performance = 3;
        int size = 30;
        size = size/performance;
        vec4 finalColor = vec4(0,0,0,0);
        int amount = 0;
        int alpha_amount = amount;
        for(int x = -size/2; x <= size/2; x++)
        {
            for(int y = -size/2; y <= size/2; y++)
            { 
                if(y != 0 && x != 0)
                {
                    vec4 c = texture2D(lightMap, texCoords + vec2(1.0f/150.0f*performance*float(x), 1.0f/150.0f*performance*float(y)));
                    if(c.a != 0)
                    {
                        finalColor += c*2;
                        alpha_amount += 1;
                    }
                    amount += 1;
                }
            }
        }
        if(finalColor.a > 0)
        {
            if(color.a > 0)
            {
                gl_FragColor = vec4(0,0,0,color.a) +color*vec4(finalColor.r/alpha_amount, finalColor.g/alpha_amount, finalColor.b/alpha_amount,finalColor.a/amount);
            }
            else
            {
                gl_FragColor = finalColor/(amount)/1.5;
            }


        }
        else
        {
            discard;
        }
}