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
        void displayPartial(){

        }
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
            double damage;
            damage = (double(Benderattack * Powermoves[i].second))/opponent.Benderdefense;
            int maxdamage;
            double type_multiplier;
            if ((BenderType == "Water" && opponent.BenderType=="Fire") || (BenderType =="Fire" && opponent.BenderType == "Air") || (BenderType =="Air" && opponent.BenderType =="Earth")|| (BenderType == "Earth"&& opponent.BenderType == "Water"))
            {
                type_multiplier = 2.0;
                cout<<BenderName<<" used "<<Powermoves[i].first << " on " << opponent.BenderName<<" (very effective)\n";
            }
            else if ((opponent.BenderType == "Water" && BenderType=="Fire") || (opponent.BenderType =="Fire" && BenderType == "Air") || (opponent.BenderType =="Air" && BenderType =="Earth")|| (opponent.BenderType == "Earth"&& BenderType == "Water"))
            {
                type_multiplier = 0.5;
                cout<<BenderName<<" used "<<Powermoves[i].first << " on " << opponent.BenderName<<" (ineffective)\n";
            }
            else
            {
                type_multiplier = 1.0;
            }

            double critical_multiplier;
            
            int n = rand()%10;
            if (n == 0)
            {
                critical_multiplier = 2.0;  
                cout << "\n CRITICAL HIT !!! \n";
            }
            else
            {
                critical_multiplier = 1.0;
            }
            

            maxdamage = round(damage * critical_multiplier * type_multiplier);
            maxdamage = max( 1, maxdamage);
            

            
            //cout<<BenderName<<" used "<<Powermoves[i].first << " on " << opponent.BenderName<<'\n';
            cout<<opponent.BenderName<< " took "<<maxdamage<<" damage \n\n";

            if (opponent.Benderhp-maxdamage>0)
            {
                opponent.Benderhp -= maxdamage;
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

class duel {
    public:
        bender *first; // first is the pointer that holds the address of first attacking bender
        bender *second;
        bender *winner;
        
        int damage ;

        void start(){
            int choice;
            int turn=1;
            while (1)
            {   cout<<"\n-------------------------------------------------------\n";
                cout<<"TURN "<<turn<<"\n";
    
                cout<<(*first).BenderName<< " is attacking , which move would you like to play (0,1,2,3)? : ";

                cin>>choice;
                cout<<"\n";

                (*first).attackBender(*second , choice);
                (*second).displayBender();

                if ((*second).fainted() == true)
                {   
                    cout<<'\n'<<(*first).BenderName<<" won\n";
                    winner = first;
                    break;
                }
                turn++;

                cout<<"\n-------------------------------------------------------\n";
                cout<<"TURN "<<turn<<"\n";
                

                cout<<(*second).BenderName<< " is attacking , which move would you like to play (0,1,2,3)? : ";
                cin>>choice;
                (*second).attackBender(*first , choice);
                (*first).displayBender();
                if ((*first).fainted() == true)
                {   

                    cout<<'\n'<<(*second).BenderName<<" won\n";
                    winner = second;
                    break;
                }
                turn++;
            }
            cout<<"\n-------------------------------------------------------";
            cout<<"\nFINAL RESULT:\n";
            cout<<"Winner is : "<<(*winner).BenderName<<'\n';
            cout<<"Number of turns :"<<turn;


        }



    duel (bender &bender1 , bender &bender2){
        if (bender1.Benderspeed>bender2.Benderspeed)
        {
            first = &bender1;
            second = &bender2;
        }

        else if (bender2.Benderspeed>bender1.Benderspeed)
        {
            first = &bender2;
            second = &bender1;
        }
        else
        {   srand(time(NULL));
            int n = rand()%2;
            if (n==0)
            {
                first = &bender1;
                second = &bender2;
            }
            else
            {
                first = &bender2;
                second = &bender1;
            }
            
            
        }
        
        
        

    }

};


int main(){

    //---------------Name/ type  /  hp / attack/def / speed
    bender bender1 ("Kael", "Fire", 100, 58, 38, 88, array<pair<string, int>, 4>{ {{"Ember Slash", 40}, {"Quick Jab", 30}, {"Focus", 0}, {"Flame Surge", 70}} });
    bender bender2 ("Mira", "Water", 92, 50, 45, 60, array<pair<string, int>, 4>{{{"Water Whip", 35}, {"Tide Push", 25}, {"Mist Veil", 0}, {"Tidal Wave", 60}}});
    //bender bender2 ("Zephyr", "Air", 28, 12, 50, 95, array<pair<string, int>, 4>{{ {"Gust", 0} , { "Wind Slap", 18 } , {"Tumble", 12} , {"Cyclone", 22} }});
    //bender bender1 ("Doran", "Earth", 145, 80, 75,40,array<pair<string, int>, 4>{{ {"Boulder Throw", 75 }, {"Rock Fist", 42}, {"Tremor", 48} , {"Mountain Crush", 85}}});
    srand(time(NULL));

    bender1.displayBender();
    bender2.displayBender();

    //bender1.attackBender(bender2 , 0);

    //bender2.displayBender();

    //bender2.fainted();

    duel d1(bender1 , bender2);
    d1.start();

    

    return 0;
}