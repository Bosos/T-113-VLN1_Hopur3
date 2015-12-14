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
    bool isScientistSearchAvalidScientist(ScientistSearch scientist);
    void storeScientistPicture(QString fileName, int currentlySelectedID);

    QSqlQueryModel* search(ScientistSearch scientist);
    QPixmap getScientistPicture(int scientistId);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientist);

    //Computer
    void addComputer(ComputerSearch computerSearch);
    void updateComputerDatabase(ComputerSearch comp, int id);
    void deleteComputer(int id);
    bool isComputerSearchAvalidComputer(ComputerSearch computerSearch);

    QSqlQueryModel* searchComputer(ComputerSearch computerSearch);

    //Relations
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);

private:
    DataManager* dataMan;
};

#endif // SERVICE

