//
// Created by erik on 2/22/16.
//

#include "scene.h"

void Scene::add_actor(Actor *actor1) {
    actors.push_back(actor1);
}

void Scene::update() {

    for(vector<Actor *>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->update(actors);
    }

}

void Scene::render() {

    for(vector<Actor *>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->render((*it)->pos(), (*it)->angle());
    }

}

void Scene::add_stereotype (string name, Actor *actor1) {
    stereotypes.insert(pair<string, Actor *>(name, actor1));
}

Actor *Scene::stereotype (string name) const {
    return stereotypes.at(name);
}
