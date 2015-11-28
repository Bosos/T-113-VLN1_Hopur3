#include "Scientist.h"


Scientist::Scientist(string newName, char newSex, int newBirthYear, int newDeathYear)
{
    name = newName;
    sex = newSex;
    birthYear = newBirthYear;
    deathYear = newDeathYear;
}
Scientist::Scientist(){}
Scientist::~Scientist(){}

int Scientist::getSex()
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
