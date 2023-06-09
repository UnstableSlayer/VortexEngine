#type vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aTexTiling;
layout (location = 4) in float aTexIndex;

uniform mat4 uViewProj;

out vec4 vColor;
out vec2 vTexCoord;
out vec2 vTexTiling;
out float vTexIndex;

void main()
{
    vColor = aColor;
    vTexCoord = aTexCoord;
    vTexTiling = aTexTiling;
    vTexIndex = aTexIndex;

    gl_Position = uViewProj * vec4(aPos, 1.0);
}

#type fragment
#version 410 core
layout(location = 0) out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;
in vec2 vTexTiling;
in float vTexIndex;

uniform sampler2D uTextures[32];

//uniform bool horizontal = false;
//uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
  
void main()
{
    /*vec2 tex_offset = 1.0 / textureSize(uTextures[int(vTexIndex)], 0); // gets size of single texel
    vec3 result = texture(uTextures[int(vTexIndex)], vTexCoord).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(uTextures[int(vTexIndex)], vTexCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(uTextures[int(vTexIndex)], vTexCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(uTextures[int(vTexIndex)], vTexCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(uTextures[int(vTexIndex)], vTexCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }*/

    vec4 fragColor = texture(uTextures[int(vTexIndex)], vTexCoord * vTexTiling) * vColor;
    //vec4 fragColor = vec4(result, 1.0) * vColor;


    if(fragColor.a < 0.001)
        discard;

    FragColor = fragColor;
}
