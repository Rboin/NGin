//
// Created by Erik on 3/15/2016.
//

#ifndef GAME_ENGINE_OBSTACLE_H
#define GAME_ENGINE_OBSTACLE_H

#include "entity.h"

class Obstacle : public Entity {
public:
    Obstacle (vec3 pos, vec3 rot, vec3 scale, RenderPart);
    void update (int time_elapsed);
};

#endif //GAME_ENGINE_OBSTACLE_H
