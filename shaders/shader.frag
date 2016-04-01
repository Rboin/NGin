#version 120

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

uniform float power;

varying vec2 tex_cor;

varying vec3 N;
varying vec3 L;
varying vec3 V;

void main() {

    vec3 R = reflect(-L, N);

    vec3 diffusion = max(dot(V, R), 0.0f) * diffuse;//texture2D(sampler, tex_cor).rgb;

    vec3 specularation = pow(max(dot(V, R), 0.0f), power) * specular;

    gl_FragColor = vec4(ambient + diffusion + specularation, 1.0f);

}