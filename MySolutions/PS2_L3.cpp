#include <iostream>
#include <utility>
#include <array>
#include <cmath> 

using namespace std;


class moves{
    public:
        string Name;
        int Power;
        string status;
        
    moves() {
    Name = "";
    Power = 0;
    status = "NULL";
    }
        
        
    
    moves(string N , int p , string s){
        Name = N;
        Power = p;
        status = s;
        

    }


};

class bender {

    public:
        string BenderName;
        string BenderType;
        int Bendermaxhp;
        int Benderhp;
        int Benderattack;
        int Benderdefense;
        int Benderspeed;
        array< moves , 4> Powermoves;

        string affected_Status="NULL";
        int affected_turn=0;

        
        void displayBender()

        {
        cout << BenderName << " (" << BenderType << ") - HP: "
         << Benderhp << "/" << Bendermaxhp
         << ", Attack: " << Benderattack
         << ", Defense: " << Benderdefense
         << ", Speed: " << Benderspeed <<", status: "<< affected_Status <<'\n';

        cout << "Moves: ";

        for (int i = 0; i < 4; i++)
        {
            cout << Powermoves[i].Name << " ("
                << Powermoves[i].Power << ")("
                <<Powermoves[i].status<<")";

            if (i < 3)
            cout << ", ";
        }

            cout << '\n'<<'\n';
        }
        

        void attackBender(bender &opponent  , int i){
            double damage;
            damage = (double(Benderattack * Powermoves[i].Power))/opponent.Benderdefense;
            int maxdamage;
            double type_multiplier;
            if ((BenderType == "Water" && opponent.BenderType=="Fire") || (BenderType =="Fire" && opponent.BenderType == "Air") || (BenderType =="Air" && opponent.BenderType =="Earth")|| (BenderType == "Earth"&& opponent.BenderType == "Water"))
            {
                type_multiplier = 2.0;
                cout<<BenderName<<" used "<<Powermoves[i].Name << " on " << opponent.BenderName<<" (very effective)\n";
            }
            else if ((opponent.BenderType == "Water" && BenderType=="Fire") || (opponent.BenderType =="Fire" && BenderType == "Air") || (opponent.BenderType =="Air" && BenderType =="Earth")|| (opponent.BenderType == "Earth"&& BenderType == "Water"))
            {
                type_multiplier = 0.5;
                cout<<BenderName<<" used "<<Powermoves[i].Name << " on " << opponent.BenderName<<" (ineffective)\n";
            }
            else
            {
                type_multiplier = 1.0;
            }
            
            if (opponent.affected_Status == "NULL"|| opponent.affected_turn <=0)
            {
                opponent.affected_Status ="NULL";
            }
            else if (opponent.affected_Status == "Burn" && opponent.affected_turn >0)
            {   
                int burn_damage = round(0.10 * opponent.Bendermaxhp);
                
                if (opponent.Benderhp - burn_damage>0)
                {
                    opponent.Benderhp -= burn_damage;
                }
                else
                {
                    opponent.Benderhp = 0;
                }
                
                
            }

            if (affected_Status == "Heal" && affected_turn>0)
            {
                int heal_health = round(0.10 * Bendermaxhp);
                Benderhp += heal_health;
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

    bender (string bName, string Type , int hp ,int attack , int defense , int speed , array< moves , 4> movelist ){

        BenderName = bName;
        BenderType = Type;
        Benderhp = hp;
        Bendermaxhp = hp;
        Benderattack = attack;
        Benderdefense = defense;
        Benderspeed = speed;
        Powermoves = movelist;


    }

};

void apply_status( bender &attacker, int i , bender &opponent){
            if ((attacker.Powermoves[i]).status =="NULL")
            {
                return;
            }
            
            else if ((attacker.Powermoves[i]).status =="Burn")
            {
                opponent.affected_Status = "Burn";
                opponent.affected_turn = 4;
            }

            else if ((attacker.Powermoves[i]).status == "Heal")
            {
                attacker.affected_Status="Heal";
                attacker.affected_turn = 4;
            }
            
            
            
        }


class duel {
    public:
        bender *first; // first is the pointer that holds the address of first attacking bender
        bender *second;
        bender *winner;
        
        int damage ;
        int turn;
        

        void start(){
            int choice;
            turn=1;
            while (1)
            {   cout<<"\n-------------------------------------------------------\n";
                cout<<"TURN "<<turn<<"\n";
    
                cout<<(*first).BenderName<< " is attacking , which move would you like to play (0,1,2,3)? : ";

                cin>>choice;
                
                apply_status(*first , choice , * second);
                (*first).attackBender(*second , choice);

                (*second).affected_turn --;

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

                apply_status(*second , choice , *first);
                (*second).attackBender(*first , choice);
                (*first).affected_turn --;


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
        {   
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


class AI_duel {
    public:
        bender *first; // first is the pointer that holds the address of first attacking bender
        bender *second;
        bender *winner;
        int turn;

    int choose_move(bender &aibender , bender &human){
        
        if ( ((double)(aibender.Benderhp))/(aibender.Bendermaxhp)<0.30 && ( ((aibender.Powermoves[0]).status == "Heal" ) || ((aibender.Powermoves[1]).status == "Heal" ) || ((aibender.Powermoves[2]).status == "Heal" ) || ((aibender.Powermoves[3]).status == "Heal" ) ) )
        {
            for (int j = 0; j < 4; j++)
            {
               if (aibender.Powermoves[j].status == "Heal"){
                    return j;


               }
            }
            
        }

        else if (
                ((double)human.Benderhp / human.Bendermaxhp > 0.70) &&
                (
                    (aibender.Powermoves[0].status != "NULL" && aibender.Powermoves[0].status != "Heal") ||
                    (aibender.Powermoves[1].status != "NULL" && aibender.Powermoves[1].status != "Heal") ||
                    (aibender.Powermoves[2].status != "NULL" && aibender.Powermoves[2].status != "Heal") ||
                    (aibender.Powermoves[3].status != "NULL" && aibender.Powermoves[3].status != "Heal")
                )
        )
        {
            for (int j = 0; j < 4; j++)
            {
               if (aibender.Powermoves[j].status != "NULL" && aibender.Powermoves[j].status != "Heal"){
                    return j;


               }
            }
        }

        else if ((double)human.Benderhp / human.Bendermaxhp < 0.25)
{
    int moveIndex[4] = {0, 1, 2, 3};
    double damage[4];

    for (int j = 0; j < 4; j++)
    {
        damage[j] = (double)(aibender.Benderattack *
                       aibender.Powermoves[j].Power)
                       / human.Benderdefense;
    }

    // Bubble sort move indices by damage
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3 - j; k++)
        {
            if (damage[k] > damage[k + 1])
            {
                double tempDamage = damage[k];
                damage[k] = damage[k + 1];
                damage[k + 1] = tempDamage;

                int tempIndex = moveIndex[k];
                moveIndex[k] = moveIndex[k + 1];
                moveIndex[k + 1] = tempIndex;
            }
        }
    }

    int i = moveIndex[3];  // Index of the highest-damage move
    return i;
}
        
    }

    AI_duel (bender &bender1 , bender &benderAI){
        if (bender1.Benderspeed>benderAI.Benderspeed)
        {
            first = &bender1;
            second = &benderAI;
        }

        else if (benderAI.Benderspeed>bender1.Benderspeed)
        {
            first = &benderAI;
            second = &bender1;
        }
        else
        {   
            int n = rand()%2;
            if (n==0)
            {
                first = &bender1;
                second = &benderAI;
            }
            else
            {
                first = &benderAI;
                second = &bender1;
            }
            
            
        }
        
        

    }
    void start(){
            int choice;
            turn=1;
            while (1)
            {   cout<<"\n-------------------------------------------------------\n";
                cout<<"TURN "<<turn<<"\n";
    
                cout<<(*first).BenderName<< " is attacking , which move would you like to play (0,1,2,3)? : ";

                cin>>choice;
                
                apply_status(*first , choice , * second);
                (*first).attackBender(*second , choice);

                (*second).affected_turn --;

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

                apply_status(*second , choice , *first);
                (*second).attackBender(*first , choice);
                (*first).affected_turn --;


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
};

int main(){

    //---------------Name/ type  /  hp / attack/def / speed
    moves m1("Ember slash ", 40 , "Burn");
    moves m2("Quick Jab" , 30 , "NULL");
    moves m3("Focus", 0 , "NULL");
    moves m4("Flame Surge", 70 , "NULL");
    moves m5("Water Pulse", 35, "NULL");
    moves m6("Aqua Jet", 25, "NULL");
    moves m7("Healing Flow", 0, "Heal");
    moves m8("Tidal Wave", 65, "NULL");
    bender bender1 ("Kael", "Fire", 100, 58, 38, 88, array<moves , 4>{ m1,m2,m3,m4 });
    bender bender2 ("Mira", "Water", 92, 50, 45, 60, array<moves , 4>{m5, m6,m7 ,m8});
    //bender bender2 ("Zephyr", "Air", 28, 12, 50, 95, array<moves , 4>{{ {"Gust", 0} , { "Wind Slap", 18 } , {"Tumble", 12} , {"Cyclone", 22} }});
    //bender bender1 ("Doran", "Earth", 145, 80, 75,40,array<moves , 4>{{ {"Boulder Throw", 75 }, {"Rock Fist", 42}, {"Tremor", 48} , {"Mountain Crush", 85}}});
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