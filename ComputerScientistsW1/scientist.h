#ifndef scientistr
#define scientistr
#include "stdlib.h"
#include <string>
#include <qstring.h>
#include <vector>
#include "ConnectedTo.h"

using namespace std;

class Scientist
{
public:
    Scientist(QString newName, char newSex, int newBirthYear, int newDeathYear, QString newAbout, int ID);
    Scientist(QString newName, QString newSex, int newBirthYear, int newDeathYear, QString newAbout, int newID);
    QString getName() const;
    char getSex() const;
    int getBirthYear() const;
    int getDeathYear() const;
    QString getAbout();
    int getID();
    int getAge();
    void setName(QString newName);
    void setSex(char newSex);
    void setBirthYear(int newBirthYear);
    void setDeathYear(int newDeathYear);
    void setAbout(QString newAbout);
private:
    QString name;
    char sex;
    int birthYear;
    int deathYear;
    QString about;
    int ID;
};

#endif // scientistr

