//
// Created by Erik on 3/10/2016.
//

#include "vehicle.h"

void truncate (vec4 &v, float m) {
    if (v.x > m) v.x = m;
    if (v.y > m) v.y = m;
    if (v.z > m) v.z = m;
    if (v.x < -m) v.x = -m;
    if (v.y < -m) v.y = -m;
    if (v.z < -m) v.z = -m;
}

Vehicle::Vehicle (vec4 pos, vec4 rot, vec4 scale, Vehicle &v) : MovingEntity(pos, rot, scale, v) {
    m_pSteering = new SteeringBehaviours(*this);
    m_deceleration = v.m_deceleration;
}

Vehicle::Vehicle (float mass, float speed, float force, float turn_rate, Deceleration d) : MovingEntity() {
    m_mass = mass;
    m_speed = speed;
    m_force = force;
    m_turn_rate = turn_rate;
    m_deceleration = d;
}

Vehicle::~Vehicle () {
    if (m_pSteering)
        delete m_pSteering;
}

void Vehicle::update (int time_elapsed) {
    vec4 steeringForce = m_pSteering->calc();

    vec4 acceleration = steeringForce / m_mass;

    m_velocity += acceleration * (float) time_elapsed;

    truncate(m_velocity, m_speed);

    m_position += m_velocity * (float) time_elapsed;

    float dist = length(m_velocity);

    if (dist > 0.000001f) {

        m_heading = normalize(m_velocity);

        m_side = glm::perp(m_heading, vec4());

        m_rotation.y = (float) (atan2(m_heading.x, m_heading.z) * (180.0f / 3.1415926f)) + 180.0f;

    }

}

void Vehicle::render () const {
    render_snowmen(vec3(m_position), vec3(m_rotation));
}

void Vehicle::set_deceleration (Deceleration &d) {
    m_deceleration = d;
}
