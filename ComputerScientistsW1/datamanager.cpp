#include "DataManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

DataManager::DataManager(string fileName)
{
    this->fileName = fileName;
}

DataManager::~DataManager()
{

}

vector<Scientist> DataManager::getAllScientists(SortBy sort, Direction direction)
{
    vector<Scientist> allScientists;
    ifstream newInput;

    newInput.open(fileName.c_str());

    for (string newLine; getline(newInput, newLine);)
    {
        stringstream ss(newLine);
        string sName;
        string addedPartofName;
            while (ss >> addedPartofName)
            {
                sName += addedPartofName + " ";
            }
        int age, birthYear, deathYear;
        ss >> age >> birthYear >> deathYear;
        Scientist newScientist(sName.c_str(), age, birthYear, deathYear);
        allScientists.push_back(newScientist);
    }

    return allScientists;
}

vector<Scientist> DataManager::findByName(string name, SortBy sort, Direction direction)
{
    // TODO

    vector<Scientist> allScientists = getAllScientists(NONE, ASCENDING);
    return allScientists;
}

vector<Scientist> DataManager::findByBirthYear(string year,SortBy sort, Direction direction)
{
    // TODO

    vector<Scientist> allScientists = getAllScientists(NONE, ASCENDING);
    return allScientists;
}
