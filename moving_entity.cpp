//
// Created by Erik on 3/15/2016.
//

#include "moving_entity.h"

MovingEntity::MovingEntity(float mass, float speed, float force, float turn_rate) : Entity() {
    m_mass = mass;
    m_speed = speed;
    m_force = force;
    m_turn_rate = turn_rate;
}