#ifndef SERVICE
#define SERVICE
#include "DataManager.h"
#include "Scientist.h"
#include "Computer.h"
#include "stdlib.h"
#include <vector>
#include <SortBy.h>
#include <TypeOfComputer.h>
#include <SearchCriteria.h>
#include <QGraphicsPixmapItem>

/*!
 * \brief The Service class
 * It's responsible for the communication between the interface and the data manager
 */
class Service
{
public:
    Service(string fileLocation);

    //Scientist
    void addScientist(ScientistSearch scientistSearch);
    void updateScientistDatabase(ScientistSearch scientistSearch, int id);
    void deleteScientist(int id);
    bool isScientistSearchAvalidScientist(ScientistSearch scientistSearch);
    void storeScientistPicture(QString fileName, int currentlySelectedID);
    vector<QString> scientistExists(ScientistSearch scientistSearch);

    QSqlQueryModel* search(ScientistSearch scientistSearch);
    QPixmap getScientistPicture(int scientistId);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientistSearch);

    //Computer
    void addComputer(ComputerSearch computerSearch);
    void updateComputerDatabase(ComputerSearch computerSearch, int id);
    void deleteComputer(int id);
    bool isComputerSearchAvalidComputer(ComputerSearch computerSearch);
    QPixmap getComputerPicture(int computerId);
    void storeComputerPicture(QString fileName, int currentlySelectedComputerID);
    vector<QString> computerExists(ComputerSearch computerSearch);

    QSqlQueryModel* searchComputer(ComputerSearch computerSearch);

    //Relations
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);
    void addCSRelation(int userId, int computerId);
    void removeCSRelation(int userId, int computerId);

private:
    DataManager* dataMan;
};

#endif // SERVICE

