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

using namespace std;

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
            _state ^= FORWARD;
            break;
        case 's':
            _state ^= BACKWARD;
            break;
        case 'a':
            _state ^= LEFT;
            break;
        case 'd':
            _state ^= RIGHT;
            break;
        case 'x':
            _state ^= UPWARD;
            break;
        case 'z':
            _state ^= DOWNWARD;
            break;
    }
}

void Controls::mouseClick(int btn, int btnState, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON) {
        _state ^= BUTTON_LEFT;
    }

    if (btn == GLUT_RIGHT_BUTTON) {
        _state ^= BUTTON_RIGHT;
    }

    _lastClickCoordinates = vec2(x,y);
	
}


void Controls::mouseWheel(int btn, int dir, int x, int y)
{
	if (dir > 0)
	{
		_mouseWheelTravel -= 0.2;
	} else {
		_mouseWheelTravel += 0.2;
	}
}

void Controls::mouseMove(int x, int y)
{
	cout << x << "|" << y << endl;
	_mouseMoveCoordinates = vec2(x, y);
}




