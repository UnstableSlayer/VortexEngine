#type vertex
#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_viewProj;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_viewProj * u_Transform * vec4(aPos, 1.0);
}

#type fragment
#version 410 core
layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;
 
uniform sampler2D u_Texture;

void main()
{
    gl_FragColor = texture(u_Texture, v_TexCoord);
}