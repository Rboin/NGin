//
// Created by erik on 2/22/16.
//

#ifndef CAMERA_GLEW_MOVEMENT_H
#define CAMERA_GLEW_MOVEMENT_H

#include <glm/glm.hpp>
#include "../ability.h"

using namespace glm;

class movement : public ability {
private:
    vec3 * position, * look, * target, velocity;
public:
    void update();
};


#endif //CAMERA_GLEW_MOVEMENT_H
