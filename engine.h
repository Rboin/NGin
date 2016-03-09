//
// Created by Erik on 3/8/2016.
//

#ifndef SNOWMENS_ENGINE_H
#define SNOWMENS_ENGINE_H

#include <vector>

// OpenGL
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;


class World {
private:
    std::vector<Entity> entities;

public:
    void update(int time_elapsed);
    void render() const;
};


class Entity {
private:
    static int current_id = 0;
protected:
    vec4 position;
    vec4 rotation;
public:
    void update(int time_elapsed);
    void render() const;
};


class MovingEntity : public Entity {
protected:
    // maximum variables
    float m_mass;
    float m_speed;
    float m_force;
    float m_turn_rate;

    vec4 velocity;
    vec4 heading;
public:

    void update(int time_elapsed);
    void render() const;
};


class Vehicle : public MovingEntity {
public:

    void update(int time_elapsed);
    void render() const;
};

class SteeringBehaviours {
public:
    bool seek_on, flee_on, arrive_on;
private:
    vec4 seek(vec4&);
    vec4 flee(vec4&);
    vec4 arrive(vec4&);
public:
    vec4 calc();
    vec4 forward_comp();
    vec4 side_comp();

    void set_path();
    void set_target(vec4);

};

#endif //SNOWMENS_ENGINE_H