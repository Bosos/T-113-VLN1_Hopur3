#include "SortBy.h"

ScientistSortOrder::ScientistSortOrder(){}
ScientistSortOrder::ScientistSortOrder(ScientistSortBy sortBy)
{
    this->sortBy = sortBy;
}

ComputerSortOrder::ComputerSortOrder(){}
ComputerSortOrder::ComputerSortOrder(ComputerSortBy sortBy)
{
    this->sortBy = sortBy;
}

string ScientistSortOrder::getSortByString()
{
    switch (sortBy)
    {
    case SNAME: return "name";
    case BIRTH: return "birth";
    case DEATH: return "death";
    case SEX: return "sex";
    case SID:
    default: return "id";
    }
}

string ComputerSortOrder::getSortByString()
{
    switch (sortBy)
    {
    case CNAME: return "name";
    case BUILT: return "buildyear";
    case TYPE: return "type";
    case WASBUILT: return "wasbuild";
    case CID:
    default: return "id";
    }
}

string ScientistSortOrder::getDirectionString()
{
    switch (direction)
    {
    case DESCENDING: return "DESC";
    case ASCENDING:
    default: return "ASC";
    }
}

string ComputerSortOrder::getDirectionString()
{
    switch (direction)
    {
    case DESCENDING: return "DESC";
    case ASCENDING:
    default: return "ASC";
    }
}
