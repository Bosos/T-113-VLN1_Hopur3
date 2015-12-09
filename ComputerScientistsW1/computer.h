#ifndef COMPUTER
#define COMPUTER
#include <string>
#include <vector>
#include "ConnectedTo.h"

using namespace std;

class Computer
{
public:
    Computer(string newName, int newBuildYear, int newType, bool NewWasItBuilt, string newAbout, int newID);
    string getName();
    int getBuildYear();
    int getType();
    bool getWasItBuilt();
    string getWasItBuiltString();
    string getAbout();
    int getID();
    void setName(string newName);
    void setBuildYear(int newBuildYear);
    void setType(int newType);
    void setWasItBuilt(bool newWasItBuilt);
    void setAbout(string newAbout);
private:
    string name;
    int buildYear;
    int type;
    bool wasItBuilt;
    string about;
    int ID;
};

#endif // COMPUTER

