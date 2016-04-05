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
#include "world.h"

using namespace std;

GLuint shader_program;

Camera camera = defaults::camera;

Mesh cone, cube, star, plane, pyramid;
vec3 lightPosition(0, 1, -4);

World * world;

void construct_shader();
void construct_meshes();
void construct_world();
void construct_world2();

int timeElapsed = 0;

void update(int tick) {

    int currentTimeElapsed = glutGet(GLUT_ELAPSED_TIME);
    int delta = currentTimeElapsed - timeElapsed;
    timeElapsed = currentTimeElapsed;

    updateCamera(camera, (float)delta / 10);
    world->update(delta);

    glutPostRedisplay();
    glutTimerFunc(1, update, tick++);
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
    // buffer clearing isn't supported in OpenGL 2.1
    //glClearBufferfv(GL_COLOR, 0, value_ptr(defaults::color_black));
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program);

    mat4 view = getViewMatrix(camera);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, value_ptr(view));

    mat4 model;

    world->render();

    // if the camera is close up to the target; the model does not get rendered.
    if (length2(camera.dist) > 1.0f) {
        model = translate(camera.pos);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, value_ptr(model));
        useMaterial(defaults::solidRed, shader_program);
        drawMesh(pyramid, GL_TRIANGLES);
    }

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

    construct_world2();

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

void construct_world() {
    world = new World();

    RenderPart orangeCube = {
            shader_program,
            cube,
            defaults::softOrange
    };

    RenderPart bluePyramid = {
            shader_program,
            pyramid,
            defaults::softBlue
    };

    int dist = 0;
    for(int i = 0; i < 2000; i++) {
        vec3 pos = vec3(rotate((float)i, vec3(0,1,0)) * translate(vec3(0,-20,dist)) * vec4(0,i/50,0,1));
        world->add_obstacle(new Obstacle(pos, vec3(0, radians((float) i), 0), vec3(5, 1, .5f), orangeCube));
        if(i%5==0) {
            if(i < 1000)
                dist++;
            else
                dist--;
        }
    }

    Vehicle * v = new Vehicle(vec3(), vec3(0,0,0), vec3(3), defaults::defaultVehicle, bluePyramid);
    v->steer()->set_status(ARRIVE_ON | FLEE_ON);
    v->steer()->set_target(vec3(-5,0,-50));
    world->add_vehicle(v);

    Vehicle * v2 = new Vehicle(vec3(4,0,0), vec3(0,0,0), vec3(3), defaults::defaultVehicle, bluePyramid);
    v2->steer()->set_status(ARRIVE_ON | SEEK_ON);
    v2->steer()->set_target(vec3(9,0,-50));
    world->add_vehicle(v2);

    //test_entity = new Entity(vec3(), vec3(), vec3(1), rp);
};

void construct_world2() {
    world = new World();

    RenderPart cosCube = {
            shader_program,
            cube,
            defaults::solidRed
    };

    RenderPart sinCube = {
            shader_program,
            cube,
            defaults::softBlue
    };

    RenderPart tanCube = {
            shader_program,
            cube,
            defaults::softOrange
    };

    RenderPart atanCube = {
            shader_program,
            cube,
            defaults::solidGreen
    };

    RenderPart vehiclePart = {
            shader_program,
            star,
            defaults::vehicleColor
    };

    Vehicle * v = new Vehicle(vec3(),vec3(),vec3(.2f), defaults::defaultVehicle, vehiclePart);
    v->steer()->set_status(ARRIVE_ON);
    v->steer()->set_target(vec3(0,50,-50));
    world->add_vehicle(v);


    for (int i = 0; i < 50; ++i) {
        vec3 pos = vec3(rotate(.0f, vec3(0,1,0)) * translate(vec3(0, cos((float)i), -i)) * vec4(0, 0, 0, 1));
        world->add_obstacle(new Obstacle(pos, vec3(), vec3(.5f), cosCube));
    }

    for (int i = 0; i < 50; ++i) {
        vec3 pos = vec3(rotate(.0f, vec3(0,1,0)) * translate(vec3(0, 5+sin((float)i), -i)) * vec4(0, 0, 0, 1));
        world->add_obstacle(new Obstacle(pos, vec3(), vec3(.5f), sinCube));
    }

    for (float i = 0; i < 50; i+=.1f) {
        vec3 pos = vec3(rotate(.0f, vec3(0,1,0)) * translate(vec3(0, -5-tan((float)i), -i)) * vec4(0, 0, 0, 1));
        world->add_obstacle(new Obstacle(pos, vec3(), vec3(.5f), tanCube));
    }

    for (float i = 0; i < 50; i+=.1f) {
        vec3 pos = vec3(rotate(.0f, vec3(0,1,0)) * translate(vec3(0, -10-cot((float)i), -i)) * vec4(0, 0, 0, 1));
        world->add_obstacle(new Obstacle(pos, vec3(), vec3(.5f), atanCube));
    }
}