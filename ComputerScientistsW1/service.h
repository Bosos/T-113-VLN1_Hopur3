#ifndef SERVICE
#define SERVICE
#include "DataManager.h"
#include "Scientist.h"
#include "Computer.h"
#include "stdlib.h"
#include <vector>
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
    void storeScientistPicture(QString fileName, int currentlySelectedID);
    QPixmap getScientistPicture(int scientistId);
    bool isScientistSearchAvalidScientist(ScientistSearch scientistSearch);
    QString scientistExists(ScientistSearch scientistSearch);
    QString scientistExistsEdit(ScientistSearch scientistSearch);
    QSqlQueryModel* search(ScientistSearch scientistSearch);
    Scientist makeScientistFromSearchCriteria(ScientistSearch scientistSearch);

    //Computer
    void addComputer(ComputerSearch computerSearch);
    void updateComputerDatabase(ComputerSearch computerSearch, int id);
    void deleteComputer(int id);
    void storeComputerPicture(QString fileName, int currentlySelectedComputerID);
    QPixmap getComputerPicture(int computerId);
    bool isComputerSearchAvalidComputer(ComputerSearch computerSearch);
    QString computerExists(ComputerSearch computerSearch);
    QString computerExistsEdit(ComputerSearch computerSearch);
    QSqlQueryModel* searchComputer(ComputerSearch computerSearch);

    //Relations
    QSqlQueryModel* searchScientistToComputer(int id);
    QSqlQueryModel* searchComputerToScientist(int id);
    void addCSRelation(int userId, int computerId);
    void removeCSRelation(int userId, int computerId);
    QString relationExists(int sID, int cID);

private:
    DataManager* dataMan;
    QString getErrorMessages(vector<QString> errMessages);

};

#endif // SERVICE

