#include <iostream>
int r;
int c;
void display(char OG[][100]);
void copyarray(char n1[][100], char n2[][100]);
void transform_mid(char n1[][100] , char n2[][100]);
void cover(char n1[][100],char blanket[][100]);
void uncover(char blanket[][100] ,char n1[][100]);
void displayblanket(char OG[][100]);
int count(char n1[][100]);

char ogblanket[100][100];
char blanket[100][100];
char blanket2[100][100];

int main(){
    
    int g;
    std::cout<<"ENTER R : ";
    std::cin>>r;
    std::cout<<"ENTER c : ";
    std::cin>>c;
    std::cout<<"ENTER G : ";
    std::cin>>g;

    char OG[100][100];
    char a[100][100];
    char b[100][100];

    // b is dotted array with r x c dimension
    for (int i = 0; i < r ; i++)
    {   for (int j = 0; j < c; j++)
    {   b[i][j] = '.';
        
    }
    }

    // blankets are dotted array with dimension (r+2) x (c+2)
    for (int i = 0; i < r+2 ; i++)
    {   for (int j = 0; j < c+2; j++)
    {   blanket[i][j] = '.';
        blanket2[i][j] = '.';
    }
    }

    /* This is for display of initial blanket
    for (int i = 0; i < r+2 ; i++)
    {   for (int j = 0; j < c+2; j++)
    {   std::cout<< blanket[i][j];
        std::cout<<' ';
        
    }
    
    std::cout<<'\n';    
    
    }
    */
    

    std::cout<< "\nENTER THE ARRAY : \n";

    for (int i = 0; i < r ; i++)
    {   for (int j = 0; j < c; j++)
    {   std::cin>> OG[i][j];
        //std::cout<<' ';
        
    }
    std::cout<<'\n';    
    
    }


    std::cout<< "\nThe array u entered: \n";
    display(OG);
    copyarray(OG,a); //og--> a

    
    
    int population[g];
    if (g==0)
    {   c = count(a);
        std::cout<<"\nInitial POPULATION\n"<<c;
        std::cout<<"\nCurrent POPULATION\n"<<c;
        std::cout<<"\nPeak POPULATION\n"<<c;
        

        
        
        std::cout<<"\n-------------------FINAL----------------\n";
        display(a);
        /* code */
    }
    
    else {
    for (int i = 0; i < g; i++)
    {
    
        /* code */
    
    
    cover(a,blanket);
    
    //displayblanket(blanket);

    transform_mid(blanket,blanket2);

    //std::cout<<"\n---------------------------------\n";

    //displayblanket(blanket2);

    //std::cout<<"\n---------------------------------\n";
    uncover(blanket2, b);

    //std::cout<<"B \n";
    //display (b);
    copyarray(b,a);
    int c = count(b);
    population[i]=c;
    
    
        
    //std::cout<<"\n------------------NEW ITERATION---------------\n";
    }
    std::cout<<"\nInitial POPULATION\n"<<population[0];
    std::cout<<"\nCurrent POPULATION\n"<<population[g-1];

    
    for (int x = 0; x < g; x++)
    {   int temp;
        if (population[x]>population[x+1])
        {   temp = population[x+1];
            population[x+1]=population[x];
            population[x]= population[x+1];
                        /* code */
        }
        
    }
    std::cout<<"\nPEAK POPULATION\n"<<population[g-1];
    



    
    std::cout<<"\n-------------------FINAL----------------\n";
    display(b);
    }


    return 0;
}
void cover(char n1[][100],char blanket[][100]){
    for (int i = 1; i < r+1; i++)
    {   for (int j = 1; j < c+1; j++)
    {   blanket[i][j]=n1[i-1][j-1];
        /* code */
    }
    
        /* code */
    }
    
}

void uncover(char blanket[][100] ,char n1[][100]){
    for (int i = 0; i < r; i++)
    {   for (int j = 0; j < c; j++)
    {   n1[i][j]=blanket[i+1][j+1];
        /* code */
    }
    
        /* code */
    }
    
}



void transform_mid(char n1[][100] , char n2[][100]){  // make sure n2 is like atleast a dotted array, basically smth filled
    for (int i = 1; i < r+1; i++)
    { for (int j = 1 ; j < c+1; j++)
    {   if (n1[i][j]=='#')
    {       int alive=0;
            char check[] = { n1[i-1][j-1] , n1[i-1][j] , n1[i-1][j+1] , n1[i][j-1] , n1[i][j+1] , n1[i+1][j-1] , n1[i+1][j] , n1[i+1][j+1]};
            for ( char a : check)
            {   if (a=='#')
            {   alive+=1;
                /* code */
            }
            
                /* code */
            }

            if (alive<2 || alive>3)
            {
                n2[i][j]='.';
            }
            else if(alive==2 || alive ==3){
                n2[i][j]='#';

            }
                
        
    }
        else if (n1[i][j]=='.')
    {   int alive = 0;
        char check[] = { n1[i-1][j-1] , n1[i-1][j] , n1[i-1][j+1] , n1[i][j-1] , n1[i][j+1] , n1[i+1][j-1] , n1[i+1][j] , n1[i+1][j+1]};

            for ( char i : check)
                {   if (i=='#')
                {  
                    alive+=1;
                    /* code */
                }

            
                    /* code */
                }
            if (alive ==3)
            {
                n2[i][j]='#';
            }
            
        
    }
        
    }
    
        
    }
    


}

void display(char OG[][100]){
    for (int i = 0; i < r ; i++)
    {   for (int j = 0; j < c; j++)
    {   std::cout<< OG[i][j];
        std::cout<<' ';
        
    }
    std::cout<<'\n';    
    
    }
}

void displayblanket(char OG[][100]){
    for (int i = 0; i < r+2 ; i++)
    {   for (int j = 0; j < c+2; j++)
    {   std::cout<< OG[i][j];
        std::cout<<' ';
        
    }
    std::cout<<'\n';    
    
    }
}


void copyarray(char n1[][100], char n2[][100]){
    for (int i = 0; i < r ; i++)
    {   for (int j = 0; j < c; j++)
    {   n2[i][j] = n1[i][j];
        
    }
        
    
    }
    
}

int count(char n1[][100]){
    int alive=0;
    for (int i = 0; i < r ; i++)
    {   for (int j = 0; j < c; j++)
    {   if(n1[i][j]=='#'){
        alive +=1;
    }
        
    }
    }
    return alive;

}
