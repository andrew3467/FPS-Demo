#type vertex
#version 460

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 uTransform;
uniform mat4 uViewProj;


out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;

void main() {
    vTexCoord = aTexCoord;
    vNormal = aNormal;
    vFragPos = vec3(uTransform * vec4(aPosition, 1.0));

    gl_Position =  uViewProj * uTransform * vec4(aPosition, 1.0);
}


#type fragment
#version 460

layout (location = 0) out vec4 FragColor;

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;


struct PointLight {
    vec3 Position;
    vec3 Ambient;
};

uniform vec4 uColor;
uniform sampler2D uTexture;


uniform vec3 viewPos;

uniform PointLight uLight;


void main() {
    float ambient = 0.2f;

    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(uLight.Position - viewPos);

    float diffuse = max(dot(normal, lightDir), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAMT = pow(max(dot(viewDir, reflectionDir), 0.0f), 32);
    float specular = specularLight * specAMT;

    FragColor = texture(uTexture, vTexCoord) * vec4(uLight.Ambient, 1.0) * (specular + diffuse + ambient);
}
