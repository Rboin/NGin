#include <iostream>

#include "render/render.h"
#include "camera.h"

using namespace std;

void resize(int w, int h);
void render();
void update();

vec3 *dudes_position = new vec3(0,-1,0);
vec3 *dudes_look = new vec3();

int main(int argc, char **argv) {

    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1400, 820);
    glutCreateWindow("Some program...");

    // registry
    glutReshapeFunc(resize);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutKeyboardFunc(press_key);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutMainLoop();

    return 0;
}

void update() {

    glutPostRedisplay();
}

void render() {

    // Clear color and depth buffers
    glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    render_camera();

    render_light();

    render_ground();

    render_snowmen(*dudes_position, *dudes_look);

    glutSwapBuffers(); // Make it all visible
}

void resize(int w, int h) {
    float ratio = ((float) w) / ((float) h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}