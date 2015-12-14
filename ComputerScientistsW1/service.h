#ifndef SERVICE
#define SERVICE

#include "DataManager.h"
#include "scientist.h"
#include "computer.h"
#include <string>


class Service
{
public:
    Service(string fileLocation);

    //Scientist
    void addScientist(ScientistSearch scientistSearch);
    bool isScientistSearchAvalidScientist(ScientistSearch scientist);
    void storeScientistPicture(QString fileName, int currentlySelectedID);

    QSqlQueryModel* search(ScientistSearch scientist);
    QPixmap getScientistPicture(int scientistId);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientist);

    //Computer
    void addComputer(ComputerSearch co);
    void updateComputerDatabase(ComputerSearch comp, int id);
    void deleteComputer(int id);

    QSqlQueryModel* searchComputer(ComputerSearch computer);

    //Relations
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);

private:
    DataManager* dataMan;
};

#endif // SERVICE

