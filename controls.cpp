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

Controls::Controls()
{

}

void Controls::keyPress(unsigned char key) {
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

void Controls::mouseClick(int btn, int btnState, int x, int y) {

    if (btn == GLUT_LEFT_BUTTON) {
        state ^= BUTTON_LEFT;
    }

    if (btn == GLUT_RIGHT_BUTTON) {
        state ^= BUTTON_RIGHT;
    }

    prevMouseMovement = vec2(x,y);

}
/*
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
*/

/*
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
*/



