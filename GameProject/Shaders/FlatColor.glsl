#type vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uViewProj;
uniform mat4 uTransform;

out vec2 vTexCoord;

void main()
{
    vTexCoord = aTexCoord;
    gl_Position = uViewProj * uTransform * vec4(aPos, 1.0);
}

#type fragment
#version 410 core
layout(location = 0) out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec2 uTextureScale;
uniform vec4 uTextureColor;
  
void main()
{
    gl_FragColor = texture(uTexture, vTexCoord * uTextureScale) * uTextureColor;
}