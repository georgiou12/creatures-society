#include <iostream>
#include <cstdlib>
#include <ctime>
#include "creatures.h"

using namespace std;

int main(int argc, char* argv[]){
    int N=atoi(argv[1]);
    int M=atoi(argv[2]);
    int L=atoi(argv[3]);
    int good_thrsh=atoi(argv[4]);
    int bad_thrsh=atoi(argv[5]);
    int action,place;
    creature_society mysociety(N,L,good_thrsh,bad_thrsh);   //creating creature_society object:mysociety
    srand(time(NULL));
    for(int i=0; i<M; i++){                     //repeat bless or beats
        action=rand()%2+1;                      //random numbers to choose beat or bless and the position
        place=rand()%(N);
        if(action==1){
            mysociety.beat(place);
        }
        else{
            mysociety.bless(place);
        }
    }
    if(mysociety.no_of_good(N)==N){
        cout << "Good Dominates in the World!" << endl;
    }
    else if(mysociety.no_of_zobies(N)==N){
        cout << "This is a dead society" << endl;
    }
    else
        cout << "Try again to improve the world" << endl;
}
