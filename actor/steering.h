//
// Created by erik on 2/29/16.
//

#ifndef CAMERA_GLEW_STEERING_H
#define CAMERA_GLEW_STEERING_H

#define MAX_FORCE 0.1f
#define MAX_VELOCITY 0.35f

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;
using namespace std;

class Steering {
private:
    float m_mass;
public:
    vec3 m_position, m_look, m_target, m_velocity;
    Steering(float mass, vec3 pos, vec3 look) : m_mass(mass), m_position(pos), m_look(look) {}
    void move();

    void seek(vec3 target);
    void flee(vec3 from);
    void wander();
    void arrival();
private:

};


#endif //CAMERA_GLEW_STEERING_H
