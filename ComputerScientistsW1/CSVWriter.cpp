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
    // TODO clears the file, good for edits,
}

void CSVWriter::add(vector<string> scientist)
{
    std::ofstream newEntry(fileName, std::ios_base::app);
    for(unsigned i = 0; i < scientist.size(); i++)
    {
        newEntry << scientist[i];
        if(i < scientist.size()-1)
        {
            newEntry << ",";
        }
    }
    newEntry << endl;
    //TODO add a new line to the end of the doc
}

void CSVWriter::close()
{
    //TODO closes the string
}
