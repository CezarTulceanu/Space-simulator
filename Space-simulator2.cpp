#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;



class Human
{
private:
    string name;
    int age;
    int height;
public:
    string get_name()
    {
        return name;
    }
    int get_age()
    {
        return age;
    }
    int get_height()
    {
        return height;
    }
    void set_name(string s)
    {
        name=s;
    }
    void set_age(int ag)
    {
        age=ag;
    }
    void set_height(int hei)
    {
        height=hei;
    }
    Human() {
        string ns;
        name=ns;
        age=0;
        height=0;
    }
    Human(string nam,int ag,int hei) {
        name=nam;
        age=ag;
        height=hei;
    }
};


class Engineer : public Human
{
private:
    int level; //experience in years;
public:
    int get_level()
    {
        return level;
    }
    void set_level(int lv)
    {
        level=lv;
    }
    Engineer() : Human() {
        level=0;
    }
    Engineer(string nam,int ag,int hei,int lvl) : Human(nam,ag,hei) {
        level=lvl;
    }
};


class Medical : public Human
{
private:
    int patients; //experience in years;
public:
    int get_patients()
    {
        return patients;
    }
    void set_patients(int pa)
    {
        patients=pa;
    }
    Medical() : Human() {
        patients=0;
    }
    Medical(string nam,int ag,int hei,int pat) : Human(nam,ag,hei) {
        patients=pat;
    }
};


class Doctor_has_zero_surgeries : public exception {
public:
    const char* what() const noexcept override {
        return "The doctor hasn't performed any surgeries yet\n";
    }
};


class Doctor : public Medical
{
private:
    static int total_surgeries;
    int surgeries;
    int succesful_surgeries;
public:
    static int get_total_surgeries()
    {
        return total_surgeries;
    }
    static void add_total_surgeries(int nr)///Add nr of surgeries to the total count that were done by doctors that are not registered
    {
        total_surgeries+=nr;
    }
    static void set_total_surgeries(int nr)
    {
        total_surgeries=nr;
    }
    int get_surgeries()
    {
        return surgeries;
    }
    void set_surgeries(int s)
    {
        total_surgeries=total_surgeries-surgeries+s;
        surgeries=s;
    }
    int get_succesful_surgeries()
    {
        return succesful_surgeries;
    }
    void set_succesful_surgeries(int s)
    {
        succesful_surgeries=s;
    }
    double calculate_succes_rate()
    {
        try
        {
            if(surgeries==0)
            {
                throw Doctor_has_zero_surgeries();
            }
            return (double)((double)(succesful_surgeries)/(double)(surgeries));
        }
        catch (const Doctor_has_zero_surgeries& e)
        {
            cout<< "Caught Doctor_has_zero_surgeries: " <<e.what()<<"\n";
            return 1;
        }
    }
    Doctor() : Medical() {
        total_surgeries=total_surgeries-surgeries;
        surgeries=0;
        succesful_surgeries=0;
    }
    Doctor(string nam,int ag,int hei,int pat,int sur,int suc_sur) : Medical(nam,ag,hei,pat) {
        total_surgeries=total_surgeries-surgeries+sur;
        surgeries=sur;
        succesful_surgeries=suc_sur;
    }
};

class Nurse : public Medical
{
private:
    double rating;
public:
    int get_rating()
    {
        return rating;
    }
    void set_rating(double ra)
    {
        rating=(double)(ra);
    }
    Nurse() : Medical() {
        rating=0;
    }
    Nurse(string nam,int ag,int hei,int pat,double rat) : Medical(nam,ag,hei,pat) {
        rating=rat;
    }
};

class Crew : public Human
{
protected:
    int experience; //experience in years;
public:
    int get_experience()
    {
        return experience;
    }
    void set_experience(int ex)
    {
        experience=ex;
    }
    virtual int calculate_value()=0;
    Crew() : Human() {
        experience=0;
    }
    Crew(string nam,int ag,int hei,int exp) : Human(nam,ag,hei) {
        experience=exp;
    }
};

class Pilot : public Crew
{
private:
    int flights;
    int succesful_landings;
public:
    int get_flights()
    {
        return flights;
    }
    void set_flights(int fl)
    {
        flights=fl;
    }
    void set_succesful_landings(int fl)
    {
        succesful_landings=fl;
    }
    int get_succesful_landings()
    {
        return succesful_landings;
    }
    int calculate_value() override {
        return experience*flights;
    }
    Pilot() : Crew() {
        flights=0;
        succesful_landings=0;
    }
    Pilot(string nam,int ag,int hei,int exp,int fli,int suc_land) : Crew(nam,ag,hei,exp) {
        flights=fli;
        succesful_landings=suc_land;
    }
};

class Cabin : public Crew
{
private:
    double rating;
    int number_of_passengers_flown;
public:
    int get_rating()
    {
        return rating;
    }
    void set_rating(int ra)
    {
        rating=ra;
    }
    int calculate_value() override {
        return experience*number_of_passengers_flown;
    }
    Cabin() : Crew() {
        rating=0;
        number_of_passengers_flown=0;
    }
    Cabin(string nam,int ag,int hei,int exp,double rat,int nr) : Crew(nam,ag,hei,exp) {
        rating=rat;
        number_of_passengers_flown=nr;
    }
};

class Space_object
{
private:
    string name;
    int age;
protected:
    int get_age()
    {
        return age;
    }
public:
    void set_age(int ag)
    {
        age=ag;
    }
    string get_name()
    {
        return name;
    }
    virtual int calculate_coeficient_of_usability()=0;
    Space_object() {
        string s;
        name=s;
        age=0;
    }
    Space_object(string nam,int ag) {
        name=nam;
        age=ag;
    }
};

class Nonpositive_radius : public exception {
public:
    const char* what() const noexcept override {
        return "The radius must be a positive number\n";
    }
};

class Star : public Space_object
{
private:
    int temperature;
    int radius;
public:
    int get_temperature()
    {
        return temperature;
    }
    void set_temperature(int te)
    {
        temperature=te;
    }
    int get_radius()
    {
        return radius;
    }
    void set_radius(int ra)
    {
        try
        {
            if(ra<0)
            {
                throw Nonpositive_radius();
            }
            radius=ra;
        }
        catch (const Nonpositive_radius& e)
        {
            cout<< "Caught Nonpositive_radius: " <<e.what()<<"\n";
            radius=-ra;
        }
    }
    int calculate_coeficient_of_usability() override {
        return radius*radius*temperature/get_age();
    }
    Star() : Space_object() {
        temperature=0;
        radius=0;
    }
    Star(string nam,int ag,int temp,int ra) : Space_object(nam,ag) {
        temperature=temp;
        try
        {
            if(ra<0)
            {
                throw Nonpositive_radius();
            }
            radius=ra;
        }
        catch (const Nonpositive_radius& e)
        {
            cout<< "Caught Nonpositive_radius: " <<e.what()<<"\n";
            radius=-ra;
        }
    }
};

class Planet : public Space_object
{
private:
    int population;
    int development_level;
public:
    int get_population()
    {
        return population;
    }
    void set_population(int po)
    {
        population=po;
    }
    int get_development_level()
    {
        return development_level;
    }
    void set_development_level(int dl)
    {
        development_level=dl;
    }
    int calculate_coeficient_of_usability() override {
        return development_level*development_level*development_level*population;
    }
    Planet() : Space_object() {
        population=0;
        development_level=0;
    }
    Planet(string nam,int ag,int pop,int dlv) : Space_object(nam,ag) {
        population=pop;
        development_level=dlv;
    }
};

class Black_hole : public Space_object
{
protected:
    int radius;
public:
    Black_hole() : Space_object() {
        radius=0;
    }
    Black_hole(string nam,int ag,int rad) : Space_object(nam,ag) {
        radius=rad;
    }
};

class Supermassive_black_hole : public Black_hole
{
private:
    int radius_of_danger;
public:
    Supermassive_black_hole() : Black_hole() {
        radius_of_danger=0;
    }
    Supermassive_black_hole(string nam,int ag,int rad,int rd) : Black_hole(nam,ag,rad) {
        radius_of_danger=rd;
    }
    int calculate_coeficient_of_usability() override {
        return radius*radius;
    }
};

class Small_black_hole : public Black_hole
{
private:
    int time_left;
public:
    Small_black_hole() : Black_hole() {
        time_left=0;
    }
    Small_black_hole(string nam,int ag,int rad,int tl) : Black_hole(nam,ag,rad) {
        time_left=tl;
    }
    int calculate_coeficient_of_usability() override {
        return 0;
    }
};

int Doctor::total_surgeries = 0;

int main()
{
    vector<Engineer> Engineers;
    vector<Doctor> Doctors;
    vector<Nurse> Nurses;
    vector<Pilot> Pilots;
    vector<Cabin> Cabin_crew;
    vector<Star> Stars;
    vector<Planet> Planets;
    vector<Supermassive_black_hole> Supermassive_black_holes;
    vector<Small_black_hole> Small_black_holes;
    int op;
    while(true)
    {
        cout<<"Insert action code: ";
        cin>>op;
        if(op==1) ///add doctor
        {
            string nam;
            int ag,hei,pat,sur,suc_sur;
            cout<<"Doctor's name: ";
            cin>>nam;
            cout<<"Doctor's age: ";
            cin>>ag;
            cout<<"Doctor's height: ";
            cin>>hei;
            cout<<"Number of patients treated by doctor: ";
            cin>>pat;
            cout<<"Number of surgeries performed by doctor: ";
            cin>>sur;
            cout<<"Number of succesful surgeries performed by doctor: ";
            cin>>suc_sur;
            Doctor doc(nam,ag,hei,pat,sur,suc_sur);
            Doctors.push_back(doc);
            cout<<"Index of doctor: "<<Doctors.size()<<"\n";
        }
        if(op==2) ///add engineer
        {
            string nam;
            int ag,hei,lvl;
            cout<<"Engineer's name: ";
            cin>>nam;
            cout<<"Engineer's age: ";
            cin>>ag;
            cout<<"Engineer's height: ";
            cin>>hei;
            cout<<"Engineer's level: ";
            cin>>lvl;
            Engineer engi(nam,ag,hei,lvl);
            Engineers.push_back(engi);
            cout<<"Index of engineer: "<<Engineers.size()<<"\n";
        }
        if(op==3) ///add nurse
        {
            string nam;
            int ag,hei,pat;
            double rat;
            cout<<"Nurse's name: ";
            cin>>nam;
            cout<<"Nurse's age: ";
            cin>>ag;
            cout<<"Nurse's height: ";
            cin>>hei;
            cout<<"Number of patients helped by nurse: ";
            cin>>pat;
            cout<<"Nurse's rating: ";
            cin>>rat;
            Nurse nur(nam,ag,hei,pat,rat);
            Nurses.push_back(nur);
            cout<<"Index of nurse: "<<Nurses.size()<<"\n";
        }
        if(op==4) ///add pilot
        {
            string nam;
            int ag,hei,exp,fli,suc_land;
            cout<<"Pilot's name: ";
            cin>>nam;
            cout<<"Pilot's age: ";
            cin>>ag;
            cout<<"Pilot's height: ";
            cin>>hei;
            cout<<"Years of experience of pilot: ";
            cin>>exp;
            cout<<"Number of flights performed by pilot: ";
            cin>>fli;
            cout<<"Number of succesful landings performed by pilot: ";
            cin>>suc_land;
            Pilot pil(nam,ag,hei,exp,fli,suc_land);
            Pilots.push_back(pil);
            cout<<"Index of pilot: "<<Pilots.size()<<"\n";
        }
        if(op==5) ///add flight attendant
        {
            string nam;
            int ag,hei,exp,nr;
            double rat;
            cout<<"Flight attendant's name: ";
            cin>>nam;
            cout<<"Flight attendant's age: ";
            cin>>ag;
            cout<<"Flight attendant's height: ";
            cin>>hei;
            cout<<"Years of experience of Flight attendant: ";
            cin>>exp;
            cout<<"Flight attendant' rating: ";
            cin>>rat;
            cout<<"Number of passengers flown by flight attendant: ";
            cin>>nr;
            Cabin cab(nam,ag,hei,exp,rat,nr);
            Cabin_crew.push_back(cab);
            cout<<"Index of flight attendat: "<<Cabin_crew.size()<<"\n";
        }
        if(op==6) ///add star
        {
            string nam;
            int ag,temp,rad;
            cout<<"Star's name: ";
            cin>>nam;
            cout<<"Star's age: ";
            cin>>ag;
            cout<<"Star's temperature: ";
            cin>>temp;
            cout<<"Star's radius: ";
            cin>>rad;
            Star st(nam,ag,temp,rad);
            Stars.push_back(st);
            cout<<"Index of star: "<<Stars.size()<<"\n";
        }
        if(op==7) ///add planet
        {
            string nam;
            int ag,pop,dlv;
            cout<<"Planet's name: ";
            cin>>nam;
            cout<<"Planet's age: ";
            cin>>ag;
            cout<<"Planet's population: ";
            cin>>pop;
            cout<<"Planet's development level: ";
            cin>>dlv;
            Planet pl(nam,ag,pop,dlv);
            Planets.push_back(pl);
            cout<<"Index of planet: "<<Planets.size()<<"\n";
        }
        if(op==8) ///add supermassive black hole
        {
            string nam;
            int ag,rad,rd;
            cout<<"Black hole's name: ";
            cin>>nam;
            cout<<"Black hole's age: ";
            cin>>ag;
            cout<<"Black hole's radius: ";
            cin>>rad;
            cout<<"Black hole's radius of danger: ";
            cin>>rd;
            Supermassive_black_hole sh(nam,ag,rad,rd);
            Supermassive_black_holes.push_back(sh);
            cout<<"Index of supermassive black hole: "<<Supermassive_black_holes.size()<<"\n";
        }
        if(op==9) ///add small black hole
        {
            string nam;
            int ag,rad,tl;
            cout<<"Black hole's name: ";
            cin>>nam;
            cout<<"Black hole's age: ";
            cin>>ag;
            cout<<"Black hole's radius: ";
            cin>>rad;
            cout<<"Black hole's time until complete evaporation: ";
            cin>>tl;
            Small_black_hole sh(nam,ag,rad,tl);
            Small_black_holes.push_back(sh);
            cout<<"Index of small black hole: "<<Small_black_holes.size()<<"\n";
        }
        if(op==11) ///calculate value of i_th pilot
        {
            int id;
            cout<<"Index of pilot: ";
            cin>>id;
            Crew* ptr;
            ptr=&Pilots[id-1];   ///UPCASTING
            cout<<"Value of pilot: "<<ptr->calculate_value()<<"\n";/// DYNAMIC DISPATCH
        }
        if(op==12) ///calculate value of i_th flight attendant
        {
            int id;
            cout<<"Index of flight attendant: ";
            cin>>id;
            Crew* ptr;
            ptr=&Cabin_crew[id-1];  ///UPCASTING
            cout<<"Value of flight attendant: "<<ptr->calculate_value()<<"\n";  /// DYNAMIC DISPATCH
        }
        if(op==13) ///calculate usability of i_th star
        {
            int id;
            cout<<"Index of star: ";
            cin>>id;
            Space_object* ptr;
            ptr=&Stars[id-1];   ///UPCASTING
            cout<<"Coeficient_of_usability of star: "<<ptr->calculate_coeficient_of_usability()<<"\n";/// DYNAMIC DISPATCH
        }
        if(op==14) ///calculate usability of i_th planet
        {
            int id;
            cout<<"Index of planet: ";
            cin>>id;
            Space_object* ptr;
            ptr=&Planets[id-1];   ///UPCASTING
            cout<<"Coeficient_of_usability of planet: "<<ptr->calculate_coeficient_of_usability()<<"\n";/// DYNAMIC DISPATCH
        }
        if(op==15) ///calculate usability of i_th supermasive black hole
        {
            int id;
            cout<<"Index of supermassive black hole: ";
            cin>>id;
            Space_object* ptr;
            ptr=&Supermassive_black_holes[id-1];   ///UPCASTING
            cout<<"Coeficient_of_usability of supermassive black hole: "<<ptr->calculate_coeficient_of_usability()<<"\n";/// DYNAMIC DISPATCH
        }
        if(op==16) ///calculate usability of i_th small black hole
        {
            int id;
            cout<<"Index of small black hole: ";
            cin>>id;
            Space_object* ptr;
            ptr=&Small_black_holes[id-1];   ///UPCASTING
            cout<<"Coeficient_of_usability of small black hole: "<<ptr->calculate_coeficient_of_usability()<<"\n";/// DYNAMIC DISPATCH
        }
        if(op==17) ///calculate succes rate of i_th doctor
        {
            int id;
            cout<<"Index of doctor: ";
            cin>>id;
            cout<<fixed<<setprecision(10)<<"Succes rate of doctor: "<<Doctors[id-1].calculate_succes_rate()<<"\n";
        }
        if(op==21) ///calculate total number of surgeries
        {
            cout<<"Total number of surgeries: "<<Doctor::get_total_surgeries()<<"\n";
        }
        if(op==22) ///add total surgeries
        {
            int nr;
            cout<<"Number of surgeries performed by unregistered doctors: ";
            cin>>nr;
            Doctor::add_total_surgeries(nr);
        }
        if(op==31) ///print name of i_th supermassive black hole
        {
            int id;
            cout<<"Index of supermassive black hole: ";
            cin>>id;
            cout<<Supermassive_black_holes[id-1].get_name()<<"\n";
        }
        if(op==32) ///print name of i_th small black hole
        {
            int id;
            cout<<"Index of small black hole: ";
            cin>>id;
            cout<<Small_black_holes[id-1].get_name()<<"\n";
        }
    }
}



