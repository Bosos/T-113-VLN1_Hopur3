#include "computer.h"

Computer::Computer(string newName, int newBuildYear, int newType, bool NewWasItBuilt, string newAbout, int newID)
{
    name = newName;
    buildYear = newBuildYear;
    type = newType;
    wasItBuilt = NewWasItBuilt;
    about = newAbout;
    ID = newID;
}

string Computer::getName()
{
    return name;
}

int Computer::getBuildYear()
{
    return buildYear;
}

int Computer::getType()
{
    return type;
}

bool Computer::getWasItBuilt()
{
    return wasItBuilt;
}

string Computer::getWasItBuiltString()
{
    if (wasItBuilt){ return "Yes"; }
    return "No";
}

string Computer::getAbout()
{
    return about;
}

int Computer::getID()
{
    return ID;
}

void Computer::setName(string newName)
{
    name = newName;
}

void Computer::setBuildYear(int newBuildYear)
{
    buildYear = newBuildYear;
}

void Computer::setType(int newType)
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
