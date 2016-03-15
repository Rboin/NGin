//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_VEHICLE_H
#define SNOWMENS_VEHICLE_H

#include "steering.h"
#include "moving_entity.h"
#include "render/render.h"

class Vehicle : public MovingEntity {
private:
    SteeringBehaviours *m_pSteering = NULL;
    Deceleration m_deceleration;
public:

    Vehicle (float, float, float, float, Deceleration);

    Vehicle (vec4 pos, vec4 rot, vec4 scale, Vehicle &v);

    ~Vehicle ();

    void set_deceleration (Deceleration &d);

    void update (int time_elapsed);

    void render () const;

    SteeringBehaviours *steer () { return m_pSteering; }

    friend class SteeringBehaviours;
};

#endif //SNOWMENS_VEHICLE_H
