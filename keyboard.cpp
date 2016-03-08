//
// Created by Erik on 3/8/2016.
//

#include <stdlib.h>
#include "keyboard.h"

using namespace keyboard;

void press_key (unsigned char key, int xx, int yy) {
    switch (key) {
        case QUIT:
            exit(0);
        case FULL_SCREEN:
            //glutFullScreen();
            break;
        case FORWARD:
            forward = 1.5;
            break;
        case BACKWARD:
            forward = -1.5;
            break;
        case LEFT:
            strafe = 1.5;
            break;
        case RIGHT:
            strafe = -1.5;
            break;
        case DOWN:
            upward = 1.5;
            break;
        case UP:
            upward = -1.5;
            break;
    }
}

void release_key (unsigned char key, int xx, int yy) {
    switch (key) {
        case FORWARD:
        case BACKWARD:
            forward = 0.0;
            break;
        case LEFT:
        case RIGHT:
            strafe = 0;
            break;
        case UP:
        case DOWN:
            upward = 0;
            break;
    }
}