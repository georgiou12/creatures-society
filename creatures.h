#include <iostream>
#include <cstring>

using namespace std;

class creature_society;

class creature{
    protected:
        char* name;
        int life;
        int pos=0;
        creature_society* msociety;
    public:
        creature(const char* nname,int position, int L,creature_society* society):pos(position),life(L),msociety(society){
                        name =new char[strlen(nname)+1]; strcpy(name,nname);};
        virtual ~creature(){};
        bool is_a_zobie(){if(life==0) return true; else return false;}
        virtual bool is_a_good()const=0;
        virtual creature* clone(const creature&, int)=0;
        virtual void bless()=0;
        virtual void beat()=0;
        virtual int get_thrsh()const=0;
        const char* get_name()const{return name;};
        int get_life()const{return life;};
        int get_pos()const{return pos;};
        creature_society* get_pointer()const{return msociety;};
};

class good_creature : public creature{
    int good_thrsh;
    public:
        good_creature(const char* nname,int pos,int L,int thrsh,creature_society* society):good_thrsh(thrsh),creature(nname,pos,L,society){
            cout << "Just created a good_creature with name:"<< this->get_name() << this->get_pos() << endl;};
        virtual ~good_creature();
        creature* clone(const creature&, int);
        virtual void bless();
        virtual void beat(){
            if(is_a_zobie()==false){
                life--;
                cout << "The good creature " << this->get_name()<< this->get_pos() << " has been beaten." << endl;
            }
            else{
                cout << "Found zobie at postion:"<<pos<<endl;
            }
        };
        bool is_a_good()const{return true;};
        int get_thrsh()const{return this->good_thrsh;};
};

class bad_creature : public creature{
    int bad_thrsh;
    public:
        bad_creature(const char* nname,int pos, int L, int thrsh,creature_society* society):bad_thrsh(thrsh),creature(nname,pos,L,society){
            cout << "Just created a bad_creature with name:"<< this->get_name() << this->get_pos()  << endl;};
        ~bad_creature();
        creature* clone(const creature&, int);
        virtual void bless();
        virtual void beat(){
            if(is_a_zobie()==false){
                life--;
                cout << "The bad creature " << this->get_name() << this->get_pos() << " has been beaten." << endl;
            }
            else{
                cout << "Found zobie at position:"<< pos<<endl;
            }
        };
        bool is_a_good()const{return false;};
        int get_thrsh()const{return this->bad_thrsh;};
};


class creature_society{
        int crowd;
        creature** crpointer;
        creature** society;
    public:
        creature_society(int, int, int, int);
        void bless(int i){crpointer[i]->bless();};
        void beat(int i){crpointer[i]->beat();};
        void clone_next(int);
        void clone_zobies(int);
        int no_of_good(int);
        int no_of_zobies(int);
};
