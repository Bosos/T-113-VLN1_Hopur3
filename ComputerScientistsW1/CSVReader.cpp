#include "CSVReader.h"
#include <string>

CSVReader::CSVReader(string newfileName)
{
    fileName = newfileName;
}
CSVReader::~CSVReader()
{

}

vector<string> CSVReader::next(int scientistNr)
{
    ifstream newInput;
    vector<string> selectedScientist;
    string newLine;
    newInput.open(fileName.c_str());
    for(int i = 0; i < scientistNr; i++)
    {
        getline(newInput, newLine);
        if(i == scientistNr-1)
        {
            while(getline(newInput, newLine, ','))
            {
                selectedScientist.push_back(newLine);
            }
        }
    }
    //cout
    return selectedScientist;
}

bool CSVReader::hasNext()
{
    //TODO
    return true;
}
