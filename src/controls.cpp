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
#include <glm/ext.hpp>
#include "controls.h"
#include "init.h"

// freeglut forgot something -.-
#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4

#define ESC 27

#define BUTTON_LEFT  1
#define BUTTON_RIGHT 2

#define FORWARD  8
#define BACKWARD 16
#define LEFT     32
#define RIGHT    64
#define UPWARD   128
#define DOWNWARD 256

int scroll_buffer;
unsigned int state;

float dx, dy;

const glm::vec3 UP(0, 1, 0), SCALE(.1f);

void keyPress(unsigned char key) {
    switch (key) {
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

}

void mouseMove(int x, int y, Camera& camera) {

    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

    //if ((state & BUTTON_LEFT) == BUTTON_LEFT) {
    std::pair<int, int> center (UI::window.resolution.first / 2, UI::window.resolution.second / 2);

    dx += (center.first - x) * camera.mouseSpeed;
    dy += (center.second - y) * camera.mouseSpeed;

//    } else if ((state & BUTTON_RIGHT) == BUTTON_RIGHT) {
//
//    }


}

void updateCamera(Camera& c) {

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

    c.dist = glm::max(c.dist - ((float) scroll_buffer * c.scrollSpeed), glm::vec3());
    scroll_buffer = 0;

    glm::vec3 axis = cross(c.dir, UP);
    glm::quat pitch = glm::angleAxis(glm::radians(dy), axis);
    glm::quat yaw = glm::angleAxis(glm::radians(dx), UP);

    glm::quat dir = normalize(cross(pitch, yaw));

    c.dir = glm::rotate(dir, c.dir);

    dx = dy = 0.0f;

    glutWarpPointer(UI::window.resolution.first / 2, UI::window.resolution.second / 2);
}

glm::mat4 getViewMatrix(const Camera& c) {
    return glm::lookAt(c.pos - c.dist * c.dir, c.pos + c.dir, UP);
}

glm::mat4 getProjectionMatrix(const Camera& c) {
    return glm::perspectiveFov(c.viewAngle,
                               c.viewWidth,
                               c.viewHeight,
                               c.viewNearPlane,
                               c.viewFarPlane);
}
