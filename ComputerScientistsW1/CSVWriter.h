#ifndef CSVWRITER_H
#define CSVWRITER_H

#include<string>
#include<vector>

using namespace std;

class CSVWriter
{
public:
    CSVWriter(string fileName);
    ~CSVWriter();
    void clear();
    void add(vector<string> scientist);
    void close();
};

#endif // CSVWRITER_H
