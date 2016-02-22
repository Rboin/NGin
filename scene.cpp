//
// Created by erik on 2/22/16.
//

#include "scene.h"

void scene::add_actor(actor *actor1) {
    actors.push_back(actor1);
}

void scene::update() {

    for(vector<actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->update(actors);
    }

}

void scene::render() {

    for(vector<actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->render((*it)->pos(), (*it)->angle());
    }

}
