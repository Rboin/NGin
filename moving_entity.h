//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_MOVING_ENTITY_H
#define SNOWMENS_MOVING_ENTITY_H

#include "entity.h"

class MovingEntity : public Entity {
protected:
    // maximum variables
    float m_mass;
    float m_speed;
    float m_force;
    float m_turn_rate;

    vec4 m_velocity;
    vec4 m_heading;
    vec4 m_side;
public:
    MovingEntity () {}

    MovingEntity (float, float, float, float);

    MovingEntity (vec4 pos, vec4 rot, vec4 scale, MovingEntity &stereotype) : Entity(pos, rot, scale) {
        m_mass = stereotype.m_mass;
        m_speed = stereotype.m_speed;
        m_force = stereotype.m_force;
        m_turn_rate = stereotype.m_turn_rate;
    }

    virtual void update (int time_elapsed) = 0;

    virtual void render () const = 0;

    friend class SteeringBehaviours;
};

#endif //SNOWMENS_MOVING_ENTITY_H
