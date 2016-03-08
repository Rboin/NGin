//
// Created by Erik on 3/8/2016.
//

#ifndef SNOWMENS_KEYBOARD_H
#define SNOWMENS_KEYBOARD_H

#define QUIT 27

#define FULL_SCREEN 'f'

#define FORWARD     'w'
#define LEFT        'a'
#define BACKWARD    's'
#define RIGHT       'd'
#define UP          'x'
#define DOWN        'z'

namespace keyboard {

    float forward, strafe, upward;

    void press_key (unsigned char, int, int);

    void release_key (unsigned char, int, int);

}

#endif //SNOWMENS_KEYBOARD_H
