#ifndef dataManager
#define dataManager

#include "stdlib.h"
#include <vector>
#include "scientist.h"

using namespace std;

class DataManager
{
public:
    DataManager();
    ~DataManager();
    vector<Scientist> getScientists(string fileName);
};

#endif // dataManager



