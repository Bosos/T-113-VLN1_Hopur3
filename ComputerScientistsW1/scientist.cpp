#include "Scientist.h"
#include <stdexcept>
#include <iostream>

Scientist::Scientist(QString newName, char newSex, int newBirthYear, int newDeathYear, QString newAbout, int newID)
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

QString Scientist::getName() const
{
    return name;
}

char Scientist::getSex() const
{
    return sex;
}

int Scientist::getBirthYear() const
{
    return birthYear;
}

int Scientist::getDeathYear() const
{
    return deathYear;
}

QString Scientist::getAbout()
{
    return about;
}

int Scientist::getID()
{
    return ID;
}

int Scientist::getAge()
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

void Scientist::setName(QString newName)
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

void Scientist::setAbout(QString newAbout)
{
    about = newAbout;
}
