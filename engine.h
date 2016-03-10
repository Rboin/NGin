//
// Created by Erik on 3/8/2016.
//

#ifndef SNOWMENS_ENGINE_H
#define SNOWMENS_ENGINE_H

#include <iostream>
#include <vector>

// OpenGL
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

void truncate(vec4&, float);

class World;
class Entity;
class MovingEntity;
class Vehicle;
class SteeringBehaviours;


class World {
private:
    std::vector<Entity*> m_entities;

public:
    void update(int time_elapsed);
    void render() const;
};


class Entity {
private:
    static int current_id;
protected:
    vec4 m_position;
    vec4 m_rotation;
public:
    void update(int time_elapsed);
    void render() const;
    friend class SteeringBehaviours;
};


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

    void update(int time_elapsed);
    void render() const;
    friend class SteeringBehaviours;
};


class Vehicle : public MovingEntity {
private:
    SteeringBehaviours * m_pSteering = NULL;
public:
    Vehicle();
    ~Vehicle ();

    void update(int time_elapsed);
    void render() const;
    friend class SteeringBehaviours;
};


enum Deceleration {
    slow = 3,
    normal = 2,
    fast = 1
};


class SteeringBehaviours {
public:
    bool m_seek_on;
    bool m_flee_on;
    bool m_arrive_on;

    float m_panic_distance;

    vec4 m_cur_tar;
private:
    Vehicle * m_pVehicle;

    vec4 seek(vec4&);
    vec4 flee(vec4&);
    vec4 arrive(vec4&, Deceleration);
public:
    SteeringBehaviours(Vehicle &v) : m_pVehicle(&v) {}

    vec4 calc();
    vec4 forward_comp();
    vec4 side_comp();

    void set_path();
    void set_target(vec4);

};

#endif //SNOWMENS_ENGINE_H