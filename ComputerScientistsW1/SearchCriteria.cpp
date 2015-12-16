#include "SearchCriteria.h"

// Scientist Search
void ScientistSearch::setSex(QString sex)
{
    if (sex == "Male") { this->sex = "M"; }
    else if (sex == "Female") { this->sex = "F"; }
    else { this->sex = ""; }
}

QString ScientistSearch::getSex()
{
    return this->sex;
}

int ScientistSearch::getAge()
{
    if(death.toInt() != 0)
    {
        return death.toInt() - birth.toInt();
    }
    else
    {
        return 2015 - birth.toInt();
    }
}

// Computer Search
void ComputerSearch::setType(int type)
{
    if(!type) { this->type = ""; }
    else { this->type = QString::number(type); }
}

void ComputerSearch::setWasItBuilt(int wasBuilt)
{
    if(wasBuilt == 1) {this->wasItBuilt = "1"; }
    else if(wasBuilt == 2) {this->wasItBuilt = "0"; }
    else {this->wasItBuilt = ""; }
}

QString ComputerSearch::getType()
{
    return this->type;
}

QString ComputerSearch::getWasItBuilt()
{
    return this->wasItBuilt;
}
