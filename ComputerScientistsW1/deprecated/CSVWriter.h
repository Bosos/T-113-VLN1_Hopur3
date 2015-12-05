#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CSVWriter
{
private:
    string fileName;
public:
    CSVWriter(string newfileName);
    ~CSVWriter();
    void clear();
    void add(vector<string> scientist);
    void close();
};

#endif // CSVWRITER_H
