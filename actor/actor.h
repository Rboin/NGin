//
// Created by erik on 2/21/16.
//

#ifndef CAMERA_GLEW_ORGANISM_H
#define CAMERA_GLEW_ORGANISM_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../faction/faction.h"
#include "steering.h"

using namespace std;
using namespace glm;

class Actor {
private:
    float m_mass, m_max_velocity, m_max_speed = 0.002f;
    vec3 m_position, m_velocity, m_look, m_target;
public:
    int m_faction;

    /**
     * Use this constructor to create a stereotype
     */
    Actor (float mass, float max_velocity, void (*r) (vec3, vec3))
            : m_mass(mass), m_max_velocity(max_velocity), render(r) {};

    Actor (int faction, vec3 position, Actor &stereotype)
            : Actor(stereotype.m_mass, stereotype.m_max_velocity, stereotype.render) {
        m_faction = faction;
        m_position = position;
        m_target = position;
    };

    Actor (int faction, vec3 position, vec3 look, Actor &stereotype)
            : Actor(faction, position, stereotype) {
        m_look = look;
    }

    void set_target(vec3 t);
    void (*render) (vec3,vec3);
    void update(vector<Actor *> near_actors);
    vec3 pos() {return m_position;}
    vec3 angle() {return m_look;}
};

#endif //CAMERA_GLEW_ORGANISM_H
