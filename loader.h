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

#ifndef GAME_ENGINE_LOADER_H
#define GAME_ENGINE_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

#include "engine.h"

using namespace std;

class glsl
{
private:
    static char* contents;
public:
    glsl();
    ~glsl();
    static char* readFile(const char* filename);
    static bool compiledStatus(GLint shaderID);
    static GLuint makeVertexShader(const char* shaderSource);
    static GLuint makeFragmentShader(const char* shaderSource);
    static GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
};

bool loadOBJ(
        const char * path,
        vector<vec3> & out_vertices,
        vector<vec2> & out_uvs,
        vector<vec3> & out_normals
);


#endif //GAME_ENGINE_LOADER_H
