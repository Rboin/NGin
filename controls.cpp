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

 //Mouse controls
#define BUTTON_LEFT     1
#define BUTTON_RIGHT    2
#define BUTTON_SCROLL_UP   4
#define BUTTON_SCROLL_DOWN   8

 //Keyboard controls
#define FORWARD  16
#define BACKWARD 32
#define LEFT     64
#define RIGHT    128
#define UPWARD   256
#define DOWNWARD 512

int state;

const vec3 UP(0,1,0), SCALE(.1f);

vec2 prevMouseMovement;

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

    prevMouseMovement = vec2(x,y);

}

void mouseWheel(int btn, int dir, int x, int y, Camera & camera)
{
	if (dir > 0)
	{
		camera.distance -= 0.2f;
	}
	else {
		camera.distance += 0.2f;
	}
}

void mouseMove(int x, int y, Camera &camera) {

    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

    if ((state & BUTTON_LEFT) == BUTTON_LEFT) {

        vec3 axis = cross(camera.direction, UP);
        quat pitch = angleAxis(radians(prevMouseMovement.y - y), axis);
        quat yaw = angleAxis(radians(prevMouseMovement.x - x), UP);

        quat dir = normalize(cross(pitch, yaw));

        camera.direction = rotate(dir, camera.direction);

    } else if ((state & BUTTON_RIGHT) == BUTTON_RIGHT) {

    } //else if ((state & BUTTON_SCROLL) == BUTTON_SCROLL) {
    //    camera.distance = max(camera.distance - (prevMouseMovement.y - y) * .1f, 0.0f);
    //}

    prevMouseMovement = vec2(x,y);

}

void updateCamera(Camera & camera) {

    if ((state & FORWARD) == FORWARD) {
		camera.position += camera.direction * SCALE;
    }

    if ((state & BACKWARD) == BACKWARD) {
		camera.position -= camera.direction * SCALE;
    }

    if ((state & LEFT) == LEFT) {
		camera.position -= cross(camera.direction, UP) * SCALE;
    }

    if ((state & RIGHT) == RIGHT) {
		camera.position += cross(camera.direction, UP) * SCALE;
    }

    if ((state & UPWARD) == UPWARD) {
		camera.position += UP * SCALE;
    }

    if ((state & DOWNWARD) == DOWNWARD) {
		camera.position -= UP * SCALE;
    }

}

mat4 getViewMatrix(const Camera & c) {
    return lookAt(c.position - c.distance * c.direction, c.position + c.direction, UP);//translate(c.pos) * toMat4(c.rot);
}

mat4 getProjectionMatrix(const Camera & c) {
    return perspectiveFov(c.viewAngle,
                          c.viewWidth,
                          c.viewHeight,
                          c.viewNearPlane,
                          c.viewFarPlane);
}
