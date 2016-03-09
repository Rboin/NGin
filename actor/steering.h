//
// Created by erik on 2/29/16.
//

#ifndef SNOWMENS_STEERING_H
#define SNOWMENS_STEERING_H

#define MAX_FORCE 0.6f
#define MAX_VELOCITY 3.f

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;
using namespace std;

class Steering {
private:
    float   m_mass;

    vec3    *m_position,
            *m_look;
protected:
    vec3    m_target,
            m_velocity;

public:
    Steering(float mass, vec3 *pos, vec3 *look)
            : m_mass(mass),
              m_position(pos),
              m_look(look),
              m_target(*pos + vec3()) {}

    void move();

    void seek(vec3 target);
    void flee(vec3 from);
    void wander();
private:

};


#endif //SNOWMENS_STEERING_H
