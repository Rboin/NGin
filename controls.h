//
// Created by Erik on 3/21/2016.
//

#ifndef GAME_ENGINE_CONTROLS_H
#define GAME_ENGINE_CONTROLS_H

#include "engine.h"

struct Camera {
    float viewAngle;
    float viewWidth;
    float viewHeight;
    float viewNearPlane;
    float viewFarPlane;

    vec3 trans;
    vec3 scale;
    vec3 rot;

    vec3 pos;
    vec3 tar;

    vec3 posDelta;
};

void updateCamera(Camera &);
mat4 getViewMatrix(const Camera &);
mat4 getProjectionMatrix(const Camera &);

void mouseClick(int btn, int btnState, int x, int y);
void mouseMove(int x, int y, Camera &);
void keyPress(unsigned char key);

#endif //GAME_ENGINE_CONTROLS_H
