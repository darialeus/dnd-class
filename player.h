#ifndef PLAYER_H
#define PLAYER_H
#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<memory>
#include<algorithm>
#include "hero.h"
#include "campaign.h"
using namespace std;

class Player {
    string first_name;
    string last_name;
    map<unsigned, shared_ptr<Hero>> heroes;
    unique_ptr<Campaign> campaign; 
public: 
    Player();
    Player(string first_name = {}, string last_name = {});
    unsigned create_hero(const string& name, Hero_Class hero_cl, Hero_Species hero_sp, unsigned max_hp, const map<string, unsigned>& p);
    void create_campaign(string name, unsigned min_level, unsigned id);
    void join_friends_campaign(Player& pfriend, unsigned id);
    void transfer_campaign(Player& pfriend);
    unsigned remove_dead();
    ostream& print_campaign(ostream& o) const;
    ostream& print(ostream& o) const;
};

ostream& operator<<(ostream& o, const Player& p);

#endif