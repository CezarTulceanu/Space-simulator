#include<iostream>
#include<fstream>
#include<queue>
#include<map>
#include<string>
#include<iterator>
using namespace std;

string name_of_ship[4]={"Intergalactic_cruiser","Commute_ship","Fighter_ship","Heavy_load_carrier"};

string star_of_type[6]={"Main sequence star","Red giant","Neutron star","White dwarf","Red dwarf","Brown dwarf"};

string description_of_ship[4]={"This enormous ship is able to carry up to 100000 citizens from one galaxy to another in the blink of an eye,thanks to the newly developed lightspeed travel technology",
"This small ship can carry up to 100 citizens from one planet to another within the same solar system",
"This highly technologized ship is able to move swiftly and silently across galaxies and is equiped with powerful weapons such as high power lasers, capable of dealing considerable damage to hostile entities. This ship only requiers a crew of 6 people, making it a highly versatile unit for all kinds of different missions",
"This gigantic ship is able to carry up to a few million tonens of cargo across galaxies, making it extremely important to the economic ecosystem of the universe"};

const int SHIP_TYPES=4;

const int STAR_TYPES=6;

int min_size_of_crew[4]={2000,4,6,100};

int max_size_of_crew[4]={5000,8,8,500};

int max_capacity_of_passangers[4]={100000,100,2,200};

class Spacecraft;
class Planet;
class Star;
class Solar_system;

map<int,Spacecraft> ship_of_id;

map<int,Spacecraft>::iterator it;

map<int,Star> star_of_id;

map<int,Planet> planet_of_id;

map<int,Solar_system> solar_system_of_id;

class Spacecraft {
private:
    int type_of_ship;
    int crew_size;
    int number_of_passangers;
    int ship_id;

public:

    int get_ship_id() const {
        return ship_id;
    }

    void set_ship_id(int var){
        ship_id=var;
        return;
    }

    Spacecraft& operator=(const Spacecraft& other) {
        type_of_ship=other.type_of_ship;
        crew_size=other.crew_size;
        number_of_passangers=other.number_of_passangers;
        ship_id=other.ship_id;
        return *this; // Return reference to the current object
    }


    // Constructor
    Spacecraft() {
        crew_size=0;
        type_of_ship=0;
        ship_id=0;
        number_of_passangers=0;

    }

    Spacecraft(int type,int crew, int passangers, int id) {
        crew_size=crew;
        type_of_ship=type;
        ship_id=id;
        number_of_passangers=passangers;
    }

    // Method to calculate empty passanger seats in spacecraft
    int number_of_empty_passanger_seats() {
        return max_capacity_of_passangers[type_of_ship]-number_of_passangers;
    }

    // Method to show the name of ship
    void show_name() {
        cout<<name_of_ship[type_of_ship]<<"\n";
        return;
    }

    // Method to sho the description of ship
    void show_description() {
        cout<<description_of_ship[type_of_ship]<<"\n";
        return;
    }

    void insert_to_map() {
        ship_of_id[ship_id]=*this;
    }


    friend ostream& operator<<(ostream& cout, const Spacecraft& obj) {
        cout << "Ship type: " << name_of_ship[obj.type_of_ship] << "\nSize of crew: " << obj.crew_size << "\nNumber of passangers: " << obj.number_of_passangers<<"\nId of ship: "<<obj.ship_id<<"\n";
        return cout;
    }

    friend istream& operator>>(istream& cin, Spacecraft& obj) {
        string s;
        int as=0;
        cout<<"Type of ship: ";
        cin>>s;
        for(int i=0;i<SHIP_TYPES;i++)
        {
            if(s==name_of_ship[i])
            {
                as=1;
                obj.type_of_ship=i;
                break;
            }
        }
        if(as==0)
        {
            cout<<"There is no such type of ship in the database\n";
            return cin;
        }
        cout<<"Size of crew: ";
        cin>>obj.crew_size;
        cout<<"Number of passangers: ";
        cin>>obj.number_of_passangers;
        cout<<"Id of ship: ";
        cin>>obj.ship_id;
        return cin;
    }

    void update()
    {
        *this=ship_of_id[ship_id];
    }
};


class Planet {
private:
    string name;
    int population;
    int number_of_ships;
    vector<Spacecraft> ships;
    int planet_id;


public:
    // Constructor
    Planet() {
        vector<Spacecraft> sh;
        population=0;
        number_of_ships=0;
        ships=sh;
        planet_id=0;
    }

    Planet(int pop,int num_of_ships, vector<Spacecraft> sh , int id) {
        population=pop;
        number_of_ships=num_of_ships;
        ships=sh;
        planet_id=id;
    }

    Planet& operator=(const Planet& other) {
        name=other.name;
        population=other.population;
        number_of_ships=other.number_of_ships;
        ships=other.ships;
        planet_id=other.planet_id;
        return *this; // Return reference to the current object
    }


    vector<Spacecraft> get_ships() const {
        return ships;
    }
    void set_planet_id(int id)
    {
        planet_id=id;
        return;
    }

    int get_planet_id()
    {
        return planet_id;
    }

    int get_population()
    {
        return population;
    }

    void insert_to_map() {
        planet_of_id[planet_id]=*this;
    }

    void update()
    {
        *this=planet_of_id[planet_id];
        for(auto w:ships)
        {
            w.update();
        }
    }

    void add_ship_of_id(int id)
    {
        ships.push_back(ship_of_id[id]);
        number_of_ships++;
    }

    friend ostream& operator<<(ostream& cout, const Planet& obj) {
        int ct=1;
        cout <<"Name of planet: "<<obj.name<<"\nPopulation: " << obj.population << "\nNumber of ships stationed on this planet: " << obj.number_of_ships << "\nShips that are stationed on this planet:\n";
        for(auto w:obj.ships)
        {
            cout<<"Ship #"<<ct<<"\n";
            cout << w;
            ct++;
        }
        cout<<"Id of planet: "<<obj.planet_id<<"\n";
        return cout;
    }

    friend istream& operator>>(istream& cin, Planet& obj) {
        Spacecraft ship;
        obj.ships.clear();
        int var;
        cout<<"Name of planet: ";
        cin>>obj.name;
        cout<<"Population: ";
        cin>>obj.population;
        cout<<"Number of ships stationed on this planet: ";
        cin>>obj.number_of_ships;
        for(int i=0;i<obj.number_of_ships;i++)
        {
            cout<<"Id of ship #"<<i+1<<": ";
            cin>>var;
            ship.set_ship_id(var);
            obj.ships.push_back(ship_of_id[ship.get_ship_id()]);
        }
        cout<<"Id of planet: ";
        cin>>obj.planet_id;
        return cin;
    }
};


class Star {
private:
    string name;
    int type;
    int age;
    int star_id;


public:
    // Constructor
    Star() {
        string s;
        type=0;
        age=0;
        star_id=0;
        name=s;
    }

    Star(string nam, int ty ,int ag,int id) {
        name=nam;
        type=ty;
        age=ag;
        star_id=id;
    }

    Star& operator=(const Star& other) {
        name=other.name;
        type=other.type;
        age=other.age;
        star_id=other.star_id;
        return *this; // Return reference to the current object
    }

    int get_star_age()
    {
        return age;
    }

    void insert_to_map() {
        star_of_id[star_id]=*this;
    }

    friend ostream& operator<<(ostream& cout, const Star& obj) {
        cout <<"Name of star: "<<obj.name<<"\nType of star: " << star_of_type[obj.type] << "\nAge of star: " << obj.age << "\nId of star: "<<obj.star_id<<"\n";
        return cout;
    }

    friend istream& operator>>(istream& cin, Star& obj) {
        cout <<"Name of star: ";
        cin>>obj.name;
        cout<<"Type of star: ";
        cin>>obj.type;
        cout<<"Age of star: ";
        cin>>obj.age;
        cout<<"Id of star: ";
        cin>>obj.star_id;
        return cin;
    }

    void update()
    {
        *this=star_of_id[star_id];
    }
};




class Solar_system {
private:
    string name;
    Star star;
    int number_of_planets;
    vector<Planet> planets;
    int solar_system_id;


public:
    // Constructor
    Solar_system() {
        string s;
        vector<Planet> vec;
        Star st;
        name=s;
        star=st;
        number_of_planets=0;
        planets=vec;
        solar_system_id=0;
    }

    Solar_system(string nam, Star st ,int num, vector<Planet> plan,int id) {
        name=nam;
        star=st;
        number_of_planets=num;
        planets=plan;
        solar_system_id=id;
    }

    Solar_system& operator=(const Solar_system& other) {
        name=other.name;
        star=other.star;
        number_of_planets=other.number_of_planets;
        planets=other.planets;
        solar_system_id=other.solar_system_id;
        return *this; // Return reference to the current object
    }

    void insert_to_map() {
        solar_system_of_id[solar_system_id]=*this;
    }

    void add_planet_of_id(int id)
    {
        planets.push_back(planet_of_id[id]);
        number_of_planets++;
    }

    int population_of_solar_system()
    {
        int sum=0;
        for(auto w:planets)
        {
            sum+=w.get_population();
        }
        return sum;
    }

    friend ostream& operator<<(ostream& cout, const Solar_system& obj) {
        int ct=1;
        cout <<"Name of solar system: "<<obj.name<<"\nCentral star of solar system:\n" << obj.star << "Number of planets contained by the solar system: " << obj.number_of_planets << "\nPlanets that are located in the solar system:\n";
        for(auto w:obj.planets)
        {
            cout<<"Planet #"<<ct<<"\n";
            cout << w;
            ct++;
        }
        cout<<"Id of solar sytem: "<<obj.solar_system_id<<"\n";
        return cout;
    }

    friend istream& operator>>(istream& cin, Solar_system& obj) {
        Planet plan;
        obj.planets.clear();
        int var;
        cout<<"Name of solar system: ";
        cin>>obj.name;
        cout<<"Id of central star of solar system: ";
        cin>>var;
        obj.star=star_of_id[var];
        cout<<"Number of planets contained by the solar system: ";
        cin>>obj.number_of_planets;
        for(int i=0;i<obj.number_of_planets;i++)
        {
            cout<<"Id of planet #"<<i+1<<": ";
            cin>>var;
            plan.set_planet_id(var);
            obj.planets.push_back(planet_of_id[plan.get_planet_id()]);
        }
        cout<<"Id of solar system: ";
        cin>>obj.solar_system_id;
        return cin;
    }
    void update()
    {
        *this=solar_system_of_id[solar_system_id];
        for(auto w:planets)
        {
            w.update();
        }
        star.update();
    }
};



int main() {
    Spacecraft ship;
    Planet planet;
    Star star;
    Solar_system system;
    int code,a,b,c;
    /*
    */
    while(true)
    {
        cout<<"Insert action code: ";
        cin>>code;
        if(code==1)
        {
            cin>>ship;
            ship.insert_to_map();
        }
        else if(code==2)
        {
            cin>>planet;
            planet.insert_to_map();
        }
        else if(code==3)
        {
            cin>>star;
            star.insert_to_map();
        }
        else if(code==4)
        {
            cin>>system;
            system.insert_to_map();
        }
        else if(code==5)
        {
            cin>>a;
            cout<<ship_of_id[a].number_of_empty_passanger_seats()<<"\n";
        }
        else if(code==6)
        {
            cin>>a;
            ship_of_id[a].show_name();
        }
        else if(code==7)
        {
            cin>>a;
            ship_of_id[a].show_description();
        }
        else if(code==8)
        {
            cin>>a;
            cout<<ship_of_id[a]<<"\n";
        }
        else if(code==9)
        {
            cin>>a;
            cout<<planet_of_id[a]<<"\n";
        }
        else if(code==10)
        {
            cin>>a>>b;
            solar_system_of_id[b].add_planet_of_id(a);
        }
        else if(code==11)
        {
            cin>>a>>b;
            planet_of_id[b].add_ship_of_id(a);
        }
        else if(code==12)
        {
            cin>>a;
            cout<<star_of_id[a].get_star_age()<<"\n";
        }
        else if(code==13)
        {
            cin>>a;
            cout<<star_of_id[a];
        }
        else if(code==14)
        {
            cin>>a;
            solar_system_of_id[a].update();
            cout<<solar_system_of_id[a];
        }
        else if(code==15)
        {
            cin>>a;
            cout<<solar_system_of_id[a].population_of_solar_system()<<"\n";
        }
    }
    return 0;
}
