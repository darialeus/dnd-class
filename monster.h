#ifndef MONSTER_H
#define MONSTER_H
#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

class Monster {
    string name;
    unsigned health;
    unsigned attack;
public:
    Monster();
    Monster(string name = {}, unsigned health = 50, unsigned attack = 5);
    string get_name();
    unsigned get_health();
    unsigned get_attack();
    virtual ~Monster() = default;
    virtual unsigned calculate_damage(unsigned dmg) const = 0;
    void take_damage(unsigned dmg);
    bool is_dead() const;
    virtual string additional_information() const = 0;
    ostream& print(ostream& o) const;
};

ostream& operator<<(ostream& o, const Monster& h);

class Elite_Monster : public Monster {
    unsigned defense;
public:
    Elite_Monster();
    Elite_Monster (string name, unsigned health, unsigned attack, unsigned defense); 

    unsigned calculate_damage(unsigned dmg) const;
    string additional_information() const; 
    };

class Standard_Monster : public Monster {
public:
    Standard_Monster();
    Standard_Monster (string name, unsigned health, unsigned attack); 

    unsigned calculate_damage(unsigned dmg) const;
    string additional_information() const; 
    };

#endif