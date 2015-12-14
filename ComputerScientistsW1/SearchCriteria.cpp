#include "SearchCriteria.h"

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

SearchCriteria::SearchCriteria()
{

}

void ComputerSearch::setType(QString type)
{
    if(type == "Electronic") {this->type = "1"; }
    else if(type == "Mecanic") {this->type = "2"; }
    else if(type == "Transistor") {this->type = "3"; }
    else if(type == "Electromechanic") {this->type = "4"; }
    else {this->type = ""; }
}

void ComputerSearch::setWasItBuilt(QString wasBuilt)
{
    if(wasBuilt == "Yes") {this->wasItBuilt = "1"; }
    else if(wasBuilt == "No") {this->wasItBuilt = "0"; }
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
