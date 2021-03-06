#version 330

in vec4 vColor;

out vec4 outColor;

uniform vec3 uAmbientLight;

void main() {
    vec3 ambient = uAmbientLight;
    outColor = vec4(ambient, 1.0);
}