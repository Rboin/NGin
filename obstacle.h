//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_OBSTACLE_H
#define SNOWMENS_OBSTACLE_H

#include "entity.h"
#include "render/render.h"

class Obstacle : public Entity {
public:
    Obstacle (vec4 pos, vec4 rot, vec4 scale);
    void update (int time_elapsed);
    void render () const;
};

#endif //SNOWMENS_OBSTACLE_H
