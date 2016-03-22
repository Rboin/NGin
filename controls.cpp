//
// Created by Erik on 3/21/2016.
//

#include <iostream>
#include "controls.h"

#define ESC 27

#define BUTTON_LEFT     1
#define BUTTON_RIGHT    2
#define BUTTON_SCROLL   4

#define FORWARD  8
#define BACKWARD 16
#define LEFT     32
#define RIGHT    64

int state;

const vec3 UP(0,1,0);

vec2 prevMouseMovement;

bool btnLeft, btnRight, btnScroll;

void key_press(unsigned char key, Camera &camera) {
    switch(key) {
        case ESC:
            exit(0);
        case 'f':
            glutFullScreen();
            break;
        case 'q':
            camera.rot.y -= .1f;
            break;
        case 'e':
            camera.rot.y += .1f;
            break;
        case 'w':
            camera.trans.z += .1f;
            break;
        case 's':
            camera.trans.z -= .1f;
            break;
        case 'a':
            camera.trans.x += .1f;
            break;
        case 'd':
            camera.trans.x -= .1f;
            break;
        case 'x':
            camera.trans.y += .1f;
            break;
        case 'z':
            camera.trans.y -= .1f;
    }
}

void mouse_click(int btn, int btnState, int x, int y) {

    if (btn == GLUT_LEFT_BUTTON) {
        state ^= BUTTON_LEFT;
    }

    if (btn == GLUT_RIGHT_BUTTON) {
        state ^= BUTTON_RIGHT;
    }

    if (btn == GLUT_MIDDLE_BUTTON) {
        state ^= BUTTON_SCROLL;
    }

    prevMouseMovement = vec2(x,y);

}

void mouse_move(int x, int y, Camera &camera) {

    if ((state & BUTTON_LEFT) == state) {
        camera.rot.y += radians(prevMouseMovement.x - x);
        prevMouseMovement = vec2(x,y);
    }

    if ((state & BUTTON_RIGHT) == state) {
        camera.trans.y -= (prevMouseMovement.y - y) * .2f;
        prevMouseMovement = vec2(x,y);
    }

    if ((state & BUTTON_SCROLL) == state) {
        camera.scale -= (prevMouseMovement.y - y) * .2f;
        prevMouseMovement = vec2(x,y);
    }

}

mat4 getViewMatrix(const Camera & c) {
    return  translate(c.trans)* lookAt(c.pos * c.scale, c.tar, UP) *
            (rotate(c.rot.z, vec3(0,0,1)) * rotate(c.rot.y, vec3(0,1,0)) * rotate(c.rot.x, vec3(1,0,0)));
}

mat4 getProjectionMatrix(const Camera & c) {
    return perspectiveFov(c.viewAngle,
                          c.viewWidth,
                          c.viewHeight,
                          c.viewNearPlane,
                          c.viewFarPlane);
}
