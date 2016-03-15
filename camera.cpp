//
// Created by Erik on 3/9/2016.
//

#include "camera.h"

int leftButton = 0;
int middleButton = 0;
int rightButton = 0;

// variables to translating and rotating the objects in the scene
float translate_x = 0.0f, translate_y = -5.0f, translate_z = -10.0f;
float rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
float scale_x = .6f, scale_y = .6f, scale_z = .6f;
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
        translate_z -= (y - previousY) * 0.005;
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

void press_key (unsigned char key, int, int) {

    switch (key) {
        case 'q':
            exit(0);
        case 'f':
            glutFullScreen();
            break;
        case 'w':
            translate_z += .5f;
            break;
        case 's':
            translate_z -= .5f;
            break;
        case 'a':
            translate_x -= .5f;
            break;
        case 'd':
            translate_x += .5f;
            break;
        case 'z':
            translate_y += .5f;
            break;
        case 'x':
            translate_y -= .5f;
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