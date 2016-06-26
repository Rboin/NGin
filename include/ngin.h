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
#include <tuple>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define NGIN_SHADER_OBJECT_SHADER 1

namespace NGin {

    /**
     * Change type when using more than 8 shaders
     */
    typedef unsigned char shader_flag_t;

    namespace Model {

        struct Mesh {
            shader_flag_t shader_flags;
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
            const shader_flag_t shader_flag;
            Mesh* mesh = nullptr;
            Material material;
            //TODO add texture

            glm::vec3 position;
            glm::vec3 scale;
            glm::quat orientation;
        };

        struct Skeleton {

        };
    }

    namespace Registry {

        template<typename T>
        struct Register {

            typedef struct {
                std::string path;
                T* value = nullptr;
            } Record;
            std::map<std::string, Record> records;
        };

        extern Register<Model::Mesh>       meshes;
        extern Register<Model::Object3D>   objects;
    }

    namespace Util {

        struct ShaderProgram {
            const shader_flag_t flag;
            GLuint program;
            GLuint vertex;
            GLuint fragment;

            ShaderProgram(shader_flag_t _flag) : flag(_flag) {}
        };

        const ShaderProgram& getShader(const shader_flag_t index);

    }

    void init(int argc, char **argv);

}

#endif //NGIN_H
