//
// Created by erik on 2/21/16.
//

#ifndef CAMERA_GLEW_ORGANISM_H
#define CAMERA_GLEW_ORGANISM_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../faction/faction.h"

using namespace std;
using namespace glm;

class Actor {
private:
    float mass, max_velocity, max_speed = 0.05;
    vec3 position, velocity, look, target;
public:
    int faction;
    Actor (int f, float m, float mv, vec3 p, vec3 l, void (*r) (vec3, vec3))
            : faction(f),
              mass(m),
              max_velocity(mv),
              position(p),
              target(p),
              look(l),
              render(r) {};
    void set_target(vec3 t);
    void (*render) (vec3,vec3);
    void update(vector<Actor *> near_actors);
    vec3 pos() {return position;}
    vec3 angle() {return look;}
};

//TODO diferentieren van opengl render

#endif //CAMERA_GLEW_ORGANISM_H
