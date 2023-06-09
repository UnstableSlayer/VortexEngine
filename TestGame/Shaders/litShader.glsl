#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 vPos;
out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 uViewProj;
uniform mat4 uTransformMatrix;
void main()
{
    vPos = aPos;
    vNormal = aNormal;
    vTexCoord = aTexCoord;
    gl_Position = uViewProj * uTransformMatrix * vec4(aPos, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;

uniform sampler2D uTexture;

vec3 LightPos = vec3(0, 100, 0);

vec4 CalculateLighting(vec3 normal, vec3 pos, vec3 lightPos)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - pos);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * vec4(0.8, 0.8, 1.0, 0.0);
    vec4 ambiance = vec4(0.04, 0.04, 0.08, 1.0);

    return diffuse + ambiance;
}

void main()
{
    FragColor = texture(uTexture, vTexCoord);// * CalculateLighting(vNormal, vPos, LightPos);
}
