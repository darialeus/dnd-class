#ifndef HERO_H
#define HERO_H
#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<algorithm>
#include "monster.h"
using namespace std;

enum class Hero_Class{ BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN, RANGER, ROGUE, SORCERER, WARLOCK, WIZARD};

const vector<string> h_class {"Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"};

enum class Hero_Species{ DRAGONBORN, DWARF, ELF, GNOME, AASIMAR, HALFLING, ORC, GOLIATH, HUMAN, TIEFLING};

const vector<string> h_species {"Dragonborn", "Dwarf", "Elf", "Gnome", "Aasimar", "Halfling", "Orc", "Goliath", "Human", "Tiefling"};



class Hero {
    unsigned id;
    string name; 
    Hero_Class hero_class;
    Hero_Species hero_species;
    unsigned level;
    unsigned max_hp;
    unsigned current_hp;
    map<string, unsigned> abilities; 
    static unsigned next_id;
public:
    Hero();
    Hero( string name = {}, Hero_Class h_c = Hero_Class::FIGHTER, Hero_Species h_s = Hero_Species::HUMAN, unsigned max = 50, const map<string, unsigned>& abilities = {});
    unsigned level_up();
    bool fight(Monster& m);
    unsigned get_id();
    unsigned get_level();
    unsigned get_current_hp();
    ostream& print(ostream& o) const;
    
};

ostream& operator<<(ostream& o, const Hero& obj);

ostream& operator<<(ostream& o, Hero_Class m);

ostream& operator<<(ostream& o, Hero_Species m);
#endif