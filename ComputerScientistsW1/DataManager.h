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
    vector<Scientist> getAllScientists (SortBy sort, Direction direction);
    vector<Scientist> findByName (string name, SortBy sort, Direction direction);
    vector<Scientist> findByBirthYear (string year,SortBy sort, Direction direction);
    vector<Scientist> findByDeathYear (string year,SortBy sort, Direction direction);

    //void sort (vector<Scientist>& scientists, SortBy sort, Direction direction);


private:
    string fileName;

};

#endif // dataManager



