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
    newInput.open(fileName.c_str());//opens up the file where we store info about the scientists
    while(getline(newInput, newLine))//get each line by it self
    {
        vector<string> selectedScientist;//makes a vector of strings for each scientist
        stringstream ss;
        ss << newLine;

        while(getline(ss, newWord, ','))//seperates the words in that line
        {
            selectedScientist.push_back(newWord);//take each word in that line and put it in a vector
        }
        allScientists.push_back(selectedScientist);//take each vector of strings and put it in a vector
    }

    return allScientists;//return the vector of vectors of strings
}

bool CSVReader::hasNext()
{
    //TODO
    return true;
}
