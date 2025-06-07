#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<memory>
#include<algorithm>
#include "campaign.h"
#include "hero.h"
#include "monster.h"
using namespace std; 

Campaign::Campaign(string name, unsigned min_level) : name{name}, min_level{min_level} {
    if (name.empty()) throw runtime_error("Empty name");
    if (min_level <= 0) throw runtime_error("Wrong Min Level");
} 
void Campaign::add_hero(shared_ptr<Hero> h){
    if(!h) throw runtime_error ("No hero");
    unsigned id = h->get_id();
    if (heroes.find(id) != heroes.end()) throw runtime_error ("Hero exists");
    if (h->get_level() < min_level) throw runtime_error ("Wrong level");
    
    heroes[id] = h;

}

void Campaign::encounter_monster (unsigned id, Monster& m){
    auto it = heroes.find(id);
    if(it == heroes.end()) return;

    shared_ptr<Hero> h = it->second.lock();
    if(!h) return;

    bool won = h->fight(m);
    if (won) h->level_up();
}

unsigned Campaign::remove_dead_and_expired() {
    unsigned count = 0;
    for (auto it = heroes.begin(); it != heroes.end(); ) {
        auto hero_ptr = it->second.lock();
        if (!hero_ptr || hero_ptr->get_current_hp() == 0) {
            it = heroes.erase(it);
            ++count;
        } else ++it;
    }
    return count;
}

ostream& Campaign::print(ostream& o) const {
    o << "[" << name << " Campaign, Min_Level " << min_level << ", {";
    bool first = true;

    for (const auto& [id, weak_h] : heroes) {
        auto h = weak_h.lock();
        if (!h) continue;

        if (!first) o << ", ";
        o << *h;  
        first = false;
    }
    return o << "}]";
}


ostream& operator<<(ostream& o, const Campaign& p){
    return p.print(o);
}