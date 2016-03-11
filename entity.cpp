//
// Created by Erik on 3/10/2016.
//

#include "engine.h"
#include "render/render.h"

MovingEntity::MovingEntity(float mass, float speed, float force, float turn_rate) : Entity() {
    m_mass = mass;
    m_speed = speed;
    m_force = force;
    m_turn_rate = turn_rate;
}

Obstacle::Obstacle (vec4 pos, vec4 rot, vec4 scale) : Entity(pos, rot, scale)  {

}

void Obstacle::update(int time_elapsed) {

};

void Obstacle::render() const {
    render_wall(vec3(m_position), vec3(m_rotation), vec3(m_scale));
};