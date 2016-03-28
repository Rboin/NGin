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
	_position = vec3();
	_direction = vec3(0,0,1);
	_distance = 5.0f;
	_type = CameraType::trackball;
	_perspective = CameraPerspective::thirdperson;
	_controls = c;
}

void Camera::setCameraType(CameraType type)
{
	switch (type)
	{
	case CameraType::trackball:
		//Set trackball defaults

		_distance = 5.0f;
		break;
	case CameraType::freemovable:
		//Set trackball defaults
		_distance = 0.0f;
		break;
	}

	_type = type;
}

void Camera::update() {
	if (_type == CameraType::freemovable)
	{
		updateFreeMovable();
	}
	else {
		updateTrackBall();
	}
}

vec2 lastMouseLocation;
void Camera::updateFreeMovable()
{
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
		if (_distance < 0.0f)
			_distance = 0.0f;
		_controls->resetMouseWheelTravel();
	}

	vec2 mouseState = _controls->getMouseCoordinates();

	vec3 axis = cross(_direction, UP);
	quat pitch = angleAxis(radians(lastMouseLocation.y - mouseState.y), axis);
	quat yaw = angleAxis(radians(lastMouseLocation.x - mouseState.x), UP);
	quat dir = normalize(cross(pitch, yaw));
	_direction = rotate(dir, _direction);

	lastMouseLocation = mouseState;
}

void Camera::updateTrackBall()
{
	if ((_controls->getState() & BUTTON_LEFT) == BUTTON_LEFT)
	{
		
		vec2 mouseState = _controls->getMouseDragCoordinates();
		if(mouseState == vec2()) return;
		vec2 lastClicked = _controls->getLastMouseDragCoordinates();

		cout << to_string(mouseState) << to_string(lastClicked) << endl;

		vec3 axis = cross(_direction, UP);
		quat pitch = angleAxis(radians(lastClicked.y - mouseState.y), axis);
		quat yaw   = angleAxis(radians(lastClicked.x - mouseState.x), UP);
		quat dir   = normalize(cross(pitch, yaw));
		_direction = rotate(dir, _direction);

		_controls->setLastClickCoordinates(mouseState);
	}
}

mat4 Camera::getViewMatrix() {
	vec3 pos = _position - _distance * _direction;
	vec3 look = _position + _direction;
	return lookAt(pos, look, UP);//translate(c.pos) * toMat4(c.rot);
}

mat4 Camera::getProjectionMatrix() {
	return perspectiveFov(_viewAngle,
		_viewWidth,
		_viewHeight,
		_viewNearPlane,
		_viewFarPlane);
}