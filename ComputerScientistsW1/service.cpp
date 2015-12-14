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
void Service::addComputer(ComputerSearch co)
{
    return dataMan->addComputer(co);
}

void Service::updateComputerDatabase(ComputerSearch comp, int id)
{
    return dataMan->updateComputerDatabase(comp, id);
}

void Service::deleteComputer(int id)
{
    return dataMan->deleteComputer(id);
}

bool isComputerSearchAvalidComputer(ComputerSearch computer)
{
    if (computer.name.length() < 1) { return false; }
    if (computer.buildYear.toInt() < 1200 && computer.buildYear.toInt() > 2015) { return false; }
    return true;
}

QSqlQueryModel* Service::searchComputer(ComputerSearch computer)
{
    return dataMan->searchComputer(computer);
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
