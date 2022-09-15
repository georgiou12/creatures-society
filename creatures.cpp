#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "creatures.h"

using namespace std;

/////////////////Creature_society/////////////////

creature_society::creature_society(int N, int L,int good_thrsh,int bad_thrsh):crowd(N){
    int j=0,ran=0;
    const char* good[26]={"A","B","C","D","E","F","G","H","I","G","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    const char* bad[26]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    srand(time(NULL));
    creature** society;             //allocate dynamically space for my array of creatures
    society=new creature*[N];       //with a double pointer cause the size is given in command line 
    crpointer=society;              //set crpointer the double pointer point to the start of my array
    for(int i=0;i<N;i++){
        j=rand()%26;                //take a random "name" from the above arrays
        ran=(rand()%2)+1;           //random choose for creating good/bad creature  
        if(ran==1){
            society[i]=new good_creature(good[j],i,L,good_thrsh,this);
        }
        else{ 
            society[i]=new bad_creature(bad[j],i,L,bad_thrsh,this);
        }
    }
}

void creature_society::clone_next(int i){
    if(i==crowd-1){
        if(crpointer[0]->is_a_zobie()){
            crpointer[0]=crpointer[0]->clone(*crpointer[i],i);    //clone returns a pointer to creature
            cout << "The good creature " << crpointer[i]->get_name() << crpointer[i]->get_pos() << " has been cloned to the next postion" << endl;
        }
    }
    else{
        if(crpointer[i+1]->is_a_zobie()){
            crpointer[i+1]=crpointer[i+1]->clone(*crpointer[i],i);
            cout << "The good creature " << crpointer[i]->get_name() << crpointer[i]->get_pos() << " has been cloned to the next postion" << endl;
        }
    }
}

void creature_society::clone_zobies(int i){
    bool zobieprevious=true;                    //use this instead of crpointer[i+1] that would send me off limits of array
    while(i<crowd-1 && zobieprevious==true){
        if(crpointer[i+1]->is_a_zobie()==true){
            crpointer[i+1]=crpointer[i+1]->clone(*crpointer[i],i);
            cout << "The bad creature "<< crpointer[i]->get_name() << crpointer[i]->get_pos() << " has been cloned to the next position" << endl;
        }
        else{
            zobieprevious=false;
        }
        i++;
    }
}

int creature_society::no_of_good(int N){
    int good=0; 
    int i=0;
    while(i<N){
        if(crpointer[i]->is_a_good()){
            good++;
        }
        i++;
    }
    return good;
}

int creature_society::no_of_zobies(int N){
    int zobies=0, i=0;
    while(i<N){
        if(crpointer[i]->is_a_zobie()){
            zobies++;
        }
        i++;
    }
    return zobies;
}

/////////////////good_creature/////////////////

void good_creature::bless(){
    if (!this->is_a_zobie()){
        life++;
        cout << "The good creature " << this->get_name() << this->get_pos() << " has been blessed." << endl;
        if(life>good_thrsh){
            msociety->clone_next(pos);
        }
    }
    else{
        cout << "Found zobie at position:"<< pos<<endl;
    }
}

creature* good_creature::clone(const creature& cr,int position){
    creature* newcr;
    if(cr.is_a_good()){
        newcr =new good_creature(cr.get_name(),0,cr.get_life(),cr.get_thrsh(),cr.get_pointer());
        cout << "Just copied the good creature " << newcr->get_name() << newcr->get_pos() << " to the next position" << endl;
    }
    else{
        newcr=new bad_creature(cr.get_name(),0,cr.get_life(),cr.get_thrsh(),cr.get_pointer());
        cout << "Just copied the bad creature " << newcr->get_name() << newcr->get_pos() << " to the next position" << endl;
    }
    return newcr;
}

good_creature::~good_creature(){
    delete[] name;              //delete the pointers of creature cause of virtual destructor
    delete msociety;
}

/////////////////bad_creature/////////////////

void bad_creature::bless(){        
    if(!this->is_a_zobie()){
        life++;
        cout << "The bad creature " << this->get_name() << this->get_pos() << " has been blessed." << endl;
        if(life>bad_thrsh){
            msociety->clone_zobies(pos);
        }
    }
    else{
        cout << "Found zobie at position:"<< pos<<endl;
    }
}

creature* bad_creature::clone(const creature& cr, int position){
    creature* newcr;
    if(cr.is_a_good()==true){
        newcr =new good_creature(cr.get_name(),position+1,cr.get_life(),cr.get_thrsh(),cr.get_pointer());
        cout << "Just copied the good creature " << newcr->get_name() << newcr->get_pos() << " to the next position" << endl;
    }    
    else{
        newcr=new bad_creature(cr.get_name(),position+1,cr.get_life(),cr.get_thrsh(),cr.get_pointer());
        cout << "Just copied the bad creature " << newcr->get_name() << newcr->get_pos() << " to the next position" << endl;
    }
    return newcr;
}

bad_creature::~bad_creature(){
    delete[] name;
    delete msociety;
}
