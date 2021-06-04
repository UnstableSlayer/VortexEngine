#type vertex
#version 410 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1

uniform mat4 u_viewProj;
uniform mat4 u_Transform;

out vec4 vertexColor;

void main()
{
    gl_Position = u_viewProj * u_Transform * vec4(aPos, 1.0);
    vertexColor = aColor;
}

#type fragment
#version 410 core
out vec4 FragColor;
in vec4 vertexColor;
  
void main()
{
    gl_FragColor = vertexColor + 0.2;
}