#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<algorithm>
#include "hero.h"
#include "monster.h"
using namespace std;

unsigned Hero::next_id = 0;

Hero::Hero(string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const map<string, unsigned>& abilities) :
     name {name}, hero_class{hero_class}, hero_species {hero_species}, level {1}, max_hp {max_hp}, current_hp {max_hp}, abilities{abilities} {

    if(name.empty()) throw runtime_error("Empty name"); 
    if(level <= 0 || level > 21 ) throw runtime_error("Wrong level"); 
    if (max_hp <= 0 ) throw runtime_error("Wrong max_hp"); 
    if (current_hp > max_hp) throw runtime_error("Wrong current_hp"); 
    
    vector<string> abilit {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
    
    if (abilities.size() != abilit.size()) throw runtime_error("Wrong abilities"); 
    for (const auto& key : abilit) {
        auto it = abilities.find(key);
        if (it == abilities.end()) throw runtime_error("Missing ability");
        if (it->second == 0 || it->second > 20) throw runtime_error("Invalid value for ability");
    }   
   
    id = next_id++;
    }

unsigned Hero::level_up() {
    if (level<20) level++;
    return level;
}

bool Hero::fight(Monster& m){
    
    vector<unsigned> numbers {};
     for(const auto& h : abilities) {
        numbers.push_back(h.second);
    }
    auto max_n = *max_element(numbers.begin(), numbers.end());
    
    unsigned schaden = level*max_n;

    while (current_hp > 0 && m.get_health() > 0) {
        m.take_damage(schaden);
        if (m.get_health() == 0) break;
        unsigned m_damage =  m.get_attack();
        if (current_hp <= m_damage) current_hp = 0;
        else current_hp -= m_damage;
    } 
    return current_hp > 0; 
}
unsigned Hero::get_id() {
    return id;
}

unsigned Hero::get_level(){
    return level;
}
unsigned Hero::get_current_hp() {
    return current_hp;
}

ostream& Hero::print (ostream& o) const {
o << "[" << id << ", " << name << ", (";
   o << h_class.at(static_cast<int>(hero_class)) << ", ";
   o << h_species.at(static_cast<int>(hero_species)) << ", " << level << "), {";
   bool first = true;
   for (const auto& ch: abilities) {
    if (!first) o << ", ";
    o  << ch.second;
    first = false; 
   }
   o << "}, (" << current_hp << "/" << max_hp << ") HP]";
   return o;
}

ostream& operator<<(ostream& o, const Hero& obj) {
    return obj.print(o);
}

ostream& operator<<(ostream& o, Hero_Class m) {
    return o << h_class.at(static_cast<int>(m));
};

ostream& operator<<(ostream& o, Hero_Species m) {
    return o << h_species.at(static_cast<int>(m));
};

