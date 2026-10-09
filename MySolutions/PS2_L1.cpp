#include <iostream>
#include <utility>
#include <array>
#include <cmath> 
using namespace std;


class bender {
    public:
        string BenderName;
        string BenderType;
        int Bendermaxhp;
        int Benderhp;
        int Benderattack;
        int Benderdefense;
        int Benderspeed;
        array< pair<string, int> , 4> Powermoves;

        void displayBender()

        {
        cout << BenderName << " (" << BenderType << ") - HP: "
         << Benderhp << "/" << Bendermaxhp
         << ", Attack: " << Benderattack
         << ", Defense: " << Benderdefense
         << ", Speed: " << Benderspeed << '\n';

        cout << "Moves: ";

        for (int i = 0; i < 4; i++)
        {
            cout << Powermoves[i].first << " ("
                << Powermoves[i].second << ")";

            if (i < 3)
            cout << ", ";
        }

            cout << '\n'<<'\n';
        }
        
        void attackBender(bender &opponent  , int i){
            int damage;
            damage = round((((double)(Benderattack * Powermoves[i].second))/opponent.Benderdefense));

            cout<<BenderName<<" used "<<Powermoves[i].first << " on " << opponent.BenderName<<'\n';
            cout<<opponent.BenderName<< " took "<<damage<<" damage \n\n";

            if (opponent.Benderhp-damage>0)
            {
                opponent.Benderhp -= damage;
            }

            else
            {
                opponent.Benderhp = 0;
            }
            
        }
        
        bool fainted(){
            if (Benderhp>0)
            {   cout<<BenderName<<" fainted : false";
                return false ;
            }
            else
            {
                cout<<BenderName<<" fainted : true";
                return true;
            }
            
            
        }

    bender (string Name, string Type , int hp ,int attack , int defense , int speed , array< pair<string, int> , 4> moves ){

        BenderName = Name;
        BenderType = Type;
        Benderhp = hp;
        Bendermaxhp = hp;
        Benderattack = attack;
        Benderdefense = defense;
        Benderspeed = speed;
        Powermoves = moves;


    }

};


int main(){

    //---------------Name/ type  /  hp / attack/def / speed
    //bender bender1 ("Kael", "Fire", 100, 58, 38, 88, array<pair<string, int>, 4>{ {{"Ember Slash", 40}, {"Quick Jab", 30}, {"Focus", 0}, {"Flame Surge", 70}} });
    //bender bender2 ("Mira", "Water", 92, 50, 45, 60, array<pair<string, int>, 4>{{{"Water Whip", 35}, {"Tide Push", 25}, {"Mist Veil", 0}, {"Tidal Wave", 60}}});
    bender bender2 ("Zephyr", "Air", 28, 12, 50, 95, array<pair<string, int>, 4>{{ {"Gust", 0} , { "Wind Slap", 18 } , {"Tumble", 12} , {"Cyclone", 22} }});
    bender bender1 ("Doran", "Earth", 145, 80, 75,40,array<pair<string, int>, 4>{{ {"Boulder Throw", 75 }, {"Rock Fist", 42}, {"Tremor", 48} , {"Mountain Crush", 85}}});


    bender1.displayBender();
    bender2.displayBender();

    bender1.attackBender(bender2 , 0);

    bender2.displayBender();

    bender2.fainted();

    

    return 0;
}