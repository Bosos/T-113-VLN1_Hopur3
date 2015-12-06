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
    //Scientist parseInput(vector<string> csvLine, int ID);
    vector<Scientist> getAllScientists (ScientistSortOrder sort);
    vector<Computer> getAllComputers (ScientistSortOrder sort);
    vector<Scientist> findScientistByName (string name, ScientistSortOrder sort);
    vector<Computer> findComputerByName(string subString, ScientistSortOrder sort);
    vector<Scientist> findByBirthYear (int yearFrom, int yearTo, ScientistSortOrder sort);
    vector<Scientist> findByDeathYear (int yearFrom, int yearTo, ScientistSortOrder sort);
    vector<Scientist> findBySex(string sex, ScientistSortOrder sort);
    //vector<Scientist> sortBy(vector<Scientist> scientists, SortOrder sort );
    int getage(Scientist oneScientist);

    // New stuff
    void initializeTables();
    void addComputer(Computer comp);
    void addUser(int userId, int computerId);
    vector<Computer> getComputersFromScientistId(int scientistId);
    vector<Scientist> getScientistsFromComputerId(int computerId);
    vector<TypeOfComputer> getTypeOfComputers();
    void removeFromScientist(int id);
    void addTypeOfComputer(string type);
    string getTypeOfComputerFromId(int id);
    Scientist getScientistFromId(int id);
    void removeFromComputer(int id);
    Computer getComputerFromId(int id);
    void updateScientist(Scientist scientis);
    void updateComputer(Computer comp);

    // OLD STUFF
    //void writeNewScientistVectorToFile(vector<Scientist> scientists);
    //vector<string> scientistToVector(Scientist scientis);

private:
    Scientist getNextScientistQuery(QSqlQuery query);
    Computer getNextComputerQuery(QSqlQuery query);

    string fileName;
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // dataManager



