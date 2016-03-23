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
#include "controls.h"

#define ESC 27

#define BUTTON_LEFT     1
#define BUTTON_RIGHT    2
#define BUTTON_SCROLL   4

#define FORWARD  8
#define BACKWARD 16
#define LEFT     32
#define RIGHT    64
#define UPWARD   128
#define DOWNWARD 256

int state;

const vec3 UP(0,1,0);

vec2 prevMouseMovement;

bool btnLeft, btnRight, btnScroll;

void keyPress(unsigned char key) {
    switch(key) {
        case ESC:
        case 'q':
            exit(0);
        case 'f':
            glutFullScreen();
            break;
        case 'w':
            state ^= FORWARD;
            break;
        case 's':
            state ^= BACKWARD;
            break;
        case 'a':
            state ^= LEFT;
            break;
        case 'd':
            state ^= RIGHT;
            break;
        case 'x':
            state ^= UPWARD;
            break;
        case 'z':
            state ^= DOWNWARD;
            break;
    }
}

void mouseClick(int btn, int btnState, int x, int y) {

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

void mouseMove(int x, int y, Camera &camera) {

    if ((state & BUTTON_LEFT) == BUTTON_LEFT) {
        //camera.rot.y -= radians((prevMouseMovement.x - x) * 10);
        //camera.tar.y += radians(prevMouseMovement.y - y);
        prevMouseMovement = vec2(x,y);
    }

    if ((state & BUTTON_RIGHT) == BUTTON_RIGHT) {
        //camera.trans.y -= (prevMouseMovement.y - y) * .2f;
        prevMouseMovement = vec2(x,y);
    }

    if ((state & BUTTON_SCROLL) == BUTTON_SCROLL) {
        //camera.scale -= (prevMouseMovement.y - y) * .2f;
        prevMouseMovement = vec2(x,y);
    }

}

void updateCamera(Camera &c) {

    if ((state & FORWARD) == FORWARD) {
        c.trans.z += .1f;
    }

    if ((state & BACKWARD) == BACKWARD) {
        c.trans.z -= .1f;
    }

    if ((state & LEFT) == LEFT) {
        c.trans.x += .1f;
    }

    if ((state & RIGHT) == RIGHT) {
        c.trans.x -= .1f;
    }

    if ((state & UPWARD) == UPWARD) {
        c.trans.y += .1f;
    }

    if ((state & DOWNWARD) == DOWNWARD) {
        c.trans.y -= .1f;
    }

}

mat4 getViewMatrix(const Camera & c) {
    return  toMat4(c.rot) * translate(c.pos);
}

mat4 getProjectionMatrix(const Camera & c) {
    return perspectiveFov(c.viewAngle,
                          c.viewWidth,
                          c.viewHeight,
                          c.viewNearPlane,
                          c.viewFarPlane);
}
