//
// Created by erik on 4/5/16.
//

#ifndef GAME_ENGINE_MAZE_WORLD_H
#define GAME_ENGINE_MAZE_WORLD_H

#include "world.h"
#include "maze/maze.h"

class MazeWorld : public World {
private:
    Maze * m_pMaze;
public:
    MazeWorld();
    MazeWorld(int,int);
    ~MazeWorld ();
};

#endif //GAME_ENGINE_MAZE_WORLD_H
