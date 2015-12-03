#include "Scientist.h"
#include <stdexcept>

Scientist::Scientist(string newName, char newSex, int newBirthYear, int newDeathYear, string newAbout, int newID)
{
    name = newName;
    sex = newSex;
    birthYear = newBirthYear;
    deathYear = newDeathYear;
    about = newAbout;
    ID = newID;

    if(name.length() < 1 || (sex != 'M' && sex != 'F') || birthYear < 1200)
    {
        throw invalid_argument("Some entry into Scientist was wrong");
    }
}

Scientist::Scientist(){}
Scientist::~Scientist(){}

string Scientist::getName()
{
    return name;
}

char Scientist::getSex()
{
    return sex;
}

int Scientist::getBirthYear()
{
    return birthYear;
}

int Scientist::getDeathYear()
{
    return deathYear;
}

string Scientist::getAbout()
{
    return about;
}

int Scientist::getID()
{
    return ID;
}

int Scientist::getAge()//Calculates the age of the scientist
{
    if(deathYear != 0)
    {
        return deathYear - birthYear;
    }
    else
    {
        return 2015 - birthYear;
    }
}

vector<connectedTo> Scientist::getComputers()
{
    return compList;
}

void Scientist::setComputer(string compName, int compBuiltYear)
{
    connectedTo newComputer;
    newComputer.name = compName;
    newComputer.bYear = compBuiltYear;
    compList.push_back(newComputer);
}

void Scientist::setName(string newName)
{
    name = newName;
}

void Scientist::setSex(char newSex)
{
    sex = newSex;
}

void Scientist::setBirthYear(int newBirthYear)
{
    birthYear = newBirthYear;
}


void Scientist::setDeathYear(int newDeathYear)
{
    deathYear = newDeathYear;
}

void Scientist::setAbout(string newAbout)
{
    about = newAbout;
}
