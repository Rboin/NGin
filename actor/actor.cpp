//
// Created by erik on 2/21/16.
//

#include "actor.h"

vec3 truncate(vec3 v, float cap) {
    vec3 n;

    if (v.x > cap) n.x = cap;
    else if (v.x < -cap) n.x = -cap;
    else n.x = v.x;
    if (v.y > cap) n.y = cap;
    else if (v.y < -cap) n.y = -cap;
    else n.y = v.y;
    if (v.z > cap) n.z = cap;
    else if (v.z < -cap) n.z = -cap;
    else n.z = v.z;
    return n;
}

void Actor::update(vector<Actor *> actors) {

    if (m_faction == FACTION_SNOWMEN) {

        float prev_dist = 1000;
        vec3 nearest;

        for(vector<Actor *>::iterator it = actors.begin(); it != actors.end(); ++it) {
            vec3 from = (*it)->m_position;
            vec3 distance = from - m_position;
            vec3 mult = distance * distance;
            float dist = sqrtf(mult.x + mult.y);
            if (dist < 5.0f) {
                // in range
                if ((*it)->m_faction == FACTION_OUTLAW) {
                    // flee
                    nearest = m_position - distance;
                    break;
                } else if ((*it)->m_faction == FACTION_SNOWMEN) {
                    // seek friend if not too close
                    if (trunc(m_position) != trunc(from) && dist < prev_dist) {
                        vec3 ts = trunc(m_position - from);
                        nearest = from;
                        prev_dist = dist;
                    }
                }

            }
        }

//        cout << "setting target to " << nearest.x << ' ' << nearest.y << endl;
//        cout << "current is " << m_position.x << ' ' << m_position.y << endl << endl;

        m_target = nearest;

    } else if (m_faction == FACTION_OUTLAW) {

    }

    // to target
    if (m_position != m_target) {
        vec3 desired_velocity = glm::normalize(m_target - m_position) * m_max_velocity;
        vec3 steering = desired_velocity - m_velocity;
        steering = truncate(steering, 0.0055f);
        steering /= m_mass;

        m_velocity = truncate(m_velocity + steering, m_max_speed);
        // update camera
        m_look.z = (atan2(m_velocity.y, m_velocity.x) * (180.0f / 3.1415926f)) + 90.0f;
        // update the m_position
        m_position += m_velocity;
    }

}

void Actor::set_target(vec3 t) {
    m_target = t;
}
