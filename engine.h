//
// Created by Erik on 3/8/2016.
//

#ifndef SNOWMENS_ENGINE_H
#define SNOWMENS_ENGINE_H

#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

namespace engine {

    typedef void (*update_t)(int);
    typedef void (*render_t)();

};

#endif //SNOWMENS_ENGINE_H
