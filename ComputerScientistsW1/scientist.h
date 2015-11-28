#ifndef scientist
#define scientist

#include "stdlib.h"
#include <string>

using namespace std;

class Scientist
{
public:
    Scientist(string newName, int newAge, int newBirthYear, int newDeathYear);
    Scientist();
    ~Scientist();
    int getAge();
    void setAge(int age);
    string getName();
    void setName(string name);
    int getBirthYear();
    void setBirthYear(int birthYear);
    int getDeathYear();
    void setDeathYear(int deathYear);
private:
    int age;
    string name;
    int birthYear;
    int deathYear;
};

#endif // scientist

