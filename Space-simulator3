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
        vector<Asteroid> w;
        for(int it=v.size()-1;it>=0;it--)
        {
            w.push_back(v[it]);
        }
        v=w;
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
};

class Base
{
private:
    string name:
    int area;
public:
    string get_name()
    {
        return name;
    }
    Base(string nam,int ar)
    {
        name=nam;
        area=ar;
    }
};

class Colonist
{
private:
    string name;
public:
    string get_name()
    {
        return name;
    }
    Colonist(string nam)
    {
        name=nam;
    }
};

class Universe  ///singleton
{
private:
    Universe() {}
    vector<Star> stars;
    vector<Ship> ships;
    vector<Crew> crews;
    vector<Colonist> colonists;
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
    void assign_crew(Crew* cr,Ship* sh)
    {
        ship_of_crew[cr]=sh;
    }
    void addColonist(Colonist colonist)
    {
        colonists.push_back(colonist);
    }
    Colonist* get_colonist_pointer(int nr)
    {
        return &colonists[nr-1];
    }
    int get_number_of_colonists()
    {
        return colonists.size();
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
        cout<<"Insert rotation number:\n";
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
        if(op==1)
        {
            string nam;
            int temp;
            cout<<"Star's name:\n";
            cin>>nam;
            cout<<"Star's temperature:\n";
            cin>>temp;
            Star st(nam,temp);
            Universe& universe=Universe::getInstance();
            universe.addStar(st);
            cout<<"Index of star: "<<universe.get_number_of_stars()<<"\n";
        }
        if(op==2)
        {
            string nam;
            int pop;
            int star_index;
            cout<<"Index of star around which this planet orbits:\n";
            cin>>star_index;
            cout<<"Planet's name:\n";
            cin>>nam;
            cout<<"Planet's population:\n";
            cin>>pop;
            Planet pl(nam,pop);
            Universe& universe=Universe::getInstance();
            universe.get_star_pointer(star_index)->get_orbit_pointer()->add(pl);
            cout<<"Index of star: "<<star_index<<"\n";
            cout<<"Index of planet: "<<universe.get_star_pointer(star_index)->get_orbit_pointer()->get_cardinal()<<"\n";
        }
        if(op==3)
        {
            string nam;
            int planet_index;
            int star_index;
            cout<<"Index of star that is orbited by the planet that is orbited by the asteroid:\n";
            cin>>star_index;
            cout<<"Index of planet that is orbited by the asteroid:\n";
            cin>>planet_index;
            cout<<"Asteroid's name:\n";
            cin>>nam;
            Asteroid as(nam);
            Universe& universe=Universe::getInstance();
            universe.get_star_pointer(star_index)->get_orbit_pointer()->get_element_pointer(planet_index)->get_orbit_pointer()->add(as);
        }
        if(op==4)
        {
            string nam;
            string loc;
            cout<<"Ship's name:\n";
            cin>>nam;
            cout<<"Ship's location:\n";
            cin>>loc;
            Ship sh(nam,loc);
            Universe& universe=Universe::getInstance();
            universe.addShip(sh);
            cout<<"Index of ship: "<<universe.get_number_of_ships()<<"\n";
        }
        if(op==5)
        {
            string nam;
            string loc;
            cout<<"Crew member's name:\n";
            cin>>nam;
            cout<<"Crew member's location:\n";
            cin>>loc;
            Crew cr(nam,loc);
            Universe& universe=Universe::getInstance();
            universe.addCrew(cr);
            cout<<"Index of crew: "<<universe.get_number_of_crews()<<"\n";
        }
        if(op==6)///insert colonist with a new base
        {
            string colonist_name;
            string base_name;
            int area;
            cout<<"Colonist's name:\n";
            cin>>colonist_name;
            cout<<"Name of base:\n";
            cin>>base_name;
            cout<<"Area of base:\n";
            cin>>area;
            unique_ptr<Colonist> cptr=make_unique<Colonist>(colonist_name);
            ///THERE IS A LOT TO FIX
        }
        if(op==7)///insert colonist with existing base
        {

        }
        if(op==11)
        {
            int star_index;
            int planet_index;
            int code;
            Shuffler automata;
            cout<<"Index of star that is orbited by the planet:\n";
            cin>>star_index;
            cout<<"Index of planet:\n";
            cin>>planet_index;
            cout<<"1-Pair shuffling\n2-Reverse shuffling\n3-Random shuffling\nChoose shuffling method:\n";
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
        if(op==12)
        {
            int ship_index;
            int crew_index;
            cout<<"Index of ship:\n";
            cin>>ship_index;
            cout<<"Index of crew:\n";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            Crew* cr=universe.get_crew_pointer(crew_index);
            cr->add_to_ship(ship_index);
        }
        if(op==13)
        {
            int ship_index;
            string loc;
            cout<<"Index of ship:\n";
            cin>>ship_index;
            cout<<"New location:\n";
            cin>>loc;
            Universe& universe=Universe::getInstance();
            Ship* sh=universe.get_ship_pointer(ship_index);
            sh->change_location(loc);
        }
        if(op==16)//capitalize star
        {
            int star_index;
            cout<<"Index of star:\n";
            cin>>star_index;
            Universe& universe=Universe::getInstance();
            Star* st=universe.get_star_pointer(star_index);
            Capitalize(st);
        }
        if(op==17)//capitalize planet
        {
            int star_index;
            int planet_index;
            cout<<"Index of star that is orbited by the planet:\n";
            cin>>star_index;
            cout<<"Index of planet:\n";
            cin>>planet_index;
            Universe& universe=Universe::getInstance();
            Planet* pl=universe.get_star_pointer(star_index)->get_orbit_pointer()->get_element_pointer(planet_index);
            Capitalize(pl);
        }
        if(op==21)
        {
            int star_index;
            int planet_index;
            cout<<"Index of star that is orbited by the planet:\n";
            cin>>star_index;
            cout<<"Index of planet:\n";
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
        if(op==22)
        {
            int star_index;
            cout<<"Index of star:\n";
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
        if(op==24)
        {
            int ship_index;
            cout<<"Index of ship:\n";
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
        if(op==25)
        {
            int crew_index;
            cout<<"Index of crew member:\n";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            Crew* cr=universe.get_crew_pointer(crew_index);
            cout<<"Crew member's name: "<<cr->get_name()<<"\n";
            cout<<"Crew member's location: "<<cr->get_location()<<"\n";
        }
        if(op==26)
        {
            int crew_index;
            cout<<"Index of crew member:\n";
            cin>>crew_index;
            Universe& universe=Universe::getInstance();
            Ship* sh=universe.get_ship_pointer_of_crew(crew_index);
            cout<<"Crew member's ship: "<<sh->get_name()<<"\n";
        }
        if(op==31)
        {
            int star_index;
            cout<<"Index of star:\n";
            cin>>star_index;
            Orbiter(star_index);
        }
    }
}
