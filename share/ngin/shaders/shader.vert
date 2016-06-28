#version 120
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 light;

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texture_coordinate;

// pass the texture coordinate straight to the fragment shader
varying vec2 tex_cor;

varying vec3 N;
varying vec3 L;
varying vec3 V;

void main() {

    tex_cor = texture_coordinate;

    mat4 space = view * model;

    vec4 vert_pos = space * vec4(position, 1);

    N = normalize(mat3(space) * normal);
    L = normalize(mat3(view) * light);
    V = normalize(-vert_pos.xyz);

    gl_Position = projection * vert_pos;
}
