#include "computer.h"

Computer::Computer(string newName, int newBuildYear, string newType, bool NewWasItBuilt, string newAbout, int newID)
{
    name = newName;
    buildYear = newBuildYear;
    type = newType;
    wasItBuilt = NewWasItBuilt;
    about = newAbout;
    ID = newID;
}

Computer::Computer(){}
Computer::~Computer(){}
string Computer::getName()
{
    return name;
}

int Computer::getBuildYear()
{
    return buildYear;
}

string Computer::getType()
{
    return type;
}

bool Computer::getWasItBuilt()
{
    return wasItBuilt;
}

string Computer::getAbout()
{
    return about;
}

int Computer::getID()
{
    return ID;
}

vector<connectedTo> Computer::getScientists()
{
    return sciList;
}

void Computer::setScientist(string sciName, int sciBirthYear)
{
    connectedTo newScientist;
    newScientist.name = sciName;
    newScientist.bYear = sciBirthYear;
    sciList.push_back(newScientist);
}

void Computer::setName(string newName)
{
    name = newName;
}

void Computer::setBuildYear(int newBuildYear)
{
    buildYear = newBuildYear;
}

void Computer::setType(string newType)
{
    type = newType;
}

void Computer::setWasItBuilt(bool newWasItBuilt)
{
    wasItBuilt = newWasItBuilt;
}

void Computer::setAbout(string newAbout)
{
    about = newAbout;
}
