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

#include <iostream>

#include "mesh.h"
#include "controls.h"
#include "default_values.h"

using namespace std;

GLuint shader_program;

Camera camera = defaults::camera;

Mesh cone, cube, star, plane, pyramid;
vec3 lightPosition(0, 1, -4);

void construct_shader();
void construct_meshes();

void update(int delta) {
    updateCamera(camera);

    glutPostRedisplay();
    glutTimerFunc(20, update, delta+1);
};

void resize (int w, int h) {
    camera.viewWidth = w;
    camera.viewHeight = h;
    mat4 projection = getProjectionMatrix(camera);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, value_ptr(projection));
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void draw () {
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    //glClearBufferfv(GL_COLOR, 0, value_ptr(defaults::color_black));
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program);

    mat4 view = getViewMatrix(camera);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, value_ptr(view));

    mat4 trans;

    if (length2(camera.dist) > 1.0f) {
        trans = translate(camera.pos);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, value_ptr(trans));
        drawMaterial(defaults::solidRed, shader_program);
        drawMesh(pyramid, GL_TRIANGLES);
    }

    trans = translate(vec3(-4.0f,0,4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, value_ptr(trans));
    drawMaterial(defaults::solidRed, shader_program);
    drawMesh(cube, GL_TRIANGLES);

    trans = translate(vec3(4.0f,0,4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, value_ptr(trans));
    drawMaterial(defaults::softBlue, shader_program);
    drawMesh(pyramid, GL_TRIANGLES);

    trans = translate(vec3(-4.0f,0,-4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, value_ptr(trans));
    drawMaterial(defaults::solidGreen, shader_program);
    drawMesh(pyramid, GL_TRIANGLES);

    trans = translate(vec3(4.0f,0,-4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, value_ptr(trans));
    drawMaterial(defaults::softOrange, shader_program);
    drawMesh(cube, GL_TRIANGLES);

    glutSwapBuffers();
}

void keyPress(unsigned char key, int, int) {
    keyPress(key);
}

void mouseMove(int x, int y) {
    mouseMove(x, y, camera);
    glutPostRedisplay();
}

void special_key(int i, int x, int y) {
    switch(i) {
    }
}

int main (int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Some program...");

    glutReshapeFunc(resize);
    glutDisplayFunc(draw);
    glutIgnoreKeyRepeat(1);
    glutTimerFunc(200, update, 0);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyPress);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(special_key);

    glewInit();

    construct_shader();
    construct_meshes();
    mat4 projection = getProjectionMatrix(camera);
    glUseProgram(shader_program);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, value_ptr(projection));
    glUniform3fv(glGetUniformLocation(shader_program, "light"), 1, value_ptr(lightPosition));

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

void construct_shader() {
    GLuint vertShader = glsl::makeVertexShader(glsl::readFile("shaders/shader.vert"));
    GLuint fragShader = glsl::makeFragmentShader(glsl::readFile("shaders/shader.frag"));
    shader_program = glsl::makeShaderProgram(
            vertShader,
            fragShader
    );
}

void construct_meshes() {
    meshFromFile("objects/cone.obj", cone);
    meshFromFile("objects/cube.obj", cube);
    meshFromFile("objects/star.obj", star);
    meshFromFile("objects/plane.obj", plane);
    meshFromFile("objects/pyramid.obj", pyramid);
    bindMesh(cone, shader_program);
    bindMesh(cube, shader_program);
    bindMesh(star, shader_program);
    bindMesh(plane, shader_program);
    bindMesh(pyramid, shader_program);
}