#ifndef scientist
#define scientist

#include "stdlib.h"
#include <string>

using namespace std;

class Scientist
{
public:
    Scientist(string newName, char newSex, int newBirthYear, int newDeathYear, string newAbout);
    Scientist();
    ~Scientist();
    char getSex();
    void setSex(char newSex);
    string getName();
    void setName(string newName);
    int getBirthYear();
    void setBirthYear(int newBirthYear);
    int getDeathYear();
    void setDeathYear(int newDeathYear);
    string getAbout();
    void setAbout(string newAbout);
    int GetAge();
private:
    char sex;
    string name;
    int birthYear;
    int deathYear;
    string about;
};

#endif // scientist

