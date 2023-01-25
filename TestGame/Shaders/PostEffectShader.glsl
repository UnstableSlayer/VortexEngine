#type vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

void main()
{
    vTexCoord = aTexCoord;

    gl_Position = vec4(aPos, 1.0);
}

#type fragment
#version 410 core
layout(location = 0) out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, vTexCoord);
}
