#ifndef CAMPAIGN_H
#define CAMPAIGN_H
#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<memory>
#include<algorithm>
#include "hero.h"
#include "monster.h"
using namespace std;

class Campaign {
    string name;
    map<unsigned, weak_ptr<Hero>> heroes;
    unsigned min_level;
public:
    Campaign();
    Campaign(string name = {}, unsigned min_level = 1); 
    void add_hero(shared_ptr<Hero> h);
    void encounter_monster (unsigned id, Monster& m);
    unsigned remove_dead_and_expired();
    ostream& print(ostream& o) const;
};

ostream& operator<<(ostream& o, const Campaign& p);

#endif