//
// Created by Erik on 3/21/2016.
//

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
