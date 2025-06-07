#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<algorithm>
#include "monster.h"
using namespace std; 

Monster::Monster(string name, unsigned health, unsigned attack) : 
name {name}, health {health}, attack {attack} {
    if (health == 0) throw runtime_error("Wrong health");
    if (name.empty()) throw runtime_error("Empty name");
    if (attack <= 0) throw runtime_error("Wrong attack number");
}

string Monster::get_name() {
    return name;
}

unsigned Monster::get_health() {
        return health;
    }
unsigned Monster::get_attack() {
        return attack;
    }

void Monster::take_damage(unsigned dmg) {
        unsigned calc_dmg = calculate_damage(dmg); 
        if (health <= calc_dmg ) health = 0;
        else health -= calc_dmg;
    }

bool Monster::is_dead() const {
        return health == 0;
    };

ostream& Monster::print (ostream& o) const {
    o << "[" << name << ", " << health << " HP, " << attack << " ATK";
    o << additional_information() << "]";
    return o;  
}

ostream& operator<< (ostream& o, const Monster& h) {
    return h.print(o);
}

Elite_Monster::Elite_Monster (string name, unsigned health, unsigned attack, unsigned defense) : 
    Monster(name, health, attack), defense{defense} {
        if (defense == 0) throw runtime_error ("Wrong defense");
    }

unsigned Elite_Monster::calculate_damage(unsigned dmg) const {
    if (dmg <= defense) return 0;
    return dmg - defense;
}

string Elite_Monster::additional_information() const {
    return ", " + to_string(defense) + " DEF";
}


Standard_Monster::Standard_Monster (string name, unsigned health, unsigned attack) :
    Monster(name, health, attack) {}

unsigned Standard_Monster::calculate_damage(unsigned dmg) const {
    return dmg;
}

string Standard_Monster::additional_information() const {
    return {};
}