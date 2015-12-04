#include "TypeOfComputer.h"

TypeOfComputer::TypeOfComputer(int id, string type)
{
    this->id = id;
    this->type = type;
}

int TypeOfComputer::getId()
{
    return id;
}

string TypeOfComputer::getType()
{
    return type;
}
