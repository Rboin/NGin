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

#include <GL/freeglut.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    float viewAngle;
    float viewWidth;
    float viewHeight;
    float viewNearPlane;
    float viewFarPlane;

    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 dist;
};

void updateCamera(Camera &);
glm::mat4 getViewMatrix(const Camera &);
glm::mat4 getProjectionMatrix(const Camera &);

void mouseClick(int btn, int btnState, int x, int y);
void mouseMove(int x, int y, Camera &);
void keyPress(unsigned char key);

#endif //GAME_ENGINE_CONTROLS_H
