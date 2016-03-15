//
// Created by Erik on 3/15/2016.
//

#include "obstacle.h"

Obstacle::Obstacle (vec4 pos, vec4 rot, vec4 scale) : Entity(pos, rot, scale)  {

}

void Obstacle::update(int time_elapsed) {

};

void Obstacle::render() const {
    render_wall(vec3(m_position), vec3(m_rotation), vec3(m_scale));
};