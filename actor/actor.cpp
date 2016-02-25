//
// Created by erik on 2/21/16.
//

#include "Actor.h"

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

    if (faction == FACTION_SNOWMEN) {

        float prev_dist = 1000;
        vec3 nearest;

        for(vector<Actor *>::iterator it = actors.begin(); it != actors.end(); ++it) {
            vec3 from = (*it)->position;
            vec3 distance = from - position;
            vec3 mult = distance * distance;
            float dist = sqrtf(mult.x + mult.y);
            if (dist < 15.0f) {
                // in range
                if ((*it)->faction == FACTION_OUTLAW) {
                    // flee
                    nearest = position - distance;
                    break;
                } else if ((*it)->faction == FACTION_SNOWMEN) {
                    // seek friend
                    if (dist < prev_dist) {
                        cout << "new distance " << dist << endl;
                        nearest = from;
                        prev_dist = dist;
                    }
                }

            }
        }

        target = nearest;

    } else if (faction == FACTION_OUTLAW) {

    }

    // to target
    if (position != target) {
        vec3 desired_velocity = glm::normalize(target - position) * max_velocity;
        vec3 steering = desired_velocity - velocity;
        steering = truncate(steering, 0.0055f);
        steering /= mass;

        velocity = truncate(velocity + steering, max_speed);
        // update camera
        look.z = (atan2(velocity.y, velocity.x) * (180.0f / 3.1415926f)) + 90.0f;
        // update the position
        position += velocity;
    }

}

void Actor::set_target(vec3 t) {
    target = t;
}
