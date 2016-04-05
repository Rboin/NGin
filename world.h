//
// Created by Erik on 3/15/2016.
//

#ifndef GAME_ENGINE_WORLD_H
#define GAME_ENGINE_WORLD_H

#include "engine.h"
#include "vehicle.h"
#include "obstacle.h"

typedef std::vector<Vehicle *>::iterator vit;
typedef std::vector<Obstacle *>::iterator oit;

class World {
protected:
    vec2 m_ground;
    std::vector<Vehicle *> m_vehicles;
    std::vector<Obstacle *> m_obstacles;

public:
    World();
    void update (int time_elapsed);

    void render ();

    void reset ();

    void add_vehicle (Vehicle *);
    void add_obstacle(Obstacle *);
};

#endif //GAME_ENGINE_WORLD_H
