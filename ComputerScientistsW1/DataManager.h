#ifndef dataManager
#define dataManager

#include "stdlib.h"
#include <vector>
#include "Scientist.h"
#include <SortBy.h>


using namespace std;

class DataManager
{
public:
    DataManager(string fileName);
    ~DataManager();
    vector<Scientist> getAllScientists(SortBy sort, Direction direction);
    vector<Scientist> findByName(string name, SortBy sort, Direction direction);
    vector<Scientist> findByBirthYear(string year,SortBy sort, Direction direction);

private:
    string fileName;

};

#endif // dataManager



