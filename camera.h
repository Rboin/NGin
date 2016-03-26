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

#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "engine.h"
#include "controls.h"

enum CameraType { trackball, freemovable };
enum CameraPerspective { firstperson, thirdperson };

class Camera {
	float viewAngle;
	float viewWidth;
	float viewHeight;
	float viewNearPlane;
	float viewFarPlane;

	vec3 position;
	vec3 direction;
	float distance;

	CameraType type;
	CameraPerspective perspective;
	Controls controls;

public:
	Camera(Controls & c);
	void updateCamera();
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();

	float getDistance()
	{
		return distance;
	}

	vec3 getPosition()
	{
		return position;
	}

	void setViewWidth(float w)
	{
		viewWidth = w;
	}

	void setViewHeight(float h)
	{
		viewHeight = h;
	}
};



#endif //GAME_ENGINE_CONTROLS_H
