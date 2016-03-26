#include <iostream>
#include "camera.h"
#include "default_values.h"

using namespace defaults;
using namespace std;

Camera::Camera(Controls *c)
{
	_viewAngle = 45.0f;
	_viewWidth = 800.0f;
	_viewHeight = 600.0f;
	_viewNearPlane = 0.1f;
	_viewFarPlane = 100.0f;
	_position = vec3(0, 0, 0);
	_direction = vec3(0, 0, 1);
	_distance = 4.0f;
	_type = CameraType::freemovable;
	_perspective = CameraPerspective::thirdperson;
	_controls = c;
}

void Camera::updateCamera() {
	if ((_controls->getState() & FORWARD) == FORWARD) {
		_position += _direction * SCALE;
	}

	if ((_controls->getState() & BACKWARD) == BACKWARD) {
		_position -= _direction * SCALE;
	}

	if ((_controls->getState() & LEFT) == LEFT) {
		_position -= cross(_direction, UP) * SCALE;
	}

	if ((_controls->getState() & RIGHT) == RIGHT) {
		_position += cross(_direction, UP) * SCALE;
	}

	if ((_controls->getState() & UPWARD) == UPWARD) {
		_position += UP * SCALE;
	}

	if ((_controls->getState() & DOWNWARD) == DOWNWARD) {
		_position -= UP * SCALE;
	}
	
	if (_controls->getMouseWheelTravel() != 0)
	{
		_distance += _controls->getMouseWheelTravel();
		_controls->resetMouseWheelTravel();
	}

	// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
	//^ Awesome link indeed :D
	if ((_controls->getState() & BUTTON_LEFT) == BUTTON_LEFT)
	{
		vec2 mouseState = _controls->getMouseMoveCoordinates();
		vec2 lastClicked = _controls->getLastMouseClickCoordinates();

		vec3 axis = cross(_direction, UP);
		quat pitch = angleAxis(radians(lastClicked.y - mouseState.y), axis);
		quat yaw = angleAxis(radians(lastClicked.x - mouseState.x), UP);
		quat dir = normalize(cross(pitch, yaw));
		_direction = rotate(dir, _direction);

		_controls->setLastClickCoordinates(mouseState);
	}
}

mat4 Camera::getViewMatrix() {
	return lookAt(_position - _distance * _direction, _position + _direction, UP);//translate(c.pos) * toMat4(c.rot);
}

mat4 Camera::getProjectionMatrix() {
	return perspectiveFov(_viewAngle,
		_viewWidth,
		_viewHeight,
		_viewNearPlane,
		_viewFarPlane);
}