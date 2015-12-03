#include "DataManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <CSVWriter.h>
#include <CSVReader.h>
#include <algorithm>
#include <cstring>

DataManager::DataManager(string fileLocation)
{
    this->fileName = fileLocation;
}
DataManager::~DataManager(){}

/*!
 * \brief DataManager::parseInput takes a vector of strings from the input and parses it into the correct format
 * \param csvLine
 * \returns a Scientist
 */
Scientist DataManager::parseInput(vector<string> csvLine, int ID)
{
    return Scientist(csvLine[0], csvLine[1].c_str()[0], stoi(csvLine[2]), stoi(csvLine[3]), csvLine[4], ID);
}

/*!
 * \brief DataManager::addScientist Adds a scientist to the cvs file
 * \param Scientist
 */
void DataManager::addScientist(Scientist scientis)
{
    CSVWriter csvw (fileName);
    csvw.add(scientistToVector(scientis));
    //Changes the scientist class to a vector before adding it to the doc.
}

/*!
 * \brief DataManager::scientistToVector
 * \param Scientist
 * \returns a vector of strings
 */
vector<string> DataManager::scientistToVector(Scientist scientis)
{
    //Changes the scientist class to a vector
    return vector<string> {
        scientis.getName(),
        to_string(scientis.getSex()),
        to_string(scientis.getBirthYear()),
        to_string(scientis.getDeathYear()),
        scientis.getAbout()};
}


vector<Scientist> DataManager::getAllScientists(SortOrder sort)
{
    vector<Scientist> allScientists;
    vector<vector<string>> newScientists;
    CSVReader docReader(fileName);//initialize the CSVReader class
    newScientists = docReader.readAll();//gets vectors of vectors of strings which are essentially vectors of scientist in strings
    for(unsigned i = 0; i < newScientists.size(); i++)//goes through all of the scientists
    {
        allScientists.push_back(parseInput(newScientists[i], i));//changes vectors of strings into scientist classes
    }
    return sortBy(allScientists, sort);//return the scientist in the sort chosen
}

vector<Scientist> DataManager::findByName(string subString, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's name matches name parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(strstr(allScientists[i].getName().c_str(),subString.c_str()))
        {
             matchingScientists.push_back(allScientists[i]);
        }
    }

    return matchingScientists;
}

vector<Scientist> DataManager::findByBirthYear(int yearFrom, int yearTo, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's birth year matches year parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(allScientists[i].getBirthYear() > yearFrom && allScientists[i].getBirthYear() < yearTo)
        {
            matchingScientists.push_back(allScientists[i]);
        }
    }

    return matchingScientists;
}

vector<Scientist> DataManager::findByDeathYear(int yearFrom, int yearTo, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's death year matches year parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(allScientists[i].getDeathYear() > yearFrom && allScientists[i].getDeathYear() < yearTo)
        {
            matchingScientists.push_back(allScientists[i]);
        }
    }

    return matchingScientists;
}

vector<Scientist> DataManager::findBySex(string sex, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's sex matches sex parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(allScientists[i].getSex() == sex[0])
        {
            matchingScientists.push_back(allScientists[i]);
        }
    }
    return matchingScientists;
}

/*!
 * \brief DataManager::getage Calculates age of scientist.
 * \param oneScientist
 * \returns the age of the given scientist
 */
int DataManager::getage(Scientist oneScientist){

    if(oneScientist.getDeathYear() == 0){
        return 2015 - oneScientist.getBirthYear();
    }

   return oneScientist.getDeathYear() - oneScientist.getBirthYear();
}



struct sortByName
{
    inline bool operator() (Scientist& name1, Scientist& name2)
    {
        return (name1.getName() < name2.getName());
    }
};


struct sortByBirth
{
    inline bool operator() (Scientist& birth1, Scientist& birth2)
    {
        return (birth1.getBirthYear() < birth2.getBirthYear());
    }
};


struct sortByDeath
{
    inline bool operator() (Scientist& death1, Scientist& death2)
    {
        return (death1.getDeathYear() < death2.getDeathYear());
    }
};


struct sortBySex
{
    inline bool operator() (Scientist& sex1, Scientist& sex2)
    {
        return (sex1.getSex() < sex2.getSex());
    }
};


// This function gets an input from the user and sorts it.
vector<Scientist> DataManager::sortBy(vector<Scientist> scientists, SortOrder sortOrder )
{
    switch(sortOrder.sortBy)
    {
        case NONE:
            return scientists;

        // Sorts names in alphabetical order.
        case NAME:
            sort(scientists.begin(), scientists.end(), sortByName());
            break;

        // Sorts birthyear "lowest to highest".
        case BIRTH:
            sort(scientists.begin(), scientists.end(), sortByBirth());
            break;

        // Sorts deathyear "lowest to highest".
        case DEATH:
            sort(scientists.begin(), scientists.end(), sortByDeath());
            break;

        // Sorts gender.
        case SEX:
            sort(scientists.begin(), scientists.end(), sortBySex());
            break;

        default:
            return scientists;

    }
    // Reverses the elements in the Scientists vector.
    if(sortOrder.direction == DESCENDING){
        reverse (scientists.begin(), scientists.end());
    }
    return scientists;
}

void DataManager::writeNewScientistVectorToFile(vector<Scientist> scientists)
{
    CSVWriter csvW(fileName);
    csvW.clear();
    for (size_t i = 0; i < scientists.size(); i++)
    {
        csvW.add(scientistToVector(scientists[i]));
    }
}
