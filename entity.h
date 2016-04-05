//
// Created by Erik on 3/15/2016.
//

#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H

#include "engine.h"
#include "render_part.h"

class Entity {
protected:
    vec3 m_position;
    vec3 m_rotation;
    vec3 m_scale;
    RenderPart m_renderPart;
public:
    Entity () {}

    Entity (vec3 pos, vec3 rot, vec3 scale, RenderPart r) : m_position(pos), m_rotation(rot), m_scale(scale), m_renderPart(r) { }

    virtual void update (int time_elapsed) {}

    void render () const;

    friend class SteeringBehaviours;
};

#endif //GAME_ENGINE_ENTITY_H
