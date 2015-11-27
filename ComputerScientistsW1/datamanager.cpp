#include "datamanager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

vector<Scientist> DataManager::getScientists(string fileName)
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

