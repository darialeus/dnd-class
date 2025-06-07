#include<iostream> 
#include<vector>
#include<string>
#include<stdexcept>
#include<set>
#include<map>
#include<memory>
#include<algorithm>
#include "player.h"
#include "hero.h"
#include "campaign.h"
using namespace std; 

Player::Player(string first_name, string last_name) : first_name{first_name}, last_name{last_name} {
    if(first_name.empty()) throw runtime_error ("Empty first name");
    if(last_name.empty()) throw runtime_error ("Empty last name");
}
unsigned Player::create_hero(const string& name, Hero_Class hero_cl, Hero_Species hero_sp, unsigned max_hp, const map<string, unsigned>& ab) {
    auto hero = make_shared<Hero>(name, hero_cl, hero_sp, max_hp, ab);
    unsigned id = hero->get_id();
    heroes[id] = hero;
    return id;
}

void Player::create_campaign(string name, unsigned min_level, unsigned id) {
    if (heroes.find(id) == heroes.end()) throw runtime_error("Hero not found");
    //if (campaign) campaign.reset();
    auto new_campaign = make_unique<Campaign>(name, min_level);
    try {
        new_campaign->add_hero(heroes[id]); 
    } catch (...) {
        throw runtime_error("Hero is not added");
    }
    campaign = std::move(new_campaign);
}

void Player::join_friends_campaign(Player& pfriend, unsigned id) {
    if (!pfriend.campaign) throw runtime_error ("Friend has no campaign");
    if (heroes.find(id) == heroes.end()) throw runtime_error ("Hero not found");
    pfriend.campaign->add_hero(heroes[id]);
}

void Player::transfer_campaign(Player& pfriend) {
    if (!campaign) throw runtime_error("No campaign");
    pfriend.campaign = std::move(campaign);
}

unsigned Player::remove_dead() {
    if (!campaign) return 0;
    return campaign->remove_dead_and_expired();
}

ostream& Player::print_campaign(ostream& o) const {
    if(campaign) return campaign->print(o);
    return o << "[]";
}

ostream& Player::print(ostream& o) const {
    bool first = true;
    o << "[" << first_name << " " << last_name << ", {"; 
    for (const auto& [id, shared_h] : heroes) {
        if (!first) o << ", ";
        o << *shared_h;  
        first = false;
    }
    o << "}, ";
    print_campaign(o); 
    return o << "]";
}


ostream& operator<<(ostream& o, const Player& p) {
    return p.print(o);
}