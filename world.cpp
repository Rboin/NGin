//
// Created by Erik on 3/10/2016.
//

#include "engine.h"

void World::update (int time_elapsed) {
    // update vehicles
    for(vit it = m_vehicles.begin(); it != m_vehicles.end(); ++it) {
        (*it)->update(time_elapsed);
    }
}

void World::render () {
    // render vehicles
    for(vit it = m_vehicles.begin(); it != m_vehicles.end(); ++it) {
        (*it)->render();
    }
}

void World::reset() {
    m_vehicles.clear();
}

void World::add_vehicle (Vehicle &vehicle) {
    m_vehicles.push_back(&vehicle);
}