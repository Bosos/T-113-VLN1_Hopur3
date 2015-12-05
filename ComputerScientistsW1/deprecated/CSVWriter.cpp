#include "CSVWriter.h"
#include <iostream>
#include <string>

CSVWriter::CSVWriter(string newfileName)
{
    fileName = newfileName;
}

CSVWriter::~CSVWriter()
{

}

void CSVWriter::clear()
{
    std::ofstream clearing;
    clearing.open(fileName, std::ofstream::out | std::ofstream::trunc);
    //clears the file, good for edits
}

void CSVWriter::add(vector<string> scientist)
{
    std::ofstream newEntry(fileName, std::ios_base::app);//appending a new entry to the document
    for(unsigned i = 0; i < scientist.size(); i++)//go over all the strings in the scientist vector
    {
        if(i == 1)//if "i = 1" then it is the sex and we make sure the new entry has the right output
        {
            if(scientist[i] == "70")//then the output is 70 is female or F
            {
                newEntry << "F";
            }
            else
            {
                newEntry << "M";//and as we stand we havn't gotten to more of the sexes, so only other choise is male or M
            }
            newEntry << ",";
        }
        else
        {
            newEntry << scientist[i];//input the entry into the file at the end
            if(i < scientist.size()-1)//this is to make sure we don't put a comma at the end of the line
            {
                newEntry << ",";
            }
        }
    }
    newEntry << endl;
    //add a new line to the end of the doc
}

void CSVWriter::close()
{
    //TODO closes the string
}
