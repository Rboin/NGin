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

#include <ngin.h>
#include <fstream>
#include <cstring>

using namespace NGin;

Registry::Register<Model::Mesh> Registry::meshes;

std::vector<glm::vec3>* vertices_buffer = nullptr;
std::vector<glm::vec2>* uv_buffer = nullptr;
std::vector<glm::vec3>* normal_buffer = nullptr;

bool _parse_mesh_file(const char* path) {
    // validate integrity
    if (vertices_buffer || uv_buffer || normal_buffer)
        throw "Buffers not closed properly...";

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2],
                                 &normalIndex[2]);
            if (matches != 9) {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

    }

    // initialize new buffers
    vertices_buffer = new std::vector<glm::vec3>();
    uv_buffer = new std::vector<glm::vec2>();
    normal_buffer = new std::vector<glm::vec3>();
    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        vertices_buffer->push_back(vertex);
        uv_buffer->push_back(uv);
        normal_buffer->push_back(normal);

    }

    return true;

}

void _bind_mesh(Model::Mesh& m, GLuint s) {
    glGenBuffers(1, &m.pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_buffer->size() * sizeof(glm::vec3), &(*vertices_buffer)[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m.uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, uv_buffer->size() * sizeof(glm::vec2), &(*uv_buffer)[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m.nor_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.nor_vbo);
    glBufferData(GL_ARRAY_BUFFER, normal_buffer->size() * sizeof(glm::vec3), &(*normal_buffer)[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);

    GLuint pos_id = glGetAttribLocation(s, "position");
    glBindBuffer(GL_ARRAY_BUFFER, m.pos_vbo);
    glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(pos_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uv_id = glGetAttribLocation(s, "texture_coordinate");
    glBindBuffer(GL_ARRAY_BUFFER, m.uv_vbo);
    glVertexAttribPointer(uv_id, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
    glEnableVertexAttribArray(uv_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint nor_id = glGetAttribLocation(s, "normal");
    glBindBuffer(GL_ARRAY_BUFFER, m.nor_vbo);
    glVertexAttribPointer(nor_id, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(nor_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

Model::Mesh* Model::meshFromFile(const char* filename, GLuint shader, GLuint bufferStrategy) {

    Model::Mesh* m = nullptr;

    if (_parse_mesh_file(filename)) {
        m = new Model::Mesh();
        m->buffer_strategy = bufferStrategy;
        m->ver_size = (GLsizei) vertices_buffer->size();
        _bind_mesh(*m, shader);
    }

    delete vertices_buffer;
    delete uv_buffer;
    delete normal_buffer;

    vertices_buffer = normal_buffer = nullptr;
    uv_buffer = nullptr;

    return m;
}

void Model::render(const Model::Mesh& mesh) {
    glBindVertexArray(mesh.vao);
    glDrawArrays(mesh.buffer_strategy, 0, mesh.ver_size);
    glBindVertexArray(0);
}
