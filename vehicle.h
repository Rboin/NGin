//
// Created by Erik on 3/15/2016.
//

#ifndef GAME_ENGINE_VEHICLE_H
#define GAME_ENGINE_VEHICLE_H

#include "steering.h"
#include "moving_entity.h"

class Vehicle : public MovingEntity {
private:
    SteeringBehaviours *m_pSteering = NULL;
    Deceleration m_deceleration;
public:

    Vehicle (float, float, float, float, Deceleration);

    Vehicle (vec3, vec3, vec3, Vehicle &, RenderPart);

    ~Vehicle ();

    void set_deceleration (Deceleration &d);

    void update (int time_elapsed);

    SteeringBehaviours *steer () { return m_pSteering; }

    friend class SteeringBehaviours;
};

#endif //GAME_ENGINE_VEHICLE_H
