//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_STEERING_H
#define SNOWMENS_STEERING_H

#include "engine.h"

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

#endif //SNOWMENS_STEERING_H
