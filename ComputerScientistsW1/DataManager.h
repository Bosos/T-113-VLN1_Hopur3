#ifndef dataManager
#define dataManager

#include "stdlib.h"
#include <vector>
#include "Scientist.h"
#include "Computer.h"
#include <SortBy.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <TypeOfComputer.h>

using namespace std;

class DataManager
{
public:
    DataManager(string fileName);
    ~DataManager();

    //ADD / SAVE scientist
    void addScientist(Scientist scientis);

    //LOAD file
    Scientist parseInput(vector<string> csvLine, int ID);
    vector<Scientist> getAllScientists (SortOrder sort);
    vector<Computer> getAllComputers (SortOrder sort);
    vector<Scientist> findByName (string name, SortOrder sort);
    vector<Scientist> findByBirthYear (int yearFrom, int yearTo, SortOrder sort);
    vector<Scientist> findByDeathYear (int yearFrom, int yearTo, SortOrder sort);
    vector<Scientist> findBySex(string sex, SortOrder sort);
    vector<Scientist> sortBy(vector<Scientist> scientists, SortOrder sort );
    vector<string> scientistToVector(Scientist scientis);
    void writeNewScientistVectorToFile(vector<Scientist> scientists);
    int getage(Scientist oneScientist);

    // New stuff
    void initializeTables();
    void addComputer(Computer comp);
    vector<Computer> getComputers(Scientist scientis);
    vector<Scientist> getScientists(Computer computer);
    vector<TypeOfComputer> getTypeOfComputers();
    void addTypeOfComputer(TypeOfComputer type);

private:
    string fileName;
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // dataManager



