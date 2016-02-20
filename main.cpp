#include <stdlib.h>
#include <math.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

using namespace std;


int i, j, width, height, previousTime;

GLdouble eyeX = 0.0, eyeY = 5.0, eyeZ = 1.0, xbuf, ybuf;

bool up, down, lefty, righty;
bool top_on, bottom_on, left_on, right_on;

GLdouble moveforward_backward = 5.0f, moveSiteward = 5.0f;

void changeSize(int w, int h) {

    width = w;
    height = h;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

// Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

// Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

// Draw Nose
    glColor3f(1.0f, 0.5f, 0.5f);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}

void renderScene(void) {

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = currentTime - previousTime;
    if(up)  	 	eyeZ -= timeInterval * moveforward_backward / 1000;
    if(down) 	    eyeZ += timeInterval * moveforward_backward / 1000;
    if(lefty)		eyeX -= timeInterval * moveSiteward / 1000;
    if(righty)		eyeX += timeInterval * moveSiteward / 1000;

    previousTime = currentTime;

    GLdouble tmpEyeX, tmpEyeY, tmpEyeZ;

    if (top_on) ybuf--;
    if (bottom_on) ybuf++;
    if (left_on) xbuf--;
    if (right_on) xbuf++;

    //Left Right rotation
    tmpEyeX = eyeX + sin(xbuf/100);
    tmpEyeZ = eyeZ -cos(xbuf/100);
    //looking up/down
    tmpEyeY = eyeY -sin(ybuf/100);

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();    // Set the camera

    gluLookAt(	eyeX, eyeY, eyeZ,
                  tmpEyeX, tmpEyeY, tmpEyeZ ,
                  0.0f, 1.0f,  0.0f);

// Draw ground

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

// Draw 36 SnowMen

    for (i = -3; i < 3; i++)
        for (j = -3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            drawSnowMan();
            glPopMatrix();
        }
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

    switch(key) {
        case 'w':
            // increase the camera's Z velocity
            up = true;
            break;
        case 's':
            // decrease the camera's Z velocity
            down = true;
            break;
        case 'a':
            // decrease the camera's X velocity
            lefty = true;
            break;
        case 'd':
            // increase the camera's X velocity
            righty = true;
            break;
    }
}

void processDownKeys(unsigned char key, int xx, int yy) {
    switch ( key ) {
        case 033:
            exit(0);
            break;
        case 'w': up=false; break;
        case 's': down=0; break;
        case 'a': lefty=0; break;
        case 'd': righty=0; break;
    }

}



void look(int x, int y) {

    cout << width << 'x' << height << endl;

    //check top
    if (y < height / 3)
        top_on = true;
    else if(top_on)
        top_on = false;

    //check bottom
    if (y > height / 3 * 2)
        bottom_on = true;
    else if (bottom_on)
        bottom_on = false;

    if (x < width / 3)
        left_on = true;
    else if (left_on)
        left_on = false;

    if (x > width / 3 * 2)
        right_on = true;
    else if (right_on)
        right_on = false;

}

int main(int argc, char **argv) {

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Snow Dudes");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(processDownKeys);

    // here are the two new functions
    //glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(look);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glutFullScreen();

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}