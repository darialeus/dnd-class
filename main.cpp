#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

enum class Studien_Richtung {BWL, BIOLOGIE, CHEMIE, INFORMATIK, PUBLIZISTIK, ARCHITEKTUR, SLOWISTIK};
const vector<string> studienrichtungen {"BWL", "Biologie", "Chemie", "Informatik", "Publizistik", "Architektur", "Slowistik"};


class Student {
    unsigned matrikelnummer; 
    string name; 
    Studien_Richtung st_richtung;
    static unsigned index; 
public: 
    Student() = default;
    Student(string name, Studien_Richtung st_richt = Studien_Richtung::BWL) :  name{name}, st_richtung{st_richt} {
        if(name.empty()) throw runtime_error("Empty name");
        matrikelnummer = ++index; 
    }

    unsigned get_id() { 
        return matrikelnummer;
    }
    string get_name() {
        return name;
    }
    Studien_Richtung get_richtung() {
        return st_richtung;
    }
    virtual string student_sagt() {
        string result {"I am " + name + " " + to_string(matrikelnummer) + "\n"};
        return result; 
    }
    virtual ~Student() = default;

};

class Chemiker : public Student {
    unsigned number_of_student = 0;
public: 
    Chemiker();
    Chemiker(string name, Studien_Richtung st_richtung) : Student(name, st_richtung)   {}
    
    string student_sagt() override {
        ++number_of_student;
        string base = Student::student_sagt();
        int index = static_cast<int>(get_richtung());
        string result {base + "I study " + studienrichtungen[index] +  " and i love it " + to_string(number_of_student) + "\n" };
        return result; 
    }
};

unsigned Student::index = 0;

string different_name (string& name) {
    for (size_t i {0}; i < name.length(); ++i) {
        if ((i+1) % 3 == 0) name[i] = std::toupper(static_cast<unsigned char>(name[i]));
    }
    
    name.erase(remove_if(name.begin(), name.end(), [&] (char c) {
        return c == 'a' || c == 'A';
    }), name.end());

    return name;
}

unsigned count_letter (string& name) {
    unsigned count = 0; 
      for (char c : name) {
        if (c == 'a' || c == 'A') ++count;
    }
    return count; 
}
string make_lower(string& name) {
    for(char& c : name) {
        if (isupper(c)) c = tolower(c);
    }
    return name; 
}

//pair<unsigned, unsigned> filtering (const vector<shared_ptr<Student>>& v) {}


int main(){
 
shared_ptr<Student> student = std::make_shared<Chemiker>("Anna", Studien_Richtung::CHEMIE);
cout << student->student_sagt() << endl;
/*
Student student2 {"Paul", Studien_Richtung::BWL};
Student* student3 = new Chemiker("Elisa", Studien_Richtung::CHEMIE);
shared_ptr<Student> student4 = std::make_shared<Chemiker>("Johanes", Studien_Richtung::CHEMIE);
shared_ptr<Student> student5 = std::make_shared<Student>("Maria", Studien_Richtung::BIOLOGIE);

weak_ptr<Student> w_p_student1 = std::weak_ptr<Student>(student1);
weak_ptr<Student> w_p_student2 = std::weak_ptr<Student>(student4);
unique_ptr<Student> unique_student4 = std::make_unique<Chemiker>("Johanes", Studien_Richtung::CHEMIE);
//unique_ptr<Student> unique_student4 = std::make_unique<Chemiker>(stundet2); - is not correct
auto unique_student = std::move(unique_student4);


cout << student1->student_sagt() << endl;
cout << student2.student_sagt() << endl;
cout << student3->student_sagt() << endl;

auto student_1 = w_p_student1.lock();
auto student_2 = w_p_student2.lock();
cout << student_1->student_sagt() << endl;
cout << student_2->student_sagt() << endl;
cout << unique_student->student_sagt() << endl;

auto name_of_st1 = student1->get_name();
cout << count_letter(name_of_st1) << endl;
cout << different_name(name_of_st1) << endl;
*/

    // shared_ptrs bleiben im Scope erhalten
    shared_ptr<Student> student1 = make_shared<Chemiker>("Anna", Studien_Richtung::CHEMIE);
    shared_ptr<Student> student2 = make_shared<Chemiker>("Johanes", Studien_Richtung::CHEMIE);
    shared_ptr<Student> student3 = make_shared<Student>("Maria", Studien_Richtung::BIOLOGIE);


    map<unsigned, weak_ptr<Student>> studenten{
        {1, student1},
        {2, student2},
        {3, student3}
    };

    for (auto it = studenten.begin(); it != studenten.end(); ) {
        auto st_shared = it->second.lock();

        if (!st_shared) {
            cout << "[!] Ungültig (abgelaufen), wird entfernt.\n";
            it = studenten.erase(it);
        
        } else if (st_shared->get_id() == 1) {
            cout << st_shared->get_name() << " " << st_shared->get_id() << " (lösche)\n";
            it = studenten.erase(it);
        } else {
            cout << "Bleibt: " << st_shared->get_name() << "\n";
            ++it;
        }
    }



shared_ptr<Student> first = nullptr;
auto it1 = studenten[1].lock();
auto it2 = studenten[2].lock();
if(!first) {
    first = it1;
    cout << first->get_name() << endl;
}
else cout << it2->get_name() << endl;

string name_of_st1 = student1->get_name();
cout << make_lower(name_of_st1) << endl;

return 0;  

}
/*
vector<shared_ptr<Monster>> task1(const vector<shared_ptr<Monster>>& v) {
    vector<shared_ptr<Monster>> new_monsters;

    if (v.empty()) return new_monsters;

    // Health- und Attackwerte extrahieren
    vector<unsigned> health_values;
    unsigned max_attack = 0;

    for (const auto& m : v) {
        health_values.push_back(m->get_health());
        if (m->get_attack() > max_attack) {
            max_attack = m->get_attack();
        }
    }

    unsigned min_health = *min_element(health_values.begin(), health_values.end());
    unsigned max_health = *max_element(health_values.begin(), health_values.end());
    unsigned new_health = min_health * max_health;

    // Neue Monster erzeugen
    for (const auto& m : v) {
        string new_name = bigger_letter(m->get_name());
        shared_ptr<Monster> new_m = make_shared<Standard_Monster>(new_name, new_health, max_attack);
        new_monsters.push_back(new_m);
    }

    return new_monsters;
}

class Super_Task{
  vector<weak_ptr<Hero>> heroes;
public: 
  Super_Task();
  Super_Task(const vector<shared_ptr<Hero>>& heroes) {
    for (const auto& h : heroes) {
     this->heroes.push_back(h);
    }
  }
  
  vector<shared_ptr<Hero>> filtering(const vector<pair<char, Hero_Class>>& cl) const {
  vector<shared_ptr<Hero>> result;
    
    for(auto& ch : heroes) {
      auto h_ptr = ch.lock();
      if(!h_ptr) continue; 
      for (const auto& p : cl) {
      	if (h_ptr->get_name().find(p.first) != std::string::npos && h_ptr->get_hero_class() == p.second) {
        	result.push_back(h_ptr);
          break;
        }
      }
    }
    return result; 
  }
  
};


pair<unsigned, unsigned> Campaign::enter_dungeon(const vector<shared_ptr<Monster>>& v) {
	unsigned wins = 0; 
  unsigned losses = 0; 
  for (const auto& monster : v) {
  	auto hero_ready = first_hero();
    if(hero_ready) {
    bool won = hero_ready->fight(*monster);
    if (won) ++wins;
    else ++losses; 
  } else ++losses;
  }
  return {wins, losses};
}

shared_ptr<Hero> Campaign::first_hero() {
	shared_ptr<Hero> first = nullptr; 
  for (auto& [id, weak_h] : heroes) {
  	auto h = weak_h.lock();
    if (h && h->get_current_hp() > 0) {
    if (!first || h->get_id() < first->get_id()) first = h;
  	}
  }
  return first;
}

class Task3 : public Hero {
  unsigned count = 0;
public:
  using Hero::Hero;
  Task3(); 
  //Task3(string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const map<string, unsigned>& abilities);
  bool fight(Monster& m) override; 
};

//Task3::Task3 (string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const map<string, unsigned>& abilities) : 
	//Hero (name, hero_class, hero_species, max_hp, abilities) {}

bool Task3::fight(Monster& m) {
		++count;
    if (count % 3 == 0) return Hero::fight(m);
    return false; 
}


*/

