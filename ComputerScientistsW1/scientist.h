#ifndef scientist
#define scientist

#include "stdlib.h"
#include <string>

using namespace std;

class Scientist
{
public:
    Scientist(string newName, char newSex, int newBirthYear, int newDeathYear);
    Scientist();
    ~Scientist();
    int getSex();
    void setSex(char sex);
    string getName();
    void setName(string name);
    int getBirthYear();
    void setBirthYear(int birthYear);
    int getDeathYear();
    void setDeathYear(int deathYear);
private:
    char sex;
    string name;
    int birthYear;
    int deathYear;
};

#endif // scientist

