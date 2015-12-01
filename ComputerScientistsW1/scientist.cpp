#include "Scientist.h"
#include <stdexcept>

Scientist::Scientist(string newName, char newSex, int newBirthYear, int newDeathYear)
{
    name = newName;
    sex = newSex;
    birthYear = newBirthYear;
    deathYear = newDeathYear;

    if(name.length() < 1 || (sex != 'M' && sex != 'F') || birthYear < 1600)
    {
        throw invalid_argument("Some entry into Scientist was wrong");
    }
}
Scientist::Scientist(){}
Scientist::~Scientist(){}

char Scientist::getSex()
{
    return sex;
}

void Scientist::setSex(char newSex)
{
    sex = newSex;
}

string Scientist::getName()
{
    return name;
}

void Scientist::setName(string newName)
{
    name = newName;
}

int Scientist::getBirthYear()
{
    return birthYear;
}

void Scientist::setBirthYear(int newBirthYear)
{
    birthYear = newBirthYear;
}

int Scientist::getDeathYear()
{
    return deathYear;
}

void Scientist::setDeathYear(int newDeathYear)
{
    deathYear = newDeathYear;
}
int Scientist::GetAge()//Calculates the age of the scientist
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
