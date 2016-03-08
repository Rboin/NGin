#include <iostream>
#include <stdlib.h> // standard definitions
#include <math.h> // math definitions
#include <stdio.h> // standard I/O

#include "scene/scene.h"
#include "render/render.h"
#include "faction/faction.h"

#include "keyboard.h"

using namespace std;

// Camera m_position
float x = 0.0f, y = -5.0f, z = 1.0f; // initially 5 units south of origin
float yDragStart = 0.0f;
float dyAngle = 0.0f;

// Camera direction
float lx = 0.0f, ly = 1.0f, lz = 0.0f; // camera points initially along y-axis
float _angle = 0.0f; // _angle of rotation for the camera direction
float deltaAngle = 0.0f; // additional _angle change when dragging
float yAngle = 0.0f, zmove = 0.0f;



// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

Scene *scene;
Actor * actor_1, * actor2, * actor3, * actor4;

vec3 *dudes_position = new vec3(-5, 5, 0);
vec3 *dudes_look = new vec3();

Steering steering(5.0f, dudes_position, dudes_look);

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
    if (keyboard::forward) { // update camera m_position
        x += keyboard::forward * lx * 0.1;
        y += keyboard::forward * ly * 0.1;
    }
    if (keyboard::strafe) {

        vec3 strafe = cross(vec3(x, y, 1), vec3(x+lx,y+ly, 1));

        x += keyboard::strafe * strafe.x * 0.1;
        y += keyboard::strafe * strafe.y * 0.1;
    }
    if(keyboard::upward) {
        z += keyboard::upward * 0.1;
    }

    //cout << timer << endl;

    if (timer++ % 180 == 0) {
//        actor_1->set_target(glm::vec3(20, 20, 0));
//        actor2->set_target(glm::vec3(-20, 20, 0));
//        actor3->set_target(glm::vec3(20, -20, 0));
//        actor4->set_target(glm::vec3(-20, -20, 0));
        //steering.seek(vec3(-5, -15, 0));
    }
//    if(timer % 100 == 0)
//        steering.wander();
//        actor_1->set_target(vec3(-5,-30,0));


//    cout << glm::to_string(steering.m_position) << ' ' << glm::to_string(steering.m_velocity) << endl;

    steering.move();

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

//    glEnable(GL_LIGHTING);
//
//    glEnable(GL_LIGHT0);
//
//    GLfloat lightpos[] = {.5f, 1.f, 1.f, 0.f};
//    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
//
//    glEnable(GL_LIGHT1);
//
//    GLfloat lightpos2[] = {.5f, 1.f, 1.f, 0.f};
//    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
//
//    glEnable(GL_NORMALIZE);

    // Somewhere in the initialization part of your program…
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

// Create light components
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { -1.5f, 1.0f, 4.0f, 1.0f };

// Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);

    float colorBlue[] = { 0.1, 0.7, 0.2, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBlue);
    glColor3f(0.1f,0.7f,0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-100.0f, -100.0f, 0.0f);
    glVertex3f(-100.0f, 100.0f, 0.0f);
    glVertex3f(100.0f, 100.0f, 0.0f);
    glVertex3f(100.0f, 100.0f, 0.0f);
    glVertex3f(100.0f, -100.0f, 0.0f);
    glVertex3f(-100.0f, -100.0f, 0.0f);
    glEnd();
//    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.f);

    // Draw ground - 200x200 square colored green
//    glColor3f(0.1, 0.7, 0.2);
//    glBegin(GL_QUADS);
//    glVertex3f(-100.0, -100.0, 0.0);
//    glVertex3f(-100.0, 100.0, 0.0);
//    glVertex3f(100.0, 100.0, 0.0);
//    glVertex3f(100.0, -100.0, 0.0);
//    glEnd();

    render_snowmen(*dudes_position, *dudes_look);

    //actor_1->render();
    scene->render();

    glutSwapBuffers(); // Make it all visible
}

//----------------------------------------------------------------------
// Process mouse drag events
// 
// This is called when dragging motion occurs. The variable
// _angle stores the camera _angle at the instance when dragging
// started, and deltaAngle is a additional _angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void mouseMove(int x, int y) {
    if (isDragging) { // only when dragging
        // update the change in _angle
        deltaAngle = (x - xDragStart) * 0.005;
        dyAngle = (y - yDragStart) * 0.005;

        vec2 mid_point(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);

        // camera's direction is set to _angle + deltaAngle
        lx = sin(_angle + deltaAngle);
        ly = cos(_angle + deltaAngle);
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
            _angle += deltaAngle; // update camera turning _angle
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

    Faction *snow_faction = new Faction();
    Faction *outlaw_faction = new Faction();
    outlaw_faction->hostile_to(snow_faction);
//    cout << outlaw_faction->enemies.size() << endl;
    outlaw_faction->make_peace(snow_faction);
//    cout << outlaw_faction->enemies.size() << endl;

    Actor * snowmen = new Actor(3.0f, 0.35f, render_snowmen);
    Actor * outlaw = new Actor(3.0f, 0.35f, render_outlaw);

    steering.seek(vec3(4, 5, 0));

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

//    scene->add_actor(actor_1);
//    scene->add_actor(actor2);
//    scene->add_actor(actor3);
//    scene->add_actor(actor4);

    // Draw 36 snow men
//    for (int i = -3; i < 3; i++)
//        for (int j = -3; j < 3; j++)
//            scene->add_actor(new Actor(FACTION_SNOWMEN, vec3(i * 7.5f, j * 7.5f, 0), glm::vec3(0, 0, 45), *snowmen));



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
    glutKeyboardFunc(keyboard::press_key); // process standard key clicks
    glutKeyboardUpFunc(keyboard::release_key);
    //glutSpecialFunc(pressSpecialKey); // process special key pressed
    // Warning: Nonstandard function! Delete if desired.
    //glutSpecialUpFunc(releaseSpecialKey); // process special key release

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0; // this is just to keep the compiler happy
}
