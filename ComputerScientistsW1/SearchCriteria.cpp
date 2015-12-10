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

