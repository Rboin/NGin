//
// Created by erik on 2/22/16.
//

#ifndef CAMERA_GLEW_SCENE_H
#define CAMERA_GLEW_SCENE_H

#include <vector>
#include "actor/actor.h"

class scene {
private:
    vector<actor*> actors;
public:
    void add_actor(actor*);
    void update();
    void render();
};


#endif //CAMERA_GLEW_SCENE_H
