#include "service.h"

Service::Service(string fileLocation)
{
    this->dataMan = new DataManager(fileLocation);
}

//Scientist
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
bool Service::isScientistSearchAvalidScientist(ScientistSearch scientist)
{
    if (scientist.name.length() < 1) { return false; }
    if (scientist.getSex() != "M" && scientist.getSex() != "F" ) { return false; }
    if (scientist.birth.toInt() < 1200) { return false; }
    if (scientist.death.toInt() > 2015) { return false; }
    return true;
}

void Service::storeScientistPicture(QString fileName, int currentlySelectedID)
{
    return dataMan->storeScientistPicture(fileName, currentlySelectedID);
}

QSqlQueryModel* Service::search(ScientistSearch scientist)
{
    return dataMan->search(scientist);
}

QPixmap Service::getScientistPicture(int scientistId)
{
    return dataMan->getScientistPicture(scientistId);
}

Scientist Service::makeScientistFromSearchCriteria(ScientistSearch scientist)
{
    return dataMan->makeScientistFromSearchCriteria(scientist);
}

//Computer
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
