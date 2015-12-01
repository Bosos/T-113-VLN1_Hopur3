#include "CSVReader.h"
#include <string>
#include <iostream>
#include <sstream>

CSVReader::CSVReader(string newfileName)
{
    fileName = newfileName;
}
CSVReader::~CSVReader()
{

}

vector<vector<string>> CSVReader::readAll()
{
    ifstream newInput;
    vector<vector<string>> allScientists;
    string newLine = "";
    string newWord = "";
    newInput.open(fileName.c_str());
    while(getline(newInput, newLine))
    {
        vector<string> selectedScientist;
        stringstream ss;
        ss << newLine;

        // cout << endl << "bla 1 " << selectedScientist.size() << " bla" << endl;
        while(getline(ss, newWord, ','))
        {
            selectedScientist.push_back(newWord);
           // cout << endl << "bla 2 " << selectedScientist.size() << " bla" << endl;
        }
        allScientists.push_back(selectedScientist);
    }

    return allScientists;
}

bool CSVReader::hasNext()
{
    //TODO
    return true;
}
