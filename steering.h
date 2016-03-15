//
// Created by Erik on 3/15/2016.
//

#ifndef SNOWMENS_STEERING_H
#define SNOWMENS_STEERING_H

#define SEEK_ON     1
#define FLEE_ON     2
#define ARRIVE_ON   4

#include "engine.h"

enum Deceleration {
    slow = 3,
    normal = 2,
    fast = 1
};

class SteeringBehaviours {
public:

    float m_panic_distance;

    vec4 m_cur_tar;
private:
    int m_status;
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

    void set_status(int s);
    bool is_status(int s);

};

#endif //SNOWMENS_STEERING_H
