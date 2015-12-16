#include "service.h"

Service::Service(string fileLocation)
{
    this->dataMan = new DataManager(fileLocation);
}

//Scientist
QString Service::scientistExists(ScientistSearch scientistSearch)
{
    vector<QString> errMessages = dataMan->scientistExists(scientistSearch);
    QString completeMessage = "";
    while(errMessages.size() > 0)
    {
        completeMessage += " " + errMessages.back() + "\n";
        errMessages.pop_back();
    }
    return completeMessage;
}

QString Service::scientistExistsEdit(ScientistSearch scientistSearch)
{
    vector<QString> errMessages = dataMan->scientistExistsEdit(scientistSearch);
    QString completeMessage = "";
    while(errMessages.size() > 0)
    {
        completeMessage += " " + errMessages.back() + "\n";
        errMessages.pop_back();
    }
    return completeMessage;
}

void Service::addScientist(ScientistSearch scientistSearch)
{
    if (!isScientistSearchAvalidScientist(scientistSearch)) {return;}
    return dataMan->addScientist(scientistSearch);
}

void Service::updateScientistDatabase(ScientistSearch scientistSearch, int id)
{
    return dataMan->updateScientistDatabase(scientistSearch, id);
}

void Service::deleteScientist(int id)
{
    return dataMan->deleteScientist(id);
}

/*!
 * \brief Service::isScientistSearchAvalidScientist
 * Returns true if all of the new information is valid while
 * adding a new scientist
 * \param scientist
 * \return
 */
bool Service::isScientistSearchAvalidScientist(ScientistSearch scientistSearch)
{
    if (scientistSearch.name.length() < 1) { return false; }
    if (scientistSearch.getSex() != "M" && scientistSearch.getSex() != "F" ) { return false; }
    if (scientistSearch.birth.toInt() < 1200) { return false; }
    if (scientistSearch.death.toInt() > 2015) { return false; }
    return true;
}

void Service::storeScientistPicture(QString fileName, int currentlySelectedID)
{
    return dataMan->storeScientistPicture(fileName, currentlySelectedID);
}

QSqlQueryModel* Service::search(ScientistSearch scientistSearch)
{
    return dataMan->search(scientistSearch);
}

QPixmap Service::getScientistPicture(int scientistId)
{
    return dataMan->getScientistPicture(scientistId);
}

Scientist Service::makeScientistFromSearchCriteria(ScientistSearch scientistSearch)
{
    return dataMan->makeScientistFromSearchCriteria(scientistSearch);
}

//Computer
QString Service::computerExists(ComputerSearch computerSearch)
{
    vector<QString> errMessages = dataMan->computerExistsEdit(computerSearch);
    QString completeMessage = "";
    while(errMessages.size() > 0)
    {
        completeMessage += " " + errMessages.back() + "\n";
        errMessages.pop_back();
    }
    return completeMessage;
}

QString Service::computerExistsEdit(ComputerSearch computerSearch)
{
    vector<QString> errMessages = dataMan->computerExistsEdit(computerSearch);
    QString completeMessage = "";
    while(errMessages.size() > 0)
    {
        completeMessage += " " + errMessages.back() + "\n";
        errMessages.pop_back();
    }
    return completeMessage;
}

void Service::addComputer(ComputerSearch computerSearch)
{
    if (!isComputerSearchAvalidComputer(computerSearch)) {return;}
    return dataMan->addComputer(computerSearch);
}

void Service::updateComputerDatabase(ComputerSearch computerSearch, int id)
{
    return dataMan->updateComputerDatabase(computerSearch, id);
}

void Service::deleteComputer(int id)
{
    return dataMan->deleteComputer(id);
}

/*!
 * \brief isComputerSearchAvalidComputer
 * Returns true if all of the new information is valid while
 * adding a new computer
 * \param computer
 * \return
 */
bool Service::isComputerSearchAvalidComputer(ComputerSearch computerSearch)
{
    if (computerSearch.name.length() < 1) { return false; }
    if (computerSearch.buildYear.toInt() < 1200 && computerSearch.buildYear.toInt() > 2015) { return false; }
    return true;
}

QSqlQueryModel* Service::searchComputer(ComputerSearch computerSearch)
{
    return dataMan->searchComputer(computerSearch);
}

QPixmap Service::getComputerPicture(int computerId)
{
    return dataMan->getComputerPicture(computerId);
}

void Service::storeComputerPicture(QString fileName, int currentlySelectedComputerID)
{
    return dataMan->storeComputerPicture(fileName, currentlySelectedComputerID);
}

//Relations
QSqlQueryModel* Service::searchScientistToComputer(int id)
{
    return dataMan->searchScientistToComputer(id);
}

QSqlQueryModel* Service::searchComputerToScientist(int id)
{
    return dataMan->searchComputerToScientist(id);
}

void Service::addCSRelation(int userId, int computerId)
{
    return dataMan->addCSRelation(userId, computerId);
}

void Service::removeCSRelation(int userId, int computerId)
{
    return dataMan->removeCSRelation(userId, computerId);
}

vector<QString> Service::relationExists(int sID, int cID)
{
    return dataMan->relationExists(sID, cID);
}
