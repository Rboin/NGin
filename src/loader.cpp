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

#include "loader.h"

char* contents;

char* readFile(const char* filename)
{
    // Open the file
    FILE* fp = fopen(filename, "r");
    // Move the file pointer to the end of the file and determing the length
    fseek(fp, 0, SEEK_END);
    long file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* contents = new char[file_length + 1];
    // zero out memory
    for (int i = 0; i < file_length + 1; i++)
    {
        contents[i] = 0;
    }
    // Here's the actual read
    fread(contents, 1, file_length, fp);
    // This is how you denote the end of a string in C
    contents[file_length + 1] = '\0';
    fclose(fp);
    return contents;
}

bool compiledStatus(GLint shaderID)
{
    GLint compiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if (compiled) {
        return true;
    }
    else {
        GLint logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        char* msgBuffer = new char[logLength];
        glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
        printf("%s\n", msgBuffer);
        delete (msgBuffer);
        return false;
    }
}

GLuint makeVertexShader(const char* shaderSource)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(vertexShaderID);
    bool compiledCorrectly = compiledStatus(vertexShaderID);
    if (compiledCorrectly)
    {
        return vertexShaderID;
    }
    return -1;
}

GLuint makeFragmentShader(const char* shaderSource)
{
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(fragmentShaderID);
    //delete[] source;
    bool compiledCorrectly = compiledStatus(fragmentShaderID);
    if (compiledCorrectly) {
        return fragmentShaderID;
    }
    return -1;
}

GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    GLuint shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShaderID);
    glAttachShader(shaderID, fragmentShaderID);
    glLinkProgram(shaderID);
    return shaderID;
}
