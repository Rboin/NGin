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

#ifndef NGIN_OUTPUT_H
#define NGIN_OUTPUT_H

#include "controls.h"
#include <map>
#include <tuple>

namespace Output {

    struct KeyEvent {
        char key;
    };

    enum MouseEvent {
        LEFT_MOUSE_CLICK,
        RIGHT_MOUSE_CLICK,
        MIDDLE_MOUSE_CLICK,
        SCROLL
    };

    //TODO are parameters actually needed?
    typedef void (*output_f) (Camera&, const KeyEvent*);

    extern std::map<KeyEvent*, output_f> key_registry;
    extern std::map<KeyEvent*, std::pair<MouseEvent, output_f>> mouse_registry;

}

#endif //NGIN_OUTPUT_H
