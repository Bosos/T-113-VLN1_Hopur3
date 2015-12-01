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

vector<vector<string>> CSVReader::next()
{
    ifstream newInput;
    vector<vector<string>> allScientists;
    vector<string> selectedScientist;
    string newLine;
    string newWord;
    newInput.open(fileName.c_str());
    while(getline(newInput, newLine))
    {
        stringstream ss;
        while(getline(ss, newWord, ','))
        {
            selectedScientist.push_back(newWord);
        }
        allScientists.push_back(selectedScientist);
        selectedScientist.clear();
    }
    cout << endl << "bla " << selectedScientist.size() << " bla" << endl;
    return allScientists;
}

bool CSVReader::hasNext()
{
    //TODO
    return true;
}
