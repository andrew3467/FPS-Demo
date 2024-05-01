#type vertex
#version 460

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 uTransform;
uniform mat4 uViewProj;

out vec2 vTexCoord;

void main() {
    vTexCoord = aTexCoord;
    gl_Position =  uViewProj * uTransform * vec4(aPosition, 1.0);
}


#type fragment
#version 460

layout (location = 0) out vec4 FragColor;

uniform vec4 uColor;

uniform sampler2D uTexture;

in vec2 vTexCoord;


void main() {
    FragColor = texture(uTexture, vTexCoord) * uColor;
}
