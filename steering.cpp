//
// Created by Erik on 3/9/2016.
//

#include "vehicle.h"

vec3 SteeringBehaviours::calc () {
    vec3 steeringForce;

    if(is_status(SEEK_ON))
        steeringForce += seek(m_cur_tar);

    if(is_status(ARRIVE_ON))
        steeringForce += arrive(m_cur_tar, m_pVehicle->m_deceleration);

    return steeringForce;
}

vec3 SteeringBehaviours::forward_comp () {
    return vec3();
}

vec3 SteeringBehaviours::side_comp () {
    return vec3();
}

void SteeringBehaviours::set_path () {

}

void SteeringBehaviours::set_target (vec3 t) {
    m_cur_tar = t;
}

vec3 SteeringBehaviours::seek (vec3 &target) {
    vec3 desired_velocity = normalize(target - m_pVehicle->m_position)
                            * m_pVehicle->m_speed;

    return desired_velocity - m_pVehicle->m_velocity;
}

vec3 SteeringBehaviours::flee (vec3 &target) {

    float dist = distance(m_pVehicle->m_position, target);

    if(dist > m_panic_distance)
        return vec3();

    vec3 desired_velocity = normalize(m_pVehicle->m_position - target)
                            * m_pVehicle->m_speed;

    return desired_velocity - m_pVehicle->m_velocity;
}

vec3 SteeringBehaviours::arrive (vec3 &target, Deceleration deceleration) {

    vec3 toTarget = target - m_pVehicle->m_position;

    float distance = length(toTarget);

    if (distance > 0) {

        const float decelerationTweaker = .005f;

        float speed = distance / ((float) deceleration / decelerationTweaker);

        speed = glm::min(speed, m_pVehicle->m_speed);

        vec3 desired_velocity = toTarget * speed / distance;

        return desired_velocity - m_pVehicle->m_velocity;
    }

    return vec3();
}

void SteeringBehaviours::set_status (int s) {
    m_status = s;
}

bool SteeringBehaviours::is_status (int s) {
    return (m_status & s) == 0;
}
