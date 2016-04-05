//
// Created by Erik on 3/15/2016.
//

#ifndef GAME_ENGINE_MOVING_ENTITY_H
#define GAME_ENGINE_MOVING_ENTITY_H

#include "entity.h"

class MovingEntity : public Entity {
protected:
    // maximum variables
    float m_mass;
    float m_speed;
    float m_force;
    float m_turn_rate;

    vec3 m_velocity;
    vec3 m_heading;
    vec3 m_side;
public:
    MovingEntity () {}

    MovingEntity (float, float, float, float);

    MovingEntity (vec3 pos, vec3 rot, vec3 scale, MovingEntity &stereotype, RenderPart r) : Entity(pos, rot, scale, r) {
        m_mass = stereotype.m_mass;
        m_speed = stereotype.m_speed;
        m_force = stereotype.m_force;
        m_turn_rate = stereotype.m_turn_rate;
    }

    friend class SteeringBehaviours;
};

#endif //GAME_ENGINE_MOVING_ENTITY_H
