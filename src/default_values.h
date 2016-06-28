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

#include <ngin.h>
#include "controls.h"

namespace defaults {

    glm::vec4 color_black(0,0,0,1);

    Camera camera = {
            45.0f,  // viewing angle
            800.0f, // viewing width
            600.0f, // viewing height
            0.1f,   // near plane
            100.0f, // far plane
            0.3f,   // scroll speed
            0.3f,   // mouse speed
            0.5f,   // movement speed
            glm::vec3(0, 0, 0), // position
            glm::vec3(0, 0, 1), // direction
            glm::vec3(4),// distance of target
    };

    NGin::Model::Material solidRed {
            glm::vec3(1,.2f,.2f),
            glm::vec3(.2f,.2f,.2f),
            glm::vec3(.7f),
            10.0f
    };

    NGin::Model::Material softBlue {
            glm::vec3(.2f,.2f,1),
            glm::vec3(1, 1, 1),
            glm::vec3(.7f),
            10.0f
    };

    NGin::Model::Material solidGreen {
            glm::vec3(.2f,1,.2f),
            glm::vec3(.2f,.2f,.2f),
            glm::vec3(.9f),
            10.0f
    };

    NGin::Model::Material softOrange {
            glm::vec3(.8f,.5f,.2f),
            glm::vec3(.2f,.2f,.2f),
            glm::vec3(.0f, 1, .0f),
            10.0f
    };

};

#endif //GAME_ENGINE_DEFAULTS_HPP
