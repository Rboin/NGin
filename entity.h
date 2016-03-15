//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_ENTITY_H
#define SNOWMENS_ENTITY_H

#include "engine.h"

class Entity {
public:
    vec4 m_position;
    vec4 m_rotation;
    vec4 m_scale;
public:
    Entity () {}

    Entity (vec4 pos, vec4 rot, vec4 scale) : m_position(pos), m_rotation(rot), m_scale(scale) { }

    virtual void update (int time_elapsed) = 0;

    virtual void render () const = 0;

    friend class SteeringBehaviours;
};

#endif //SNOWMENS_ENTITY_H
