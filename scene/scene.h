//
// Created by erik on 2/22/16.
//

#ifndef CAMERA_GLEW_SCENE_H
#define CAMERA_GLEW_SCENE_H

#include <map>
#include <vector>
#include "../actor/actor.h"

class Scene {
private:
    map<string, Actor *> stereotypes;
    vector<Actor *> actors;
public:
    void add_actor(Actor *);
    void add_stereotype(string, Actor *);
    Actor * stereotype(string) const;
    void update();
    void render();
};


#endif //CAMERA_GLEW_SCENE_H
