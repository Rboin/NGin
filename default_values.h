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
#include "mesh.h"

namespace defaults {

	const vec4 color_black(0,0,0,1);

    const Material solidRed {
            vec3(1,.2f,.2f),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            100.0f
    };

	const Material softBlue {
            vec3(.2f,.2f,1),
            vec3(.0f,.2f,.0f),
            vec3(.7f),
            10.0f
    };

	const Material solidGreen {
            vec3(.2f,1,.2f),
            vec3(.9f,.9f,.9f),
            vec3(.9f),
            100.0f
    };

	const Material softOrange {
            vec3(.8f,.5f,.2f),
            vec3(.2f,.2f,.2f),
            vec3(.7f),
            10.0f
    };

	const vec3 UP = vec3(0, 1, 0);
	const vec3 SCALE = vec3(.1f);

};

#endif //GAME_ENGINE_DEFAULTS_HPP