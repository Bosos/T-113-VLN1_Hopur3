#include "service.h"

Service::Service(string fileLocation)
{
    this->dataMan = new DataManager(fileLocation);
}

//Scientist
vector<QString> Service::scientistExists(ScientistSearch scientistSearch)
{
    return dataMan->scientistExists(scientistSearch);
}

vector<QString> Service::scientistExistsEdit(ScientistSearch scientistSearch)
{
    return dataMan->scientistExistsEdit(scientistSearch);
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
vector<QString> Service::computerExists(ComputerSearch computerSearch)
{
    return dataMan->computerExists(computerSearch);
}

vector<QString> Service::computerExistsEdit(ComputerSearch computerSearch)
{
    return dataMan->computerExistsEdit(computerSearch);
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

QPixmap Service::getComputerPicture(int computerId)
{
    return dataMan->getComputerPicture(computerId);
}

void Service::storeComputerPicture(QString fileName, int currentlySelectedComputerID)
{
    return dataMan->storeComputerPicture(fileName, currentlySelectedComputerID);
}
