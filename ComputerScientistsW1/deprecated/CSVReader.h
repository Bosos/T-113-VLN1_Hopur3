#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CSVReader
{
private:
    string fileName;
public:
    CSVReader(string newfileName);
    ~CSVReader();
    vector<vector<string>> readAll();
    bool hasNext();
};

#endif // CSVREADER_H
