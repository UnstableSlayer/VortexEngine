#type vertex
#version 410 core
#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aTexTiling;
layout (bindless_sampler, location = 4) in sampler2D aTexHandle;

uniform mat4 uViewProj;

out vec4 vColor;
out vec2 vTexCoord;
out vec2 vTexTiling;
layout (bindless_sampler) out sampler2D vTexHandle;

void main()
{
    vColor = aColor;
    vTexCoord = aTexCoord;
    vTexTiling = aTexTiling;
    vTexHandle = aTexHandle;

    gl_Position = uViewProj * vec4(aPos, 1.0);
}

#type fragment
#version 410 core
#extension GL_ARB_bindless_texture : require

layout(location = 0) out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;
in vec2 vTexTiling;
layout (bindless_sampler) in sampler2D vTexHandle;
  
void main()
{
    vec4 fragColor = texture(vTexHandle, vTexCoord * vTexTiling) * vColor + vec4(0.4, 0.4, 0.0, 1.0);
    
    if(fragColor.a < 0.001)
        discard;

    gl_FragColor = fragColor;
}