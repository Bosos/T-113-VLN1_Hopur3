#ifndef COMPUTER
#define COMPUTER

#include <string>
#include <vector>
#include "ConnectedTo.h"

using namespace std;

class Computer
{
public:
    Computer(string newName, int newBuildYear, string newType, bool NewWasItBuilt, string newAbout, int newID);
    Computer();
    ~Computer();
    string getName();
    int getBuildYear();
    string getType();
    bool getWasItBuilt();
    string getAbout();
    int getID();
    void setName(string newName);
    void setBuildYear(int newBuildYear);
    void setType(string newType);
    void setWasItBuilt(bool newWasItBuilt);
    void setAbout(string newAbout);
private:
    string name;
    int buildYear;
    string type;
    bool wasItBuilt;
    string about;
    int ID;
};

#endif // COMPUTER

