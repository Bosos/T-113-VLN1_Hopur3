#include "scientist.h"


Scientist::Scientist(string newName, int newAge, int newBirthYear, int newDeathYear)
{
    name = newName;
    age = newAge;
    birthYear = newBirthYear;
    deathYear = newDeathYear;
}
Scientist::Scientist(){}
Scientist::~Scientist(){}
int Scientist::getAge()
{
    return age;
}
void Scientist::setAge(int newAge)
{
    age = newAge;
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
