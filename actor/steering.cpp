//
// Created by erik on 2/29/16.
//

#include "steering.h"

void yield(vec3 &v, float max) {
    float i = max / v.length();
    i = i < 1.0f ? i : 1.0f;
    mat4 scaleMat = scale(vec3(i));
    vec4 nv = scaleMat * vec4(v, 1);
    v = vec3(nv);
}

void Steering::move() {

    vec3 desired_velocity = normalize(m_target - m_position) * MAX_VELOCITY;

    vec3 steering = desired_velocity - m_velocity;

    yield(steering, MAX_FORCE);

//    std::cout << steering.x << ' ' << steering.y << std::endl;

    mat4 scaleMat = scale(vec3(1/m_mass));

    steering = vec3(scaleMat * vec4(steering, 1));

    m_velocity += steering;
    //yield(m_velocity, MAX_VELOCITY);

    m_look.z = (atan2(m_velocity.y, m_velocity.x) * (180.0f / 3.1415926f)) + 90.0f;

    m_position += m_velocity;

}

void Steering::seek(vec3 target) {
    m_target = target;
}

void Steering::flee(vec3 from) {
    vec3 distance = from - m_position;
    m_target = m_position - distance;
}

void Steering::wander() {
    vec3 wanderForce, circleCenter, displacement(0, -1, 0);
    mat4 circleRadius = scale(vec3(6.0f));

    circleCenter = vec3(normalize(vec4(m_velocity, 1.0f)));
    circleCenter = vec3(circleRadius * vec4(circleCenter, 1.0f));
    cout << to_string(circleCenter) << endl;

    displacement = vec3(circleRadius * vec4(displacement, 1.0f));

    //set angle
    displacement.x = cos(m_look.z) * displacement.length();
    displacement.y = sin(m_look.z) * displacement.length();

    m_look.z += rand() * 1 - 1 * .5f;

    m_target = circleCenter + displacement;

}

void Steering::arrival() {

}
