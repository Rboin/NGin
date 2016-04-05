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

#ifndef GAME_ENGINE_DEFAULTS_HPP
#define GAME_ENGINE_DEFAULTS_HPP

#include "material.h"
#include "controls.h"
#include "mesh.h"
#include "entity.h"
#include "steering.h"
#include "vehicle.h"

namespace defaults {

    vec4 color_black(0,0,0,1);

    Camera camera = {
            45.0f,  // viewing angle
            800.0f, // viewing width
            600.0f, // viewing height
            0.1f,   // near plane
            1000.0f, // far plane
            //vec3(), // translation
            //vec3(4.0f),// scale
            vec3(0, 0, 10), // position
            vec3(0, 0, -1), // direction
            vec3(0),// distance of target
            //quat(0, 0, 1, 0), // rotation lookat -z thus forward
    };

    Material solidRed {
            vec3(1,.2f,.2f),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            100.0f
    };

    Material softBlue {
            vec3(.2f,.2f,1),
            vec3(.0f,.2f,.0f),
            vec3(.7f),
            10.0f
    };

    Material solidGreen {
            vec3(.2f,1,.2f),
            vec3(.9f,.9f,.9f),
            vec3(.9f),
            100.0f
    };

    Material softOrange {
            vec3(.8f,.5f,.2f),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            10.0f
    };

    Vehicle defaultVehicle(100.0f, .004f, .1f, .3f, Deceleration::slow);

};

#endif //GAME_ENGINE_DEFAULTS_HPP