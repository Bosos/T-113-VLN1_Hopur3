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

class Service
{
public:
    Service(string fileLocation);

    //Scientist
    void addScientist(ScientistSearch scientistSearch);
    void deleteScientist(int id);
    bool isScientistSearchAvalidScientist(ScientistSearch scientist);
    void storeScientistPicture(QString fileName, int currentlySelectedID);

    QSqlQueryModel* search(ScientistSearch scientist);
    QPixmap getScientistPicture(int scientistId);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientist);

    //Computer
    void addComputer(ComputerSearch co);
    void updateComputerDatabase(ComputerSearch comp, int id);
    void deleteComputer(int id);
    bool isComputerSearchAvalidComputer(ComputerSearch computer);

    QSqlQueryModel* searchComputer(ComputerSearch computer);

    //Relations
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);

private:
    DataManager* dataMan;
};

#endif // SERVICE

