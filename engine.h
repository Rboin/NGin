//
// Created by Erik on 3/8/2016.
//

#ifndef SNOWMENS_ENGINE_H
#define SNOWMENS_ENGINE_H

#define GLM_FORCE_RADIANS

#include <iostream>
#include <vector>

// OpenGL
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

void truncate (vec4 &, float);

class World;

class Entity;

class Obstacle;

class MovingEntity;

class Vehicle;

class SteeringBehaviours;

#endif //SNOWMENS_ENGINE_H