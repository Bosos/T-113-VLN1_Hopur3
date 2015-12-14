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
    QSqlQueryModel* search(ScientistSearch scientist);
    bool isScientistSearchAvalidScientist(ScientistSearch scientist);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientist);
    void storeScientistPicture(QString fileName, int currentlySelectedID);
    QPixmap getScientistPicture(int scientistId);

    QSqlQueryModel* searchComputer(ComputerSearch computerSearch);
    void addComputer(ComputerSearch computerSearch);
    void updateComputerDatabase(ComputerSearch computerSearch, int id);
    void deleteComputer(int id);
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);

private:
    QSqlDatabase db;
    QSqlQuery query;
    void initializeTables();

    string fileName;

};

#endif // dataManager
