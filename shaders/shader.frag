
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

uniform float power;

//uniform sampler2D sampler;

varying vec4 color;

attribute vec2 tex_cor;

attribute vec3 N;
attribute vec3 L;
attribute vec3 V;

void main() {

    vec3 R = reflect(-L, N);

    vec3 diffusion = max(dot(V, R), 0.0f) * diffuse;//texture2D(sampler, tex_cor).rgb;

    vec3 specularation = pow(max(dot(V, R), 0.0f), power) * specular;

    color = vec4(ambient + diffusion + specularation, 1.0f);

}