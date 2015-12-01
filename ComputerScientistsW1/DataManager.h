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
    //TODO
    //ADD / SAVE scientist
    void addScientist(Scientist scientist);

    //LOAD file
    //EDIT scientist
    //DELETE scientist
    Scientist parseInput(vector<string> csvLine);
    vector<Scientist> getAllScientists (SortOrder sort);
    vector<Scientist> findByName (string name, SortOrder sort);
    vector<Scientist> findByBirthYear (int year, SortOrder sort);
    vector<Scientist> findByDeathYear (int year, SortOrder sort);
    vector<Scientist> findBySex(string sex, SortOrder sort);
    int getage(Scientist oneScientist);
    vector<Scientist> sortBy(vector<Scientist> scientists, SortOrder sort );

    //void sort (vector<Scientist>& scientists, SortOrder sort);
    vector<string> scientistToVector(Scientist scientis);

private:
    string fileName;

};

#endif // dataManager



