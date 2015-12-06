#include "SortBy.h"

string ScientistSortOrder::getSortByString()
{
    switch (sortBy)
    {
    case SID: return "id";
    case SNAME: return "name";
    case BIRTH: return "birth";
    case DEATH: return "death";
    case SEX: return "sex";
    default: return "id";
    }
}

string ComputerSortOrder::getSortByString()
{
    switch (sortBy)
    {
    case CID: return "id";
    case CNAME: return "name";
    case BUILT: return "buildyear";
    case TYPE: return "type";
    case WASBUILT: return "wasbuild";
    default: return "id";
    }
}

string ScientistSortOrder::getDirectionString()
{
    switch (direction)
    {
    case ASCENDING: return "ASC";
    case DESCENDING: return "DESC";
    default: return "ASC";
    }
}

string ComputerSortOrder::getDirectionString()
{
    switch (direction)
    {
    case ASCENDING: return "ASC";
    case DESCENDING: return "DESC";
    default: return "ASC";
    }
}

