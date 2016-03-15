//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_WORLD_H
#define SNOWMENS_WORLD_H

#include "maze/maze.h"

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


class MazeWorld : public World {
private:
    Maze * m_pMaze;
public:
    MazeWorld();
    MazeWorld(int,int);
    ~MazeWorld ();
};

#endif //SNOWMENS_WORLD_H
