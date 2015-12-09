#ifndef TYPEOFCOMPUTER_H
#define TYPEOFCOMPUTER_H
#include <string>

using namespace std;

class TypeOfComputer
{
public:
    TypeOfComputer(int id, string type);
    int getId();
    string getType();
private:
    int id;
    string type;
};

#endif // TYPEOFCOMPUTER_H
