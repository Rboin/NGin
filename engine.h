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

void truncate (vec4 &, float);

class World;

class Entity;

class Obstacle;

class MovingEntity;

class Vehicle;

class SteeringBehaviours;

enum Deceleration {
    slow = 3,
    normal = 2,
    fast = 1
};


typedef std::vector<Vehicle *>::iterator vit;

class World {
private:
    vec2 m_ground;
    std::vector<Vehicle *> m_vehicles;

public:
    void update (int time_elapsed);

    void render ();

    void reset ();

    void add_vehicle (Vehicle &);
};


class Entity {
private:
    static int current_id;
protected:
    vec4 m_position;
    vec4 m_rotation;
public:
    Entity () {}

    Entity (vec4 pos, vec4 rot) : m_position(pos), m_rotation(rot) { }

    virtual void update (int time_elapsed) = 0;

    virtual void render () const = 0;

    friend class SteeringBehaviours;
};


class Obstacle : Entity {
public:
    Obstacle (vec4 pos, vec4 rot) : Entity(pos, rot) { }
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
    MovingEntity () {}

    MovingEntity (float, float, float, float);

    MovingEntity (vec4 pos, vec4 rot, MovingEntity &stereotype) : Entity(pos, rot) {
        m_mass = stereotype.m_mass;
        m_speed = stereotype.m_speed;
        m_force = stereotype.m_force;
        m_turn_rate = stereotype.m_turn_rate;
    }

    virtual void update (int time_elapsed) = 0;

    virtual void render () const = 0;

    friend class SteeringBehaviours;
};


class Vehicle : public MovingEntity {
private:
    SteeringBehaviours *m_pSteering = NULL;
    Deceleration m_deceleration;
public:
    Vehicle ();

    Vehicle (float, float, float, float, Deceleration);

    Vehicle (vec4 pos, vec4 rot, Vehicle &v);

    ~Vehicle ();

    void set_deceleration (Deceleration &d);

    void update (int time_elapsed);

    void render () const;

    SteeringBehaviours *steer () { return m_pSteering; }

    friend class SteeringBehaviours;
};


class SteeringBehaviours {
public:
    bool m_seek_on;
    bool m_flee_on;
    bool m_arrive_on;

    float m_panic_distance;

    vec4 m_cur_tar;
private:
    Vehicle *m_pVehicle;

    vec4 seek (vec4 &);

    vec4 flee (vec4 &);

    vec4 arrive (vec4 &, Deceleration);

public:
    SteeringBehaviours (Vehicle &v) : m_pVehicle(&v) { }

    vec4 calc ();

    vec4 forward_comp ();

    vec4 side_comp ();

    void set_path ();

    void set_target (vec4);

};

#endif //SNOWMENS_ENGINE_H