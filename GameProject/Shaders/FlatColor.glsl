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
  
void main()
{
    if(vColor.a < 0.1)
        discard;
    gl_FragColor = texture(uTextures[int(vTexIndex)], vTexCoord * vTexTiling) * vColor;
}