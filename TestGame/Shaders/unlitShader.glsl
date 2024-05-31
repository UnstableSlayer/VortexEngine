#type vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 uViewProj;
uniform mat4 uTransformMatrix;
void main()
{
    vTexCoord = aTexCoord;
    gl_Position = uViewProj * uTransformMatrix * vec4(aPos, 1.0);
}

#type fragment
#version 410 core
layout(location = 0) out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
    FragColor = vec4(vTexCoord, 0.f, 0.5f) + texture(uTexture, vTexCoord * 2.f);
}
