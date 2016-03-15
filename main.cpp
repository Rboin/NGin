#include <iostream>

#include "world.h"
#include "camera.h"

using namespace std;

void resize(int w, int h);
void render();
void update();

World * world;

int main(int argc, char **argv) {

    world = new MazeWorld();

    Vehicle snowmen(100.0f,   // mass
                    .004f,  // speed
                    .1f,    // force
                    .3f,    // turn rate
                    Deceleration::slow);

    Vehicle * v = new Vehicle(vec4(0,-1.3f,0,1), vec4(), vec4(), snowmen);
    Vehicle * v1 = new Vehicle(vec4(0,-1.3f,0,1), vec4(), vec4(), snowmen);
    Vehicle * v2 = new Vehicle(vec4(0,-1.3f,0,1), vec4(), vec4(), snowmen);
    Vehicle * v3 = new Vehicle(vec4(0,-1.3f,0,1), vec4(), vec4(), snowmen);

    world->add_vehicle(v);
    world->add_vehicle(v1);
    world->add_vehicle(v2);
    world->add_vehicle(v3);

    v->steer()->m_arrive_on = true;
    v->steer()->m_seek_on = false;
    v->steer()->m_flee_on = true;

    v1->steer()->m_arrive_on = true;
    v1->steer()->m_seek_on = false;
    v1->steer()->m_flee_on = true;

    v2->steer()->m_arrive_on = true;
    v2->steer()->m_seek_on = false;
    v2->steer()->m_flee_on = true;

    v3->steer()->m_arrive_on = true;
    v3->steer()->m_seek_on = false;
    v3->steer()->m_flee_on = true;

    v->steer()->set_target(vec4(0, -1.3f, -52, 1));
    v1->steer()->set_target(vec4(0, -1.3f, 52, 1));
    v2->steer()->set_target(vec4(-52, -1.3f, 0, 1));
    v3->steer()->set_target(vec4(52, -1.3f, 0, 1));

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

int elapsed_time = 0;

void update() {

    int current_time = glutGet(GLUT_ELAPSED_TIME);
    int delta = current_time - elapsed_time;
    elapsed_time = current_time;

    world->update(delta);
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

    world->render();

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