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
    CSVWriter(string fileName);
    ~CSVWriter();
    void clear();
    void add(vector<string> scientist);
    void close();
};

#endif // CSVWRITER_H
