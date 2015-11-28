#ifndef CSVREADER_H
#define CSVREADER_H

#include<string>
#include<vector>

using namespace std;

class CSVReader
{
public:
    CSVReader(string fileName);
    ~CSVReader();
    vector<string> next();
    bool hasNext();
};

#endif // CSVREADER_H
