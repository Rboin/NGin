#version 430 core

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

uniform float power;

out vec4 color;

in vec2 tex_cor;

in vec3 N;
in vec3 L;
in vec3 V;

void main() {

    vec3 R = reflect(-L, N);

    vec3 diffusion = max(dot(V, R), 0.0f) * diffuse;

    vec3 specularation = pow(max(dot(V, R), 0.0f), power) * specular;

    color = vec4(ambient + diffusion + specularation, 1.0f);

}