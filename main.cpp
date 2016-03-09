#include <iostream>

#include "scene/scene.h"
#include "render/render.h"

using namespace std;

// functions to be implemented
void render_camera();

void mouse_click(int button, int state, int x, int y);
void mouse_move(int x, int y);

float _forward, _strafe, _upward;
void press_key (unsigned char key, int xx, int yy);
void release_key (unsigned char key, int xx, int yy);

vec3 *dudes_position = new vec3(0.0f, 1.0f, -1.0f);
vec3 *dudes_look = new vec3();

Steering steering(5.0f, dudes_position, dudes_look);

void changeSize(int w, int h) {
    float ratio = ((float) w) / ((float) h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

void update(void) {

    steering.move();

    glutPostRedisplay();
}

void renderScene(void) {

    // Clear color and depth buffers
    glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    render_camera();

    glutWireTeapot(0.5f);

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
    glVertex3f(-100.0f, -1.0f, -100.0f);
    glVertex3f(-100.0f, -1.0f,  100.0f);
    glVertex3f( 100.0f, -1.0f,  100.0f);
    glVertex3f( 100.0f, -1.0f,  100.0f);
    glVertex3f( 100.0f, -1.0f, -100.0f);
    glVertex3f(-100.0f, -1.0f, -100.0f);
    glEnd();

    render_snowmen(*dudes_position, *dudes_look);

    glutSwapBuffers(); // Make it all visible
}

int main(int argc, char **argv) {

    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1400, 820);
    glutCreateWindow("Some program...");

    // registry
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene);
    glutIdleFunc(update);
    glutIgnoreKeyRepeat(1);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutKeyboardFunc(press_key);
    glutKeyboardUpFunc(release_key);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

int leftButton = 0;
int middleButton = 0;
int rightButton = 0;

// variables to translating and rotating the objects in the scene
float translate_x = 0.0f, translate_y = 0.0f, translate_z = 0.0f;
float rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
float scale_x = 1.0f, scale_y = 1.0f, scale_z = 1.0f;
float previousX = 0.0f, previousY = 0.0f, previousZ = 0.0f;

//  Camera position, look at position, up vector
double eyeX = 0, eyeY = 0, eyeZ = 0;
double centerX = 0, centerY = 0, centerZ = -1;
double upX = 0, upY = 1, upZ = 0;

void mouse_move(int x, int y) {

    //  Translate
    if (rightButton)
    {
        translate_x += (x - previousX) * 0.005;
        translate_y -= (y - previousY) * 0.005;
    }

    //  Scale
    if (middleButton)
    {
        scale_x -= (y - previousZ) * 0.005;
        scale_y -= (y - previousZ) * 0.005;
        scale_z -= (y - previousZ) * 0.005;
    }

    //  Rotate
    if (leftButton)
    {

        if ((y - previousY) >= 0)
            rot_x += (y - previousY);
        else
            rot_x += (y - previousY);
        if ((x - previousX) >= 0)
            rot_y += (x - previousX);
        else
            rot_y += (x - previousX);
    }

    // reset the previousX, previousY, and previousZ to the current position of the mouse
    previousX = (float)x;
    previousY = (float)y;
    previousZ = (float)y;

    glutPostRedisplay();

}

void mouse_click(int button, int state, int x, int y) {
    //  checks if the user presses the left button
    if (button == GLUT_LEFT_BUTTON)
    {
        leftButton = state == GLUT_DOWN;
    }
        // this is used to move the object with relative to the Z axis
    else if (button == GLUT_MIDDLE_BUTTON)
    {
        // if the mouse is pressed
        middleButton = state == GLUT_DOWN;
    }
        // if the user presses the right button
    else if (button == GLUT_RIGHT_BUTTON)
    {
        rightButton = state == GLUT_DOWN;
    }

    previousX = x;
    previousY = y;
    previousZ = y;
}

void press_key (unsigned char key, int xx, int yy) {

    // constants are defined in camera
    switch (key) {
        case 'q':
            exit(0);
        case 'f':
            glutFullScreen();
            break;
        case 'w':
            _forward = 1.5f;
            break;
        case 's':
            _forward = -1.5f;
            break;
        case 'a':
            _strafe = 1.5f;
            break;
        case 'd':
            _strafe = -1.5f;
            break;
        case 'z':
            _upward = 1.5f;
            break;
        case 'x':
            _upward = -1.5f;
            break;
    }
}

void release_key (unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w':
        case 's':
            _forward = 0.0f;
            break;
        case 'a':
        case 'd':
            _strafe = 0.0f;
            break;
        case 'z':
        case 'x':
            _upward = 0.0f;
            break;
    }
}

void render_camera() {
    glMatrixMode (GL_MODELVIEW);
    gluLookAt (eyeX, eyeY, eyeZ,
               centerX, centerY, centerZ,
               upX, upY, upZ);

    //  apply translation
    glTranslatef (translate_x, translate_y, translate_z);

    // apply rotation
    glRotatef (rot_x, 1.0f, 0.0f, 0.0f);
    glRotatef (rot_y, 0.0f, 1.0f, 0.0f);
    glRotatef (rot_z, 0.0f, 0.0f, 1.0f);

    //  Apply scaling
    glScalef (scale_x, scale_y, scale_z);

};