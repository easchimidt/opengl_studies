#version 330

uniform vec3 uAmbientLight;

void main() {
    vec3 ambient = uAmbientLight;
    outColor = vec4(ambient, 1.0);
}