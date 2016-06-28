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

#include <ngin.h>
#include "init.h"

#include <GL/freeglut.h>
#include <iostream>

using namespace std;

UI::Window UI::window;

string getSection(FILE* f, bool open = false) {
    char c = fgetc(f);
    if (c == '[') {
        return getSection(f, true);
    } else if (c == ']') {
        return "";
    } else if (open) {
        return c + getSection(f, open);
    }
    return getSection(f);
}

string getKey(FILE* f) {
    char c = fgetc(f);
    if (c == '=') {
        return "";
    } else if (c == '\n') {
        return getKey(f);
    } else if (c == '[') {
        return "[";
    }
    return c + getKey(f);
}

string getValue(FILE* f) {
    char c = fgetc(f);
    if (c == '\n') {
        return "";
    } else {
        return c + getValue(f);
    }
}

void parse_window(FILE* f) {
    string key = getKey(f);
    if (key == "[") {
        return;
    } else if (key == "title") {
        UI::window.title = getValue(f);
    } else if (key == "resolution") {
        bool passedX;
        string w, h;
        for (auto c : getValue(f)) {
            if (c == 'x') {
                passedX = true;
                continue;
            }
            if (passedX)
                h += c;
            else
                w += c;
        }
        UI::window.resolution.first = stoi(w);
        UI::window.resolution.second = stoi(h);
    } else if (key == "fullscreen") {
        UI::window.fullscreen = (getValue(f) != "0");
    }
    return parse_window(f);
}

void parse_keys(FILE* f) {

}

void parse_config() {
    FILE* f = fopen("games/preview/config.ini", "r");
    if (f) {

        string section = getSection(f);
        if (section == "WINDOW") {
            parse_window(f);
        } else if (section == "KEYS") {
            parse_keys(f);
        }

        section = getSection(f, true);
        if (section == "WINDOW") {
            parse_window(f);
        } else if (section == "KEYS") {
            parse_keys(f);
        }

        cout << UI::window.title << endl;
        fclose(f);
    }
}

void NGin::init(int argc, char** argv, std::string game) {
    parse_config();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow(UI::window.title.c_str());

    glutSetCursor(GLUT_CURSOR_NONE);
    initOutput();

    glewInit();

    initShaders();
}
