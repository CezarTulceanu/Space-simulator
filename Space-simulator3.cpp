#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<chrono>
#include<memory>
#include<queue>
#include<map>
#include<unistd.h>
#include<cmath>
#include<string>
#include<cctype>
using namespace std;

class Star;

class Planet;

class Crew;

class Ship;

class Universe;

class Asteroid
{
private:
    string name;
public:
    string get_name()
    {
        return name;
    }
    Asteroid(){}
    Asteroid(string nam)
    {
        name=nam;
    }
};

template <typename T>
class Orbit
{
private:
    vector<T> orbit;
public:
    void rotate_backwards()
    {
        if(orbit.size()<=1)
        {
            return;
        }
        T aux=orbit[0];
        for(int it=0;it<orbit.size()-1;it++)
        {
            orbit[it]=orbit[it+1];
        }
        orbit[orbit.size()-1]=aux;
    }
    void rotate_forward()
    {
        if(orbit.size()<=1)
        {
            return;
        }
        T aux=orbit[orbit.size()-1];
        for(int it=orbit.size()-2;it>=0;it--)
        {
            orbit[it+1]=orbit[it];
        }
        orbit[0]=aux;
    }
    void add(T el)
    {
        orbit.push_back(el);
    }
    T* get_element_pointer(int nr)
    {
        return &orbit[nr-1];
    }
    int get_cardinal()
    {
        return orbit.size();
    }
    vector<T>* get_vector_pointer()
    {
        return &orbit;
    }
    Orbit(){}
};

class Star
{
private:
    string name;
    int temperature;
    Orbit<Planet> orbit;
public:
    string get_name()
    {
        return name;
    }
    void set_name(string nam)
    {
        name=nam;
    }
    int get_temperature()
    {
        return temperature;
    }
    Star(){}
    Orbit<Planet>* get_orbit_pointer()
    {
        return &orbit;
    }
    Star(string str,int temp)
    {
        name=str;
        temperature=temp;
    }
};

class Planet
{
private:
    string name;
    int population;
    Orbit<Asteroid> orbit;
public:
    string get_name()
    {
        return name;
    }
    void set_name(string nam)
    {
        name=nam;
    }
    int get_population()
    {
        return population;
    }
    Planet(string str,int pop)
    {
        name=str;
        population=pop;
    }
    Orbit<Asteroid>* get_orbit_pointer()
    {
        return &orbit;
    }
};

template <typename T>
class shuffle_strategy    ///strategy
{
public:
    virtual void shuffled(vector<T> &v)=0;
};

class pair_shuffle : public shuffle_strategy<Asteroid>
{
public:
    void shuffled(vector<Asteroid> &v) override {
        Asteroid aux;
        for(int it=1;it<v.size();it+=2)
        {
            aux=v[it];
            v[it]=v[it-1];
            v[it-1]=aux;
        }
    }
};

class reverse_shuffle : public shuffle_strategy<Asteroid> {
public:
    void shuffled(vector<Asteroid> &v) override {
        reverse(v.begin(),v.end());
    }
};

class random_shuffle_strategy : public shuffle_strategy<Asteroid> {
public:
    void shuffled(vector<Asteroid> &v) override {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 g(seed);
        shuffle(v.begin(), v.end(), g);
    }
};

class Shuffler
{
private:
    shuffle_strategy<Asteroid>* strategy;
public:
    Shuffler(shuffle_strategy<Asteroid>* strat=nullptr) : strategy(strat) {}

    void set_strategy(shuffle_strategy<Asteroid>* strat) {
        strategy = strat;
    }

    void shuffled(Planet& pl) {
        if (strategy) {
            vector<Asteroid>* ptr=pl.get_orbit_pointer()->get_vector_pointer();
            vector<Asteroid>& act= *ptr;
            strategy->shuffled(act);
        }
    }
};

class Observer {   ///observer
public:
    virtual void update(string loc)=0;
};

class Subject {
protected:
    vector<Observer*> observers;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        auto it=find(observers.begin(), observers.end(), observer);
        if(it!=observers.end())
        {
            observers.erase(it);
        }
    }

    void notify(string loc) {
        for (Observer* observer : observers) {
            observer->update(loc);
        }
    }
};

class Ship : public Subject {
private:
    string name;
    string location;
public:
    Ship(string nam,string loc){
        name=nam;
        location=loc;
    }

    void change_location(string loc) {
        location=loc;
        notify(loc);
    }
    string get_name() {
        return name;
    }
    void set_name(string nam)
    {
        name=nam;
    }
    string get_location()
    {
        return location;
    }
    auto get_crew_pointers()
    {
        return observers;
    }
};


class Crew : public Observer {
private:
    string name;
    string location;
public:
    Crew(string nam,string loc)
    {
        name=nam;
        location=loc;
    }

    void update(string loc) override {
        location=loc;
    }
    string get_name()
    {
        return name;
    }
    void set_name(string nam)
    {
        name=nam;
    }
    string get_location()
    {
        return location;
    }
    void add_to_ship(int nr);
    void remove_from_ship();
};

class Base
{
private:
    string name;
    int area;
public:
    string get_name()
    {
        return name;
    }
    int get_area()
    {
        return area;
    }
    Base(string nam,int ar) : name(nam),area(ar){}
    ~Base(){}
};

class Colonist
{
private:
    string name;
    shared_ptr<Base> bptr=nullptr;
public:
    string get_name()
    {
        return name;
    }
    shared_ptr<Base> get_base_pointer()
    {
        return bptr;
    }
    Colonist(string nam,shared_ptr<Base> bas) : name(nam),bptr(bas){}
    ~Colonist(){}
};

class Universe  ///singleton
{
private:
    Universe() {}
    vector<Star> stars;
    vector<Ship> ships;
    vector<Crew> crews;
    vector<unique_ptr<Colonist>> colonist_pointers;
    map<Crew*,Ship*> ship_of_crew;
    Universe(const Universe&) = delete;
    Universe& operator=(const Universe&) = delete;
public:
    static Universe& getInstance() {
        static Universe instance;
        return instance;
    }
    void addStar(Star star)
    {
        stars.push_back(star);
    }
    Star* get_star_pointer(int nr)
    {
        return &stars[nr-1];
    }
    int get_number_of_stars()
    {
        return stars.size();
    }
    void addShip(Ship ship)
    {
        ships.push_back(ship);
    }
    Ship* get_ship_pointer(int nr)
    {
        return &ships[nr-1];
    }
    int get_number_of_ships()
    {
        return ships.size();
    }
    void addCrew(Crew crew)
    {
        crews.push_back(crew);
    }
    Crew* get_crew_pointer(int nr)
    {
        return &crews[nr-1];
    }
    int get_number_of_crews()
    {
        return crews.size();
    }
    Ship* get_ship_pointer_of_crew(int nr)
    {
        return ship_of_crew[get_crew_pointer(nr)];
    }
    Ship* get_ship_pointer_of_crew_cool(Crew* cr)
    {
        return ship_of_crew[cr];
    }
    void assign_crew(Crew* cr,Ship* sh)
    {
        ship_of_crew[cr]=sh;
    }
    void disassign_crew(Crew* cr,Ship* sh)
    {
        ship_of_crew[cr]=nullptr;
    }
    void addColonist_pointer(unique_ptr<Colonist> cptr)
    {
        colonist_pointers.push_back(move(cptr));
    }
    string get_colonist_name(int nr)
    {
        return colonist_pointers[nr-1]->get_name();
    }
    shared_ptr<Base> get_colonist_base_pointer(int nr)
    {
        return colonist_pointers[nr-1]->get_base_pointer();
    }
    int get_number_of_colonists()
    {
        return colonist_pointers.size();
    }
    void remove_colonist(int nr)
    {
        colonist_pointers[nr-1]=nullptr;
    }
};

void Crew::add_to_ship(int nr)
{
        Universe& universe=Universe::getInstance();
        Ship* sh=universe.get_ship_pointer(nr);
        sh->attach(this);
        universe.assign_crew(this,sh);
        update(sh->get_location());
}

void Crew::remove_from_ship()
{
        Universe& universe=Universe::getInstance();
        Ship* sh=universe.get_ship_pointer_of_crew_cool(this);
        sh->detach(this);
        universe.disassign_crew(this,sh);
}

void Orbiter(int star_index)
{
    Universe& universe=Universe::getInstance();
    Star* st=universe.get_star_pointer(star_index);
    unique_ptr<Star> starPtr=make_unique<Star>(st->get_name(),st->get_temperature());
    vector<Planet>* vptr=st->get_orbit_pointer()->get_vector_pointer();
    vector<Planet>* newvptr=starPtr->get_orbit_pointer()->get_vector_pointer();
    for(auto w: *vptr)
    {
        newvptr->push_back(w);
    }
    int rot=1;
    cout<<"The planets that orbit the star "<<starPtr->get_name()<<" are:\n";
    for(auto w: *newvptr)
    {
        cout<<"  "<<w.get_name()<<"\n";
    }
    while(true)
    {
        cout<<"Insert rotation number: ";
        cin>>rot;
        if(rot==0)
        {
            break;
        }
        else if(rot>0)
        {
            for(int itt=1;itt<=rot;itt++)
            {
                starPtr->get_orbit_pointer()->rotate_forward();
            }
        }
        else
        {
            for(int itt=1;itt<=-rot;itt++)
            {
                starPtr->get_orbit_pointer()->rotate_backwards();
            }
        }
        cout<<"The planets that orbit the star "<<starPtr->get_name()<<" after the rotation are:\n";
        for(auto w: *newvptr)
        {
            cout<<"  "<<w.get_name()<<"\n";
        }
    }
}

string capital(string str) {
    for(int it=0;it<str.size();it++)
    {
        str[it]=toupper(str[it]);
    }
    return str;
}

template <typename T>
void Capitalize(T* obj)
{
    obj->set_name(capital(obj->get_name()));
}

int main()
{
    int op;
    while(true)
    {
        cout<<"Insert action code: ";
        cin>>op;
        if(op==0)
        {
            break;
        }
        if(op==1) ///Insert star
        {
            string nam;
            int temp;
            cout<<"Star's name: ";
            cin>>nam;
            cout<<"Star's temperature: ";
            cin>>temp;
            Star st(nam,temp);
            Universe& universe=Universe::getInstance();
            universe.addStar(st);
            cout<<"Index of star: "<<universe.get_number_of_stars()<<"\n";
        }
        if(op==2) ///Insert planet
        {
            string nam;
            int pop;
            int star_index;
            cout<<"Index of star around which this planet orbits: ";
            cin>>star_index;
            cout<<"Planet's name: ";
            cin>>nam;
            cout<<"Planet's population: ";
            cin>>pop;
            Planet pl(nam,pop);
            Universe& universe=Universe::getInstance();
            universe.get_star_pointer(star_index)->get_orbit_pointer()->add(pl);
            cout<<"Index of star: "<<star_index<<"\n";
            cout<<"Index of planet: "<<universe.get_star_pointer(star_index)->get_orbit_pointer()->get_cardinal()<<"\n";
        }
        if(op==3)  ///Insert asteroid
        {
            string nam;
            int planet_index;
            int star_index;
            cout<<"Index of star that is orbited by the planet that is orbited by the asteroid: ";
            cin>>star_index;
            cout<<"Index of planet that is orbited by the asteroid: ";
            cin>>planet_index;
            cout<<"Asteroid's name: ";
            cin>>nam;
            Asteroid as(nam);
            Universe& universe=Universe::getInstance();
            universe.get_star_pointer(star_index)->get_orbit_pointer()->get_element_pointer(planet_index)->get_orbit_pointer()->add(as);
        }
        if(op==4) ///Insert ship
        {
            string nam;
            string loc;
            cout<<"Ship's name: ";
            cin>>nam;
            cout<<"Ship's location: ";
            cin>>loc;
            Ship sh(nam,loc);
            Universe& universe=Universe::getInstance();
            universe.addShip(sh);
            cout<<"Index of ship: "<<universe.get_number_of_ships()<<"\n";
        }
        if(op==5) ///Insert crew member
        {
            string nam;
            string loc;
            cout<<"Crew member's name: ";
            cin>>nam;
            cout<<"Crew member's location: ";
            cin>>loc;
            Crew cr(nam,loc);
            Universe& universe=Universe::getInstance();
            universe.addCrew(cr);
            cout<<"Index of crew: "<<universe.get_number_of_crews()<<"\n";
        }
        if(op==6)/// Insert colonist with a new base
        {
            string colonist_name;
            string base_name;
            int area;
            cout<<"Colonist's name: ";
            cin>>colonist_name;
            cout<<"Name of base: ";
            cin>>base_name;
            cout<<"Area of base: ";
            cin>>area;
            Universe& universe=Universe::getInstance();
            universe.addColonist_pointer(make_unique<Colonist>(colonist_name,make_shared<Base>(base_name,area)));
            cout<<"Index of colonist: "<<universe.get_number_of_colonists()<<"\n";
        }
        if(op==7)  ///Insert colonist with existing base
        {
            string colonist_name;
            int colonist_index;
            cout<<"Colonist's name: ";
            cin>>colonist_name;
            cout<<"Index of a colonist that is already located in the base: ";
            cin>>colonist_index;
            Universe& universe=Universe::getInstance();
            universe.addColonist_pointer(make_unique<Colonist>(colonist_name,universe.get_colonist_base_pointer(colonist_index)));
            cout<<"Index of colonist: "<<universe.get_number_of_colonists()<<"\n";
        }
        if(op==11)  ///Shuffle asteroids of a planet
        {
            int star_index;
            int planet_index;
            int code;
            Shuffler automata;
            cout<<"Index of star that is orbited by the planet: ";
            cin>>star_index;
            cout<<"Index of planet: ";
            cin>>planet_index;
            cout<<"1-Pair shuffling\n2-Reverse shuffling\n3-Random shuffling\nChoose shuffling method: ";
            cin>>code;
            if(code==1)
            {
                pair_shuffle stra;
                automata.set_strategy(&stra);
            }
            else if(code==2)
            {
                reverse_shuffle stra;
                automata.set_strategy(&stra);
            }
            else
            {
                random_shuffle_strategy stra;
                automata.set_strategy(&stra);
            }
            Universe& universe=Universe::getInstance();
            Planet* ptr=universe.get_star_pointer(star_index)->get_orbit_pointer()->get_element_pointer(planet_index);
            Planet& act= *ptr;
            automata.shuffled(act);
        }
        if(op==12)  ///Add crew member to ship
        {
            int ship_index;
            int crew_index;
            cout<<"Index of ship: ";
            cin>>ship_index;
            cout<<"Index of crew: ";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            Crew* cr=universe.get_crew_pointer(crew_index);
            cr->add_to_ship(ship_index);
        }
        if(op==13)  ///Change location of ship
        {
            int ship_index;
            string loc;
            cout<<"Index of ship: ";
            cin>>ship_index;
            cout<<"New location: ";
            cin>>loc;
            Universe& universe=Universe::getInstance();
            Ship* sh=universe.get_ship_pointer(ship_index);
            sh->change_location(loc);
        }
        if(op==14) ///Remove crew member from ship
        {
            int crew_index;
            cout<<"Index of crew: ";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            universe.get_crew_pointer(crew_index)->remove_from_ship();
        }
        if(op==16)///Capitalize star name
        {
            int star_index;
            cout<<"Index of star: ";
            cin>>star_index;
            Universe& universe=Universe::getInstance();
            Star* st=universe.get_star_pointer(star_index);
            Capitalize(st);
        }
        if(op==17)///Capitalize planet name
        {
            int star_index;
            int planet_index;
            cout<<"Index of star that is orbited by the planet: ";
            cin>>star_index;
            cout<<"Index of planet: ";
            cin>>planet_index;
            Universe& universe=Universe::getInstance();
            Planet* pl=universe.get_star_pointer(star_index)->get_orbit_pointer()->get_element_pointer(planet_index);
            Capitalize(pl);
        }
        if(op==18) ///Remove colonist
        {
            int colonist_index;
            cout<<"Index of colonist: ";
            cin>>colonist_index;
            Universe& universe=Universe::getInstance();
            universe.remove_colonist(colonist_index);
            cout<<"The colonist has been removed and it's allocated memory has been freed\n";
        }
        if(op==21) ///Show planet info
        {
            int star_index;
            int planet_index;
            cout<<"Index of star that is orbited by the planet: ";
            cin>>star_index;
            cout<<"Index of planet: ";
            cin>>planet_index;
            Universe& universe=Universe::getInstance();
            Planet* ptr=universe.get_star_pointer(star_index)->get_orbit_pointer()->get_element_pointer(planet_index);
            Planet& act= *ptr;
            cout<<"Name of planet: "<<act.get_name()<<"\n";
            cout<<"Population: "<<act.get_population()<<"\n";
            cout<<"Asteroids that orbit the planet in order:\n";
            vector<Asteroid>* ptrr=act.get_orbit_pointer()->get_vector_pointer();
            vector<Asteroid>& actt= *ptrr;
            for(auto w:actt)
            {
                cout<<w.get_name()<<"\n";
            }
        }
        if(op==22) ///Show star information
        {
            int star_index;
            cout<<"Index of star: ";
            cin>>star_index;
            Universe& universe=Universe::getInstance();
            Star* ptr=universe.get_star_pointer(star_index);
            Star& act= *ptr;
            cout<<"Name of star: "<<act.get_name()<<"\n";
            cout<<"Temperature: "<<act.get_temperature()<<"\n";
            cout<<"Planets that orbit the star in order:\n";
            vector<Planet>* ptrr=act.get_orbit_pointer()->get_vector_pointer();
            vector<Planet>& actt= *ptrr;
            for(auto w:actt)
            {
                cout<<w.get_name()<<"\n";
            }
        }
        if(op==23)  ///Show star information with planets in lexicographical order
        {
            int star_index;
            cout<<"Index of star: ";
            cin>>star_index;
            Universe& universe=Universe::getInstance();
            Star* ptr=universe.get_star_pointer(star_index);
            Star& act= *ptr;
            cout<<"Name of star: "<<act.get_name()<<"\n";
            cout<<"Temperature: "<<act.get_temperature()<<"\n";
            cout<<"Planets that orbit the star in order:\n";
            vector<Planet>* ptrr=act.get_orbit_pointer()->get_vector_pointer();
            vector<Planet>& actt= *ptrr;
            vector<string> nv;
            for(auto w:actt)
            {
                nv.push_back(w.get_name());
            }
            sort(nv.begin(),nv.end());
            for(auto w:nv)
            {
                cout<<w<<"\n";
            }
        }
        if(op==24) ///Show ship info
        {
            int ship_index;
            cout<<"Index of ship: ";
            cin>>ship_index;
            Universe& universe=Universe::getInstance();
            Ship* sh=universe.get_ship_pointer(ship_index);
            cout<<"Ship's name: "<<sh->get_name()<<"\n";
            cout<<"Ship's location: "<<sh->get_location()<<"\n";
            cout<<"Crew members on board:\n";
            for(auto w:sh->get_crew_pointers())
            {
                Crew* cr = dynamic_cast<Crew*>(w);
                cout<<cr->get_name()<<"\n";
            }
        }
        if(op==25) ///Show crew member info
        {
            int crew_index;
            cout<<"Index of crew member: ";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            Crew* cr=universe.get_crew_pointer(crew_index);
            cout<<"Crew member's name: "<<cr->get_name()<<"\n";
            cout<<"Crew member's location: "<<cr->get_location()<<"\n";
        }
        if(op==26) ///Show crew member's ship
        {
            int crew_index;
            cout<<"Index of crew member: ";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            Ship* sh=universe.get_ship_pointer_of_crew(crew_index);
            cout<<"Crew member's ship: "<<sh->get_name()<<"\n";
        }
        if(op==27) ///Show colonist's name
        {
            int colonist_index;
            cout<<"Index of colonist: ";
            cin>>colonist_index;
            Universe& universe=Universe::getInstance();
            cout<<"Colonist's name: "<<universe.get_colonist_name(colonist_index)<<"\n";
        }
        if(op==28) ///Show colonist's base's info
        {
            int colonist_index;
            cout<<"Index of colonist: ";
            cin>>colonist_index;
            Universe& universe=Universe::getInstance();
            cout<<"Name of base: "<<universe.get_colonist_base_pointer(colonist_index)->get_name()<<"\n";
            cout<<"Area of base: "<<universe.get_colonist_base_pointer(colonist_index)->get_area()<<"\n";
        }
        if(op==31) ///Show the orbit of a star after rotations
        {
            int star_index;
            cout<<"Index of star: ";
            cin>>star_index;
            Orbiter(star_index);
        }
    }
}
