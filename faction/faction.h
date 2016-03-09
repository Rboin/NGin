//
// Created by erik on 2/22/16.
//

#ifndef SNOWMENS_FACTION_H
#define SNOWMENS_FACTION_H

#include <vector>
#include "../actor/actor.h"

#define FACTION_SNOWMEN 1
#define FACTION_OUTLAW 2

using namespace std;

class Faction {
private:
    vector<Faction*> enemies;
public:
    explicit Faction() {}
    void (*on_hostile_near)(Actor);
    void hostile_to(Faction *f) { enemies.push_back(f); }
    void make_peace(Faction *f);
};

#endif //SNOWMENS_FACTION_H
