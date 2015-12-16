#ifndef dataManager
#define dataManager
#include "stdlib.h"
#include <vector>
#include "Scientist.h"
#include "Computer.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlRecord>
//#include <TypeOfComputer.h>
#include <SearchCriteria.h>
#include <QGraphicsPixmapItem>

using namespace std;

/*!
 * \brief The DataManager class
 * It's responsible for comunicating with the data storage
 */
class DataManager
{
public:
    DataManager(string fileName);

    // Scientists
    void addScientist(ScientistSearch scientistSearch);
    void updateScientistDatabase(ScientistSearch scientistSearch, int id);
    void deleteScientist(int id);
    void storeScientistPicture(QString fileName, int currentlySelectedID);
    QPixmap getScientistPicture(int scientistId);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientistSearch);
    QSqlQueryModel* search(ScientistSearch scientist);
    vector<QString> scientistExists(ScientistSearch scientistSearch);
    vector<QString> scientistExistsEdit(ScientistSearch scientistSearch);

    //Computers
    void addComputer(ComputerSearch computerSearch);
    void updateComputerDatabase(ComputerSearch computerSearch, int id);
    void deleteComputer(int id);
    void storeComputerPicture(QString fileName, int currentlySelectedComputerID);
    QPixmap getComputerPicture(int computerId);
    QSqlQueryModel* searchComputer(ComputerSearch computerSearch);
    vector<QString> computerExists(ComputerSearch computerSearch);
    vector<QString> computerExistsEdit(ComputerSearch computerSearch);

    //Relations
    void addCSRelation(int userId, int computerId);
    void removeCSRelation(int userId, int computerId);
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);


private:
    QSqlDatabase db;
    QSqlQuery query;
    void initializeTables();
    void setScaling(int& bigger, int& smaller);
    string fileName;
};

#endif // dataManager
