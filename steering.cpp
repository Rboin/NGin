//
// Created by Erik on 3/9/2016.
//

#include "vehicle.h"

vec4 SteeringBehaviours::calc () {
    vec4 steeringForce;

    if(is_status(SEEK_ON))
        steeringForce += seek(m_cur_tar);

    if(is_status(ARRIVE_ON))
        steeringForce += arrive(m_cur_tar, m_pVehicle->m_deceleration);

    return steeringForce;
}

vec4 SteeringBehaviours::forward_comp () {
    return vec4();
}

vec4 SteeringBehaviours::side_comp () {
    return vec4();
}

void SteeringBehaviours::set_path () {

}

void SteeringBehaviours::set_target (vec4 t) {
    m_cur_tar = t;
}

vec4 SteeringBehaviours::seek (vec4 &target) {
    vec4 desired_velocity = normalize(target - m_pVehicle->m_position)
                            * m_pVehicle->m_speed;

    return desired_velocity - m_pVehicle->m_velocity;
}

vec4 SteeringBehaviours::flee (vec4 &target) {

    float dist = distance(m_pVehicle->m_position, target);

    if(dist > m_panic_distance)
        return vec4();

    vec4 desired_velocity = normalize(m_pVehicle->m_position - target)
                            * m_pVehicle->m_speed;

    return desired_velocity - m_pVehicle->m_velocity;
}

vec4 SteeringBehaviours::arrive (vec4 &target, Deceleration deceleration) {

    vec4 toTarget = target - m_pVehicle->m_position;

    float distance = length(toTarget);

    if (distance > 0) {

        const float decelerationTweaker = .005f;

        float speed = distance / ((float) deceleration / decelerationTweaker);

        speed = min(speed, m_pVehicle->m_speed);

        vec4 desired_velocity = toTarget * speed / distance;

        return desired_velocity - m_pVehicle->m_velocity;
    }

    return vec4();
}

void SteeringBehaviours::set_status (int s) {
    m_status = s;
}

bool SteeringBehaviours::is_status (int s) {
    return (m_status & s) == 0;
}
