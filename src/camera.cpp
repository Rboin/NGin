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

#include <iostream>
#include "output.h"

using namespace Output;

std::map<KeyEvent*, output_f> Output::key_registry;
std::map<KeyEvent*, std::pair<MouseEvent, output_f>> Output::mouse_registry;

void forward(Camera&, const KeyEvent*) {
    std::cout << "FORWAAAARD!!" << std::endl;
}

void backward(Camera&, const KeyEvent*) {

}

void left(Camera&, const KeyEvent*) {

}

void right(Camera&, const KeyEvent*) {

}

void up(Camera&, const KeyEvent*) {

}

void down(Camera&, const KeyEvent*) {

}

void pitch(Camera&, const KeyEvent*) {

}

void yaw(Camera&, const KeyEvent*) {

}

void roll(Camera&, const KeyEvent*) {

}

void initOutput() {
    KeyEvent* k = new KeyEvent;
    k->key = 'w';
    key_registry[k] = forward;
}
