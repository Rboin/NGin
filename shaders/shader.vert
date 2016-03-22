#version 430 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 light;

in vec3 position;
in vec3 normal;
in vec2 texture_coordinate;

out vec2 tex_cor;

out vec3 N;
out vec3 L;
out vec3 V;

void main() {

    tex_cor = texture_coordinate;

    mat4 space = view * model;

    vec4 vert_pos = space * vec4(position, 1);

    N = normalize( mat3(space) * normal );
    L = normalize( mat3(view) * light - vert_pos.xyz );
    V = normalize( -vert_pos.xyz );

    gl_Position = projection * vert_pos;
}