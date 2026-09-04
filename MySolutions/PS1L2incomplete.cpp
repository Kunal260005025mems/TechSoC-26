#include <iostream>
int r;
int c;
void display(char OG[][100]);
void copyarray(char n1[][100], char n2[][100]);
void transform_mid(char n1[][100] , char n2[][100]);


char ogblanket[100][100];
char blanket[100][100];
char blanket2[100][100];

int main(){

    std::string mode;
    std::cout << " Enter Mode : \n";
    std::cin >> mode;

    char OG[100][100];
    char a[100][100];
    char b[100][100];

    // b is dotted array with r x c dimension
    for (int i = 1; i < r+1 ; i++)
    {   for (int j = 1; j < c+1; j++)
    {   b[i][j] = '.';
        
    }
    }

    
    std::cout<<"ENTER R : ";
    std::cin>>r;
    std::cout<<"ENTER c : ";
    std::cin>>c;

    int g;
    std::cout<<"ENTER G / K : ";
    std::cin>>g;

    

    
    

    std::cout<< "\nENTER THE ARRAY : \n";

    for (int i = 1; i < r+1 ; i++)
    {   for (int j = 1; j < c+1; j++)
    {   std::cin>> OG[i][j];
        //std::cout<<' ';
        
    }
    std::cout<<'\n';    
    
    }


    std::cout<< "\nThe array u entered: \n";
    display(OG);
    copyarray(OG,a); //og--> a
    std::cout<<'\n';
    
    

    

    if (mode == "torroid" )
    {
        for (int i = 0; i < g; i++)
        {   
    
        /* code */
    
    
    

        transform_mid(a,b);
    

    
        copyarray(b,a);
    
    
        }
        std::cout<<"\n-------------------FINAL----------------\n";
        display(b);
    }

    else if (mode=="classifyk")
    {   char arraycheck [100][100][100] ;
        for (int x = 0; x < g; x++)
        { for (int i = 1; i < r+1; i++)
        {   for (int j = 1; j < c+1; j++)
        {
            arraycheck[x][i][j]= a[i][j];
            

        }
        
            /* code */
        }
        transform_mid(a,b);
        copyarray(b,a);
            
        }
        //--------------------------------------------------
        int c1=0;

        for (int x = 0; x < g-1; x++)
        {   int t=0;
            for (int i = 1; i < r+1; i++)
            {      
                for (int j = 1; j < c+1; j++)
                {   if (arraycheck[x][i][j]==arraycheck[x+1][i][j])
                    {
                        t+=1;
                    }
                }
            }   

            if (t==r*c){
               c1=1;
            }    
        }


        if (c1==1)
        {
            std::cout<<"still life";
        }
        //-----------------------------------------------------------------

        int extinct_gen;
        for (int x = 0; x < g; x++)
        {   int alive = 0;
            for (int i = 1; i < r+1; i++)
        {       for (int j = 1; j < c+1; j++)
        {
            if (arraycheck[x][i][j]=='#')
            {
                alive+=1;
            }
            
        }
        
            /* code */
        }
            if (alive == 0)
            {
                c1=2;
                extinct_gen=x;
                break;

            }
            
        
            /* code */
        }
        if (c1==2)
        {
            std::cout<<"\nextinct at gen\n"<<extinct_gen;
        }

        
        
        
    }
    
    


    return 0;
}



void transform_mid(char n1[][100] , char n2[][100]){  // make sure n2 is like atleast a dotted array, basically smth filled
    for (int i = 1; i < r+1; i++)
    { for (int j = 1 ; j < c+1; j++)
    {   int alive = 0;
        for ( int di = -1; di <=1;  di++)
            {   for (int dj = -1; dj <=1; dj++)
            {   
                if ( di == 0 && dj ==0)
                {   continue;
                
                }
                
                if (n1[(i+di-1 +r)%r +1][(j+dj-1 + c)%c +1]=='#') // ( i + di + r  )%r
                {
                    alive+=1;
                }
                

                
            }
            
                /* code */
            }
        if (n1[i][j]=='#')
        {
            if (alive<2 || alive>3)
            {
                n2[i][j]='.';
            }
            else if(alive==2 || alive ==3){
                n2[i][j]='#';

            }
        }
        else
        {
            if (alive ==3)
            {
                n2[i][j]='#';
            }
        }
        
    }
    
        
    }
    


}

void display(char OG[][100]){
    for (int i = 1; i < r+1 ; i++)
    {   for (int j = 1; j < c+1; j++)
    {   std::cout<< OG[i][j];
        std::cout<<' ';
        
    }
    std::cout<<'\n';    
    
    }
}


void copyarray(char n1[][100], char n2[][100]){
    for (int i = 1; i < r+1 ; i++)
    {   for (int j = 1; j < c+1; j++)
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
