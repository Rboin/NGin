//
// Created by Erik on 3/10/2016.
//

#include "engine.h"
#include "render/render.h"

void truncate(vec4& v, float m) {
    if(v.x > m) v.x = m;
    if(v.y > m) v.y = m;
    if(v.z > m) v.z = m;
    if(v.x < -m) v.x = -m;
    if(v.y < -m) v.y = -m;
    if(v.z < -m) v.z = -m;
}

Vehicle::Vehicle () {
    m_pSteering = new SteeringBehaviours(*this);
    m_position = vec4(5,-1.3,-5,1);
    m_speed = .003f;
    m_mass = 1.3f;
    m_force = .1f;
    m_turn_rate = .3f;
    m_pSteering->m_panic_distance = 3.0f;
    m_pSteering->m_arrive_on = true;
    m_pSteering->m_seek_on = false;
    m_pSteering->m_flee_on = true;

    m_pSteering->set_target(vec4(-5, -1.3f, -5, 1));
}

Vehicle::~Vehicle () {
    if(m_pSteering)
        delete m_pSteering;
}

void Vehicle::update (int time_elapsed) {
    vec4 steeringForce = m_pSteering->calc();

    vec4 acceleration = steeringForce / m_mass;

    m_velocity += acceleration * time_elapsed;

    truncate(m_velocity, m_speed);

    m_position += m_velocity * time_elapsed;

    float dist = length(m_velocity);

    if(dist > 0.000001f) {

        m_heading = normalize(m_velocity);

        m_side.y = (atan2(m_heading.x, m_heading.z) * (180.0f / 3.1415926f)) + 180.0f;

    }

}

void Vehicle::render () const {
    render_snowmen(vec3(m_position), vec3(m_side));
}
