#include <iostream>

#include "engine.h"
#include "render/render.h"
#include "camera.h"

#include "maze/maze.h"

using namespace std;

void resize(int w, int h);
void render();
void update();

World * world;

int main(int argc, char **argv) {

    world = new World();

    Maze * maze = new Maze(10, 10);

    vec4 wall_scale(vec4(2, 2, .3f, 1));

    // top
    for (int j = 0; j < maze->get_width(); j++) {
        if(j == maze->get_width()/2)
            continue;
        Obstacle * wall = new Obstacle(vec4(j*2-maze->get_width(), 0, -1-maze->get_height(), 0), vec4(), wall_scale);
        world->add_obstacle(*wall);
    }

    // left
    for (int j = 0; j < maze->get_height(); j++) {
        if(j == maze->get_height()/2)
            continue;
        Obstacle * wall = new Obstacle(vec4(-1-maze->get_width(), 0, j*2-maze->get_height(), 0), vec4(0,90,0,0), wall_scale);
        world->add_obstacle(*wall);
    }

    for (int i = 0; i < maze->get_height()*2; i+=2) {

        for (int j = 0; j < maze->get_width()*2; j+=2) {

            int p = ((i/2) * maze->get_width()) + (j/2);

            // bottom is not open
            if(!maze->is_open(p, false) && !(j == maze->get_width() && i == maze->get_height()*2-2)) {
                Obstacle * wall = new Obstacle(vec4(j-maze->get_width(), 0, i+1-maze->get_height(), 0), vec4(), wall_scale);
                world->add_obstacle(*wall);
            }

            // right is not open
            if(!maze->is_open(p, true) && !(j == maze->get_width()*2-2 && i == maze->get_height())) {
                Obstacle * wall = new Obstacle(vec4(j+1-maze->get_width(), 0, i-maze->get_height(), 0), vec4(0,90,0,0), wall_scale);
                world->add_obstacle(*wall);
            }

        }

    }

    Vehicle snowmen(1.3f,   // mass
                    .003f,  // speed
                    .1f,    // force
                    .3f,    // turn rate
                    Deceleration::normal);

    Vehicle * v = new Vehicle(vec4(5,-1.3,-5,1), vec4(), vec4(), snowmen);

    world->add_vehicle(*v);

    v->steer()->m_arrive_on = true;
    v->steer()->m_seek_on = false;

    v->steer()->set_target(vec4(-5, -1.3f, -5, 1));

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