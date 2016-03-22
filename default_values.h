//
// Created by Erik on 3/21/2016.
//

#ifndef GAME_ENGINE_DEFAULTS_HPP
#define GAME_ENGINE_DEFAULTS_HPP

#include "material.h"
#include "controls.h"
#include "mesh.h"

namespace defaults {

    vec4 color_black(0,0,0,1);

    Camera camera = {
            45.0f,  // viewing angle
            800.0f, // viewing width
            600.0f, // viewing height
            0.1f,   // near plane
            100.0f, // far plane
            vec3(), // translation
            vec3(4.0f),// scale
            vec3(0,0,0), // rotation
            vec3(0, 0, -1), // position
            vec3(), // target
    };

    Material solidRed {
            vec3(1,.2f,.2f),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            100.0f
    };

    Material softBlue {
            vec3(.2f,.2f,1),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            10.0f
    };

    Material solidGreen {
            vec3(.2f,1,.2f),
            vec3(.5f,.5f,.5f),
            vec3(.7f),
            100.0f
    };

    Material softOrange {
            vec3(.8f,.5f,.2f),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            10.0f
    };

};

#endif //GAME_ENGINE_DEFAULTS_HPP