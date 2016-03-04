//
// Created by erik on 2/29/16.
//

#include "faction.h"

void Faction::make_peace(Faction *f) {

    vector<Faction*>::iterator it = enemies.begin();

    while(*it != f && ++it != enemies.end());

    if (it != enemies.end())
        enemies.erase(it);

}
