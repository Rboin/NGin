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

#ifndef NGIN_H
#define NGIN_H

#include <map>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace NGin {

    namespace Model {

        struct Mesh {
            GLuint buffer_strategy;
            GLuint vao;
            GLuint pos_vbo;
            GLuint nor_vbo;
            GLuint uv_vbo;
            GLsizei ver_size;
        };

        Mesh* meshFromFile(const char* filename, GLuint shader_program, GLuint type = GL_TRIANGLES);

        void render(const Mesh&);

        struct Material {
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float power;
        };

        void setMaterial(const Material&, const GLuint);

        struct Object3D {
            Mesh* mesh;
            Material* material;
            //TODO add texture
        };
    }

    namespace Registry {

        extern std::map<std::string, Model::Mesh*> meshes;
        extern std::map<std::string, Model::Material*> materials;
    }

    namespace Util {

        struct ShaderProgram {
            GLuint program;
            GLuint vertex;
            GLuint fragment;
        };

        ShaderProgram* setupShaderProgram(std::string, std::string);
    }

}

#endif //NGIN_H
