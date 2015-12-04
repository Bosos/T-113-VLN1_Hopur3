#ifndef scientist
#define scientist

#include "stdlib.h"
#include <string>
#include <vector>
#include "ConnectedTo.h"

using namespace std;

class Scientist
{
public:
    Scientist(string newName, char newSex, int newBirthYear, int newDeathYear, string newAbout, int ID);
    Scientist();
    ~Scientist();
    string getName();
    char getSex();
    int getBirthYear();
    int getDeathYear();
    string getAbout();
    int getID();
    int getAge();
    void setName(string newName);
    void setSex(char newSex);
    void setBirthYear(int newBirthYear);
    void setDeathYear(int newDeathYear);
    void setAbout(string newAbout);
private:
    string name;
    char sex;
    int birthYear;
    int deathYear;
    string about;
    int ID;
};

#endif // scientist

