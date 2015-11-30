#include "DataManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <CSVWriter.h>

DataManager::DataManager(string fileLocation)
{
    this->fileName = fileLocation;
}

DataManager::~DataManager()
{

}
Scientist DataManager::parseInput(vector<string> csvLine)
{//     Scientist(string name, int age, int birthYear, int deathYear);
    return Scientist(csvLine[0], stoi(csvLine[1]), stoi(csvLine[2]), stoi(csvLine[3]));
}

void DataManager::addScientist(Scientist scientis){
    CSVWriter csvw (fileName);
    csvw.add(scientistToVector(scientis));
    //Changes the scientist class to a vector before adding it to the doc.
}

vector<string> DataManager::scientistToVector(Scientist scientis)
{
    //Changes the scientist class to a vector
    return vector<string> { scientis.getName(),
                 to_string( scientis.getSex()),
                 to_string( scientis.getBirthYear()),
                 to_string( scientis.getDeathYear()) };
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
        char sex;
        int birthYear, deathYear;
        ss >> sex >> birthYear >> deathYear;
        Scientist newScientist(sName.c_str(), sex, birthYear, deathYear);
        allScientists.push_back(newScientist);
    }

    return allScientists;
}

vector<Scientist> DataManager::findByName(string name, SortBy sort, Direction direction)
{
    // TODO

    return vector<Scientist>();
}

vector<Scientist> DataManager::findByBirthYear(string year,SortBy sort, Direction direction)
{
    // TODO

    return vector<Scientist>();
}

vector<Scientist> DataManager::findByDeathYear(string year,SortBy sort, Direction direction)
{
    // TODO

    return vector<Scientist>();
}
