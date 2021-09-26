#type vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uViewProj;
out vec4 vColor;
void main()
{
    vColor = vec4(aPos, 1.0);
    gl_Position = uViewProj * vec4(aPos, 1.0);
}

#type fragment
#version 410 core
layout(location = 0) out vec4 FragColor;

in vec4 vColor;

void main()
{
    gl_FragColor = vColor;
}