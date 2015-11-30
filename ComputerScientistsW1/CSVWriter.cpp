#include "CSVWriter.h"

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
    // TODO clears the file, good for edits
}

void CSVWriter::add(vector<string> scientist)
{
    std::ofstream newEntry(fileName, std::ios_base::app);//appending a new entry to the document
    for(unsigned i = 0; i < scientist.size(); i++)
    {
        newEntry << scientist[i];
        if(i < scientist.size()-1)
        {
            newEntry << ",";
        }
    }
    newEntry << endl;
    //add a new line to the end of the doc
}

void CSVWriter::close()
{
    //TODO closes the string
}
