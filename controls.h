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

#ifndef GAME_ENGINE_CONTROLS_H
#define GAME_ENGINE_CONTROLS_H

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

#include "engine.h"

class Controls
{
private:
	int state;
	vec2 prevMouseMovement;
public:
	Controls();
	void mouseClick(int btn, int btnState, int x, int y);
	//void mouseMove(int x, int y, Camera &);
	void keyPress(unsigned char key);
	//void mouseWheel(int btn, int dir, int x, int y, Camera &);
	int getState()
	{
		return state;
	}
};

#endif
