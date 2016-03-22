//
// Created by Erik on 3/21/2016.
//

#ifndef GAME_ENGINE_MESH_H
#define GAME_ENGINE_MESH_H

#include <iostream>
#include <string>
#include <vector>
#include "loader.h"

struct Mesh {
    GLuint vao;
    GLuint pos_vbo;
    GLuint nor_vbo;
    GLuint uv_vbo;
    std::vector<vec3> pos_buf;
    std::vector<vec3> nor_buf;
    std::vector<vec2> uv_buf;
};

void meshFromFile(const char *, Mesh&);
void meshFromFile(const char *, Mesh&);
void bindMesh(Mesh &, GLuint);
void drawMesh(const Mesh &, GLuint);
//void drawMesh(const Mesh &m) {drawMesh(m, GL_TRIANGLES);};

#endif //GAME_ENGINE_MESH_H
