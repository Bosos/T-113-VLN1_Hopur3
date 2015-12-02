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

    //ADD / SAVE scientist
    void addScientist(Scientist scientist);

    //LOAD file
    Scientist parseInput(vector<string> csvLine, int ID);
    vector<Scientist> getAllScientists (SortOrder sort);
    vector<Scientist> findByName (string name, SortOrder sort);
    vector<Scientist> findByBirthYear (int yearFrom, int yearTo, SortOrder sort);
    vector<Scientist> findByDeathYear (int yearFrom, int yearTo, SortOrder sort);
    vector<Scientist> findBySex(string sex, SortOrder sort);
    vector<Scientist> sortBy(vector<Scientist> scientists, SortOrder sort );
    vector<string> scientistToVector(Scientist scientis);
    void writeNewScientistVectorToFile(vector<Scientist> scientists);
    int getage(Scientist oneScientist);

    //EDIT scientist
    //DELETE scientist


private:
    string fileName;

};

#endif // dataManager



