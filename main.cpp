//----------------------------------------------------------------------
//	Best if viewed with tab stops set every 2 columns.
//----------------------------------------------------------------------
//	File: opengl-3D-sample.cpp - Sample 3D OpenGL/GLUT program
//	Origin: Lighthouse3D (heavily modified by Dave Mount)
//
//	This is a sample program that illustrates OpenGL and GLUT. It
//	renders a picture of 36 snowmen. The camera can be moved by dragging
//	the mouse. The camera moves forward by hitting the up-arrow key and
//	back by moving the down-arrow key. Hit ESC, 'q' or 'Q' to exit.
//
//	Warning #1: This program uses the function glutSpecialUpFunc, which
//	may not be available in all GLUT implementations. If your system
//	does not have it, you can comment this line out, but the up arrow
//	processing will not be correct.
//
//	Warning #2: This is a minimalist program. Very little attention has
//	been paid to good programming technique.
//----------------------------------------------------------------------
#include <iostream>
#include <stdlib.h> // standard definitions
#include <math.h> // math definitions
#include <stdio.h> // standard I/O

// include files are in a slightly different location for MacOS
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//
//#include <GL/glut.h>
#include "scene/Scene.h"
//#include "actor/Actor.h"
//#include "faction/faction.h"
#include "render/render.h"

//#endif

// escape key (for exit)
#define ESC 27

//----------------------------------------------------------------------
// Global variables
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera m_position. The values (lx, ly)
// point in the direction the camera is looking. The variables angle and
// deltaAngle control the camera's angle. The variable deltaMove
// indicates the amount of incremental motion for the camera with each
// redraw cycle. The variables isDragging and xDragStart are used to
// monitor the mouse when it drags (with the left button down).
//----------------------------------------------------------------------

using namespace std;

vec3 camera_position, direction;

// Camera m_position
float x = 0.0, y = -5.0, z = 1.0f; // initially 5 units south of origin
float yDragStart = 0.0f;
float deltaMove = 0.0; // initially camera doesn't move
float dyAngle = 0.0f;
//float strafeMove = 0.0;

// Camera direction
float lx = 0.0, ly = 1.0, lz = 0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging
float yAngle = 0.0, zmove = 0.0f;



// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

Scene *scene;
Actor * actor_1, * actor2, * actor3, * actor4;

mat2 rotateDeg(float degrees) {
    double rad = (3.14f / 180) * degrees;
    return mat2(
            cos(rad), -sin(rad),
            sin(rad), cos(rad)
    );
}

//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h) {
    float ratio = ((float) w) / ((float) h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

int timer = 1;

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update(void) {
    if (deltaMove) { // update camera m_position
        x += deltaMove * lx * 0.1;
        y += deltaMove * ly * 0.1;
    }
    if(zmove) {
        cout << "hoi" << endl;
        z += zmove * 0.1;
    }
//    if (strafeMove) {
//        x += strafeMove * (sin(angle + 1.0f)) * 0.1;
//        y += strafeMove * (cos(angle - 1.0f)) * 0.1;
//    }

    //cout << timer << endl;

    if (timer++ % 150 == 0) {
        actor_1->set_target(glm::vec3(20, 20, 0));
        actor2->set_target(glm::vec3(-20, 20, 0));
        actor3->set_target(glm::vec3(20, -20, 0));
        actor4->set_target(glm::vec3(-20, -20, 0));
    }
//        actor_1->set_target(vec3(-5,-30,0));


    scene->update();
//    actor_1->update();

    glutPostRedisplay(); // redisplay everything
}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We first update the camera location based on its distance from the
// origin and its direction.
//----------------------------------------------------------------------
void renderScene(void) {
    int i, j;

    // Clear color and depth buffers
    glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera centered at (x,y,1) and looking along directional
    // vector (lx, ly, 0), with the z-axis pointing up
    gluLookAt(
            x, y, z,
            x + lx, y + ly, z + lz,
            0.0, 0.0, 1.0);

    // Draw ground - 200x200 square colored green
    glColor3f(0.1, 0.7, 0.2);
    glBegin(GL_QUADS);
    glVertex3f(-100.0, -100.0, 0.0);
    glVertex3f(-100.0, 100.0, 0.0);
    glVertex3f(100.0, 100.0, 0.0);
    glVertex3f(100.0, -100.0, 0.0);
    glEnd();

    //actor_1->render();
    scene->render();

    glutSwapBuffers(); // Make it all visible
}

//----------------------------------------------------------------------
// User-input callbacks
//
// processNormalKeys: ESC, q, and Q cause program to exit
// pressSpecialKey: Up arrow = forward motion, down arrow = backwards
// releaseSpecialKey: Set incremental motion to zero
//----------------------------------------------------------------------
void press_key(unsigned char key, int xx, int yy) {
    switch (key) {
        case ESC:
        case 'q':
        case 'Q':
            exit(0);
        case 'f':
            glutFullScreen();
            break;
        case 'w' :
            deltaMove = 1.5;
            break;
        case 's' :
            deltaMove = -1.5;
            break;
        case 'x' :
            zmove = 1.5;
            break;
        case 'z' :
            zmove = -1.5;
            break;
//        case 'a':
//            strafeMove = -1.5;
//            break;
//        case 'd':
//            strafeMove = 1.5;
//            break;
    }
}

void release_key(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w' :
            deltaMove = 0.0;
            break;
        case 's' :
            deltaMove = 0.0;
            break;
//        case 'a':
//            strafeMove = 0;
//            break;
//        case 'd':
//            strafeMove = 0;
//            break;
        case 'x' :
            zmove = 0;
            break;
        case 'z' :
            zmove = 0;
            break;
    }
}

//----------------------------------------------------------------------
// Process mouse drag events
// 
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void mouseMove(int x, int y) {
    if (isDragging) { // only when dragging
        // update the change in angle
        deltaAngle = (x - xDragStart) * 0.005;
        dyAngle = (y - yDragStart) * 0.005;

        vec2 mid_point(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);

        cerr << deltaAngle << endl;

        // camera's direction is set to angle + deltaAngle
        lx = sin(angle + deltaAngle);
        ly = cos(angle + deltaAngle);
        lz = -sin(yAngle + dyAngle);
        //glutWarpPointer(mid_point.x, mid_point.y);
    }
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) { // left mouse button pressed
            isDragging = 1; // start dragging
            xDragStart = x; // save x where button first pressed
			yDragStart = y;
        }
        else { /* (state = GLUT_UP) */
            angle += deltaAngle; // update camera turning angle
			yAngle += dyAngle;
            isDragging = 0; // no longer dragging
        }
    }
}
float test = 1.0f;
mat4 Trx = mat4(
        1, 0, 0 ,0,
        0, cos(test), -cos(test), 0,
        0, sin(test), cos(test), 0,
        0,0,0,1
);
mat4 Try = mat4(
        cos(test), 0, sin(test), 0,
        0, 1, 0, 0,
        -sin(test), 0, cos(test), 0,
        0,0,0,1
);
mat4 Trz = mat4(
        cos(test), -sin(test), 0, 0,
        sin(test), cos(test), 0, 0,
        0,0,1,0,
        0,0,0,1
);

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
int main(int argc, char **argv) {
    printf("\n\
-----------------------------------------------------------------------\n\
  OpenGL Sample Program:\n\
  - Drag mouse left-right to rotate camera\n\
  - Hold up-arrow/down-arrow to move camera forward/backward\n\
  - q or ESC to quit\n\
-----------------------------------------------------------------------\n");

    scene = new Scene();

    Actor * snowmen = new Actor(3.0f, 0.35f, render_snowmen);
    Actor * outlaw = new Actor(3.0f, 0.35f, render_outlaw);

    scene->add_stereotype("snowmen", snowmen);
    scene->add_stereotype("outlaw", outlaw);


    actor_1 = new Actor(FACTION_OUTLAW, vec3(0.5, 0.5, 0), vec3(0, 0, 45), *outlaw);
    actor_1->set_target(glm::vec3(20, 0, 0));
    actor2 = new Actor(FACTION_OUTLAW, vec3(0.5, 0.5, 0), vec3(0, 0, 45), *outlaw);
    actor2->set_target(glm::vec3(-20, 0, 0));
    actor3 = new Actor(FACTION_OUTLAW, vec3(0.5, 0.5, 0), vec3(0, 0, 45), *outlaw);
    actor3->set_target(glm::vec3(0, -20, 0));
    actor4 = new Actor(FACTION_OUTLAW, vec3(0.5, 0.5, 0), vec3(0, 0, 45), *outlaw);
    actor4->set_target(glm::vec3(-20, -20, 0));

    scene->add_actor(actor_1);
    scene->add_actor(actor2);
    scene->add_actor(actor3);
    scene->add_actor(actor4);

    // Draw 36 snow men
    for (int i = -3; i < 3; i++)
        for (int j = -3; j < 3; j++)
            scene->add_actor(new Actor(FACTION_SNOWMEN, vec3(i * 7.5f, j * 7.5f, 0), glm::vec3(0, 0, 45), *snowmen));



    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1400, 820);
    glutCreateWindow("OpenGL/GLUT Sampe Program");

    // register callbacks
    glutReshapeFunc(changeSize); // window reshape callback
    glutDisplayFunc(renderScene); // (re)display callback
    glutIdleFunc(update); // incremental update
    glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
    glutMouseFunc(mouseButton); // process mouse button push/release
    glutMotionFunc(mouseMove); // process mouse dragging motion
    glutKeyboardFunc(press_key); // process standard key clicks
    glutKeyboardUpFunc(release_key);
    //glutSpecialFunc(pressSpecialKey); // process special key pressed
    // Warning: Nonstandard function! Delete if desired.
    //glutSpecialUpFunc(releaseSpecialKey); // process special key release

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0; // this is just to keep the compiler happy
}
