//
// Created by Erik on 3/10/2016.
//

#include "engine.h"

MovingEntity::MovingEntity(float mass, float speed, float force, float turn_rate) : Entity() {
    m_mass = mass;
    m_speed = speed;
    m_force = force;
    m_turn_rate = turn_rate;
}