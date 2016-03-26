#include <iostream>
#include "camera.h"
#include "default_values.h"

using namespace defaults;
Camera::Camera(Controls & c)
{
	viewAngle = 45.0f;
	viewWidth = 800.0f;
	viewHeight = 600.0f;
	viewNearPlane = 0.1f;
	viewFarPlane = 100.0f;
	position = vec3(0, 0, 0);
	direction = vec3(0, 0, 1);
	distance = 4.0f;
	type = CameraType::freemovable;
	perspective = CameraPerspective::thirdperson;
	controls = c;
}
void Camera::updateCamera() {

	if ((controls.getState() & FORWARD) == FORWARD) {
		position += direction * SCALE;
	}

	if ((controls.getState() & BACKWARD) == BACKWARD) {
		position -= direction * SCALE;
	}

	if ((controls.getState() & LEFT) == LEFT) {
		position -= cross(direction, UP) * SCALE;
	}

	if ((controls.getState() & RIGHT) == RIGHT) {
		position += cross(direction, UP) * SCALE;
	}

	if ((controls.getState() & UPWARD) == UPWARD) {
		position += UP * SCALE;
	}

	if ((controls.getState() & DOWNWARD) == DOWNWARD) {
		position -= UP * SCALE;
	}

}

mat4 Camera::getViewMatrix() {
	return lookAt(position - distance * direction, position + direction, UP);//translate(c.pos) * toMat4(c.rot);
}

mat4 Camera::getProjectionMatrix() {
	return perspectiveFov(viewAngle,
		viewWidth,
		viewHeight,
		viewNearPlane,
		viewFarPlane);
}