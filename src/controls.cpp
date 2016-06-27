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

#include "controls.h"

#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4

#define ESC 27

#define BUTTON_LEFT         1
#define BUTTON_RIGHT        2

#define FORWARD  8
#define BACKWARD 16
#define LEFT     32
#define RIGHT    64
#define UPWARD   128
#define DOWNWARD 256

int scroll_buffer;
unsigned int state;

const glm::vec3 UP(0,1,0), SCALE(.1f);

glm::vec2 prevMouseMovement;

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

    if (btn == GLUT_WHEEL_UP) {
        scroll_buffer += btnState;
    }

    if (btn == GLUT_WHEEL_DOWN) {
        scroll_buffer -= btnState;
    }

    prevMouseMovement = glm::vec2(x,y);

}

void mouseMove(int x, int y, Camera &camera) {

    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

    if ((state & BUTTON_LEFT) == BUTTON_LEFT) {

        glm::vec3 axis = cross(camera.dir, UP);
        glm::quat pitch = glm::angleAxis(glm::radians(prevMouseMovement.y - y), axis);
        glm::quat yaw = glm::angleAxis(glm::radians(prevMouseMovement.x - x), UP);

        glm::quat dir = normalize(cross(pitch, yaw));

        camera.dir = glm::rotate(dir, camera.dir);

    } else if ((state & BUTTON_RIGHT) == BUTTON_RIGHT) {

    }

    prevMouseMovement = glm::vec2(x,y);

}

void updateCamera(Camera &c) {

    if ((state & FORWARD) == FORWARD) {
        c.pos += c.dir * SCALE;
    }

    if ((state & BACKWARD) == BACKWARD) {
        c.pos -= c.dir * SCALE;
    }

    if ((state & LEFT) == LEFT) {
        c.pos -= cross(c.dir, UP) * SCALE;
    }

    if ((state & RIGHT) == RIGHT) {
        c.pos += cross(c.dir, UP) * SCALE;
    }

    if ((state & UPWARD) == UPWARD) {
        c.pos += UP * SCALE;
    }

    if ((state & DOWNWARD) == DOWNWARD) {
        c.pos -= UP * SCALE;
    }

    if (scroll_buffer > 0) {
        scroll_buffer--;
        c.dist *= 1.01f;
    } else if (scroll_buffer < 0) {
        scroll_buffer++;
        c.dist *= 0.99f;
    }

}

glm::mat4 getViewMatrix(const Camera & c) {
    return glm::lookAt(c.pos - c.dist * c.dir, c.pos + c.dir, UP);
}

glm::mat4 getProjectionMatrix(const Camera & c) {
    return glm::perspectiveFov(c.viewAngle,
                               c.viewWidth,
                               c.viewHeight,
                               c.viewNearPlane,
                               c.viewFarPlane);
}
