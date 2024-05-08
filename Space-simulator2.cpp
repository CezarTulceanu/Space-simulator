#include<iostream>
#include<fstream>
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
};

class Doctor : public Medical
{
private:
    int surgeries;
public:
    int get_surgeries()
    {
        return surgeries;
    }
    void set_surgeries(int s)
    {
        surgeries=s;
    }
};

class Nurse : public Medical
{
private:
    int rating;
public:
    int get_rating()
    {
        return rating;
    }
    void set_rating(int ra)
    {
        rating=ra;
    }
};

class Crew : public Human
{
private:
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
};

class Pilot : public Crew
{
private:
    int flights;
public:
    int get_flights()
    {
        return flights;
    }
    void set_flights(int fl)
    {
        flights=fl;
    }
};

class Cabin : public Crew
{
private:
    int rating;
public:
    int get_rating()
    {
        return rating;
    }
    void set_rating(int ra)
    {
        rating=ra;
    }
};

class Space_object
{
private:
    int age;
public:
    int get_age()
    {
        return age;
    }
    void set_age(int ag)
    {
        age=ag;
    }
    virtual int calculate_coeficent_of_usability()=0;
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
        radius=ra;
    }
    int calculate_coeficient_of_usability() override {
        return ra*ra*temperature;
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
};



