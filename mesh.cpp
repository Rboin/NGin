/*
 *  Modern OpenGL Game Engine C/C++
 *  Copyright (C) 2016  Erik Nijenhuis

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mesh.h"

void meshFromFile(const char *filename, Mesh &m) {
    loadOBJ(filename, m.pos_buf, m.uv_buf, m.nor_buf);
}

void bindMesh(Mesh &m, GLuint s) {
    glGenBuffers(1, &m.pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, m.pos_buf.size() * sizeof(vec3), &m.pos_buf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m.uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, m.uv_buf.size() * sizeof(vec2), &m.uv_buf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m.nor_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.nor_vbo);
    glBufferData(GL_ARRAY_BUFFER, m.nor_buf.size() * sizeof(vec3), &m.nor_buf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);

    GLuint pos_id = glGetAttribLocation(s, "position");
    glBindBuffer(GL_ARRAY_BUFFER, m.pos_vbo);
    glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
    glEnableVertexAttribArray(pos_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uv_id = glGetAttribLocation(s, "texture_coordinate");
    glBindBuffer(GL_ARRAY_BUFFER, m.uv_vbo);
    glVertexAttribPointer(uv_id, 3, GL_FLOAT, GL_FALSE, sizeof(vec2), 0);
    glEnableVertexAttribArray(uv_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint nor_id = glGetAttribLocation(s, "normal");
    glBindBuffer(GL_ARRAY_BUFFER, m.nor_vbo);
    glVertexAttribPointer(nor_id, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
    glEnableVertexAttribArray(nor_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void drawMesh (const Mesh &mesh, GLuint bufferStrategy) {
    glBindVertexArray(mesh.vao);
    glDrawArrays(bufferStrategy, 0, mesh.pos_buf.size());
    glBindVertexArray(0);
}

void drawMesh(const Mesh &m) {
    drawMesh(m, GL_TRIANGLES);
}
