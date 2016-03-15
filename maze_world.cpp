//
// Created by Erik on 3/15/2016.
//

#include "world.h"

MazeWorld::MazeWorld () : MazeWorld(10,10) {}

MazeWorld::MazeWorld (int width, int height) : World() {
    m_pMaze = new Maze(width, height);

    vec4 wall_size(vec4(2, 2, .3f, 1));

    // top
    for (int j = 0; j < m_pMaze->get_width(); j++) {
        if(j == m_pMaze->get_width()/2)
            continue;
        Obstacle * wall = new Obstacle(vec4(j*2-m_pMaze->get_width(), 0, -1-m_pMaze->get_height(), 0), vec4(), wall_size);
        add_obstacle(wall);
    }

    // left
    for (int j = 0; j < m_pMaze->get_height(); j++) {
        if(j == m_pMaze->get_height()/2)
            continue;
        Obstacle * wall = new Obstacle(vec4(-1-m_pMaze->get_width(), 0, j*2-m_pMaze->get_height(), 0), vec4(0,90,0,0), wall_size);
        add_obstacle(wall);
    }

    for (int i = 0; i < m_pMaze->get_height()*2; i+=2) {

        for (int j = 0; j < m_pMaze->get_width()*2; j+=2) {

            int p = ((i/2) * m_pMaze->get_width()) + (j/2);

            // bottom is not open
            if(!m_pMaze->is_open(p, false) && !(j == m_pMaze->get_width() && i == m_pMaze->get_height()*2-2)) {
                Obstacle * wall = new Obstacle(vec4(j-m_pMaze->get_width(), 0, i+1-m_pMaze->get_height(), 0), vec4(), wall_size);
                add_obstacle(wall);
            }

            // right is not open
            if(!m_pMaze->is_open(p, true) && !(j == m_pMaze->get_width()*2-2 && i == m_pMaze->get_height())) {
                Obstacle * wall = new Obstacle(vec4(j+1-m_pMaze->get_width(), 0, i-m_pMaze->get_height(), 0), vec4(0,90,0,0), wall_size);
                add_obstacle(wall);
            }

        }

    }
}

MazeWorld::~MazeWorld () {
    delete m_pMaze;
}