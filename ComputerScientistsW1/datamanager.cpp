#include "DataManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <QSqlQuery>
#include <QSqlRecord>

// having problems with queries? try this
//    auto error = query.lastError();
//    if (error.isValid()) {
//        cout << "ERROR: " << error.text().toStdString() << endl;
//        cout << query.lastQuery().toStdString() << endl;
//    }
/*!
 * \brief DataManager::initializeTables
 */
void DataManager::initializeTables()
{
    query.exec(" CREATE TABLE IF NOT EXISTS scientists ("
               " ID INTEGER primary key NOT NULL,"
               " name VARCHAR(100) NOT NULL,"
               " sex CHAR(1) NOT NULL,"
               " birth INT NOT NULL,"
               " death INT,"
               " About text)"
              );

    query.exec(" CREATE TABLE IF NOT EXISTS pctype ("
               " ID INTEGER primary key NOT NULL,"
               " type VARCHAR(100) NOT NULL)"
              );

    query.exec(" CREATE TABLE IF NOT EXISTS computers ("
               " ID INTEGER primary key NOT NULL,"
               " name VARCHAR(255) NOT NULL,"
               " buildyear INT,"
               " type INT REFERENCES pctype(ID) NOT NULL,"
               " wasbuilt INT,"
               " About text)"
              );

    query.exec(" CREATE TABLE IF NOT EXISTS users ("
               " ID INTEGER primary key NOT NULL,"
               " scientistID INT NOT NULL REFERENCES scientists(ID) ON DELETE CASCADE,"
               " computerID INT NOT NULL REFERENCES computers(ID) ON DELETE CASCADE,"
               " CONSTRAINT oneUser UNIQUE (scientistID,computerID))"
              );

    query.exec("INSERT OR REPLACE INTO pctype VALUES (1, 'Electronic')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (2, 'Mecanic')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (3, 'Transistor')");
    query.exec("PRAGMA foreign_keys = ON");
    query.exec("PRAGMA encoding = \"UTF-8\";");
}

DataManager::DataManager(string dataBaseLocation)
{
    this->fileName = dataBaseLocation;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString(fileName.c_str()));
    db.open();

    query = QSqlQuery(db);
    initializeTables();
}

/*!
 * \brief DataManager::getComputersFromScientistId
 * Get all computers that are related to the selected scientist
 * \param scientistId
 * \returns computers
 */
vector<Computer> DataManager::getComputersFromScientistId(int scientistId)
{
    vector<Computer> allRelatedComputers;
    QSqlQuery query(db);
    query.prepare("SELECT computers.*"
                  " FROM computers"
                  " JOIN users on computers.ID = users.computerID"
                  " WHERE users.scientistID = :sciID");
    query.bindValue(":sciID", scientistId);
    query.exec();

    while(query.next())
    {
        allRelatedComputers.push_back(getNextComputerQuery(query));
    }
    return allRelatedComputers;
}

/*!
 * \brief DataManager::getScientistsFromComputerId
 * Get all scientist that are related to the selected computer
 * \param computerId
 * \returns scientists
 */
vector<Scientist> DataManager::getScientistsFromComputerId(int computerId)
{
    vector<Scientist> allRelatedScientist;
    QSqlQuery query(db);
    query.prepare("SELECT scientists.*"
                  " FROM scientists"
                  " JOIN users on scientists.ID = users.scientistID"
                  " WHERE users.computerID = :comID");
    query.bindValue(":comID", computerId);
    query.exec();
    while(query.next())
    {
        allRelatedScientist.push_back(getNextScientistQuery(query));
    }
    return allRelatedScientist;
}

/*!
 * \brief DataManager::getAllTypesOfComputers
 * Gets all the different kinds of types
 * \returns types
 */
vector<TypeOfComputer> DataManager::getAllTypesOfComputers()
{
    vector<TypeOfComputer> returnTypes;

    QSqlQuery record("SELECT * FROM pctype");
    while (record.next())
    {
        int id = record.value("id").toUInt();
        string name = record.value("type").toString().toStdString();
        TypeOfComputer newType(id,name);
        returnTypes.push_back(newType);
    }
    return returnTypes;
}

/*!
 * \brief DataManager::getTypeOfComputerFromId
 * \param id
 * Gets the type of the computer selected with an id
 * \returns type
 */
string DataManager::getTypeOfComputerFromId(int id)
{
    string toQstring = "SELECT type FROM pctype WHERE id == " + to_string(id);
    QSqlQuery record(toQstring.c_str());
    record.next();
    return record.value(0).toString().toStdString();
}

/*!
 * \brief DataManager::getScientistFromId
 * \param id
 * Gets the scientist selected with an id
 * \returns scientist
 */
Scientist DataManager::getScientistFromId(int id)
{
    //QSqlQuery query(db); // may or maynot be needed uncomment if database seems flaky
    query.prepare("SELECT * FROM scientists WHERE id == :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    return getNextScientistQuery(query);
}

/*!
 * \brief DataManager::getComputerFromId
 * \param id
 * Gets the computer selected with an id
 * \returns computer
 */
Computer DataManager::getComputerFromId(int id)
{
    //QSqlQuery query(db); // may or maynot be needed uncomment if database seems flaky
    query.prepare("SELECT * FROM computers WHERE id == :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    return getNextComputerQuery(query);
}

/*!
 * \brief DataManager::addTypeOfComputer
 * \param type
 * Adds another type of computer if needed
 */
void DataManager::addTypeOfComputer(string type)
{
    string newType = "INSERT OR REPLACE INTO pctype (type) VALUES ('" + type + "')";
    query.exec(newType.c_str());
    db.commit();
}

/*!
 * \brief DataManager::addUser
 * \param userId
 * \param computerId
 * Adds a connection between a scientist and a computer,
 * computer owned by scientist\scientist owned a computer
 */
void DataManager::addCSRelation(int userId, int computerId)
{
    string newType = "INSERT OR REPLACE INTO users (scientistID,computerID) VALUES ('"
            + to_string(userId) + "','"
            + to_string(computerId) + "' )";

    query.exec(newType.c_str());
    db.commit();
}

// edit type?
//void DataManager::editTypeOfComputer(TypeOfComputer type)
//{
//    query.exec("");
//}

/*!
 * \brief DataManager::removeFromScientist
 * \param id
 * Deletes the scientist selected with an id
 */
void DataManager::removeFromScientist(int id)
{
    string deleteSci = "DELETE FROM scientists WHERE ID = " + to_string(id);

    query.exec(deleteSci.c_str());
    db.commit();
}

/*!
 * \brief DataManager::removeFromComputer
 * \param id
 * Deletes the computer selected with an id
 */
void DataManager::removeFromComputer(int id)
{
    string deleteComp = "DELETE FROM computers WHERE ID = " + to_string(id);
    query.exec(deleteComp.c_str());
    db.commit();
}

/*!
 * \brief DataManager::removeCSRelation
 * Deletes the relation between the id's selected
 */
void DataManager::removeCSRelation(int userId, int computerId)
{
    string deleteUser = "DELETE FROM users WHERE scientistID = " + to_string(userId) + " AND computerID = " + to_string(computerId);
    query.exec(deleteUser.c_str());
    db.commit();
}

DataManager::~DataManager(){}

/*!
 * \brief DataManager::addScientist
 * Adds a scientist to the database
 * \param Scientis
 */
void DataManager::addScientist(Scientist scientis)
{
    string currScientist = "";
    if (scientis.getDeathYear() == 0)
    {
         currScientist = "INSERT INTO scientists(name,sex,birth,about)"
              "VALUES('" + scientis.getName()
                 + "','" + scientis.getSex()
                 + "','" + to_string(scientis.getBirthYear())
                 + "','" + scientis.getAbout() + "')";
    }
    else
    {
        currScientist = "INSERT INTO scientists(name,sex,birth,death,about)"
             "VALUES('" + scientis.getName()
                + "','" + scientis.getSex()
                + "','" + to_string(scientis.getBirthYear())
                + "','" + to_string(scientis.getDeathYear())
                + "','" + scientis.getAbout() + "')";
    }

    query.exec(QString::fromUtf8(currScientist.c_str()));
}

/*!
 * \brief DataManager::addComputer
 * Adds a computer to the database
 * \param comp
 */
void DataManager::addComputer(Computer comp)
{
    query.prepare("INSERT INTO computers(name, buildyear, type, wasbuilt, about)"
                  "VALUES(:name, :buildyear, :type, :wasbuilt, :about)");
    query.bindValue(":name", comp.getName().c_str());
    query.bindValue(":buildyear", comp.getBuildYear());
    query.bindValue(":type", comp.getType());
    query.bindValue(":wasbuilt", comp.getWasItBuilt());
    query.bindValue(":about", comp.getAbout().c_str());
    query.exec();
}

/*!
 * \brief DataManager::getAllScientists
 * \param sort
 * \returns all the scientists in the database in a sorted order
 */
vector<Scientist> DataManager::getAllScientists(ScientistSortOrder sort)
{
    vector<Scientist> allScientists;

    QSqlQuery query(db);

    // Otputs the list as the user wants it sorted
    string command = "SELECT * FROM scientists ORDER BY " + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();
    query.exec(command.c_str());

    // Creates a scientist from the values and inserts the scientist to a vector
    while(query.next())
    {
        allScientists.push_back(getNextScientistQuery(query));
    }

    return allScientists;
}

// query.next MUST be called before or it will fetch old/wrong data
/*!
 * \brief DataManager::getNextScientistQuery
 * \param query
 * \returns the next scientist
 */
Scientist DataManager::getNextScientistQuery(QSqlQuery query)
{
    int id = query.value("ID").toUInt();
    string name = query.value("name").toString().toUtf8().constData() ;
    string sex = query.value("sex").toString().toStdString();
    int birth = query.value("birth").toUInt();
    int death = query.value("death").toUInt();
    string about = query.value("About").toString().toStdString();

    return Scientist(name, sex[0], birth, death, about, id);
}

/*!
 * \brief DataManager::getAllComputers
 * \param sort
 * \returns all the computers in the database in a sorted order
 */
vector<Computer> DataManager::getAllComputers(ComputerSortOrder sort)
{
    vector<Computer> allComputers;
    QSqlQuery query(db);

    // Otputs the list as the user wants it sorted
    string command = "SELECT * FROM computers ORDER BY " + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();
    query.exec(command.c_str());

    // Creates a computer from the values and inserts the scientist to a vector
    while(query.next())
    {
        allComputers.push_back(getNextComputerQuery(query));
    }
    return allComputers;
}

// query.next MUST be called before or it will fetch old/wrong data
/*!
 * \brief DataManager::getNextComputerQuery
 * \param query
 * \returns the next computer
 */
Computer DataManager::getNextComputerQuery(QSqlQuery query)
{
    int id = query.value("ID").toUInt();
    string name = query.value("name").toString().toStdString();
    int buildYear = query.value("buildyear").toUInt();
    int type = query.value("type").toUInt();
    bool wasItBuilt = query.value("wasbuilt").toUInt();
    string about = query.value("about").toString().toStdString();

    return Computer(name, buildYear, type, wasItBuilt, about, id);
}

/*!
 * \brief DataManager::findScientistByName
 * \param subString
 * \param sort
 * \returns all scientists matching the substring, if any
 */
vector<Scientist> DataManager::findScientistByName(string subString, ScientistSortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;
    string temp;
    string name;

    //sets substring to all lowercase
    for(unsigned int i = 0; i < subString.length(); i++)
    {
        subString[i] = tolower(subString[i]);
    }

    //Checks all scientists and inserts the ones who's name matches name parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        name = allScientists[i].getName();

        //sets the scientist name to all lowercase
        for(unsigned int j = 0; j < name.length(); j++)
        {
            temp += tolower(name[j]);
        }

        //inserts the matching scientists to a vector
        if(temp.find(subString) != std::string::npos)
        {
             matchingScientists.push_back(allScientists[i]);
        }
        temp = "";
    }
    return matchingScientists;
}

/*!
 * \brief DataManager::findComputerByName
 * \param subString
 * \param sort
 * \returns all computers matching the substring, if any
 */
vector<Computer> DataManager::findComputerByName(string subString, ComputerSortOrder sort)
{
    vector<Computer> allComputers = getAllComputers(sort);
    vector<Computer> matchingComputers;
    string temp;
    string name;

    //sets substring to all lowercase
    for(unsigned int i = 0; i < subString.length(); i++)
    {
        subString[i] = tolower(subString[i]);
    }

    //Checks all scientists and inserts the ones who's name matches name parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allComputers.size(); i++)
    {
        name = allComputers[i].getName();

        //sets the scientist name to all lowercase
        for(unsigned int j = 0; j < name.length(); j++)
        {
            temp += tolower(name[j]);
        }

        //inserts the matching scientists to a vector
        if(temp.find(subString) != std::string::npos)
        {
             matchingComputers.push_back(allComputers[i]);
        }
        temp = "";
    }
    return matchingComputers;
}

/*!
 * \brief DataManager::findByBirthYear
 * \param yearFrom
 * \param yearTo
 * \param sort
 * \returns all scientists with birthYear on given range
 */
vector<Scientist> DataManager::findByBirthYear(int yearFrom, int yearTo, ScientistSortOrder sort)
{
    vector<Scientist> matchingScientists;

    string scientis = "SELECT * FROM scientists WHERE birth >= '" + to_string(yearFrom)
                      + "' AND birth <= '" + to_string(yearTo) + "' ORDER BY "
                      + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();

    query.exec(scientis.c_str());

    while(query.next())
    {
        matchingScientists.push_back(getNextScientistQuery(query));
    }

    return matchingScientists;
}

/*!
 * \brief DataManager::findByDeathYear
 * \param yearFrom
 * \param yearTo
 * \param sort
 * \returns all scientists with deathYear on given range
 */
vector<Scientist> DataManager::findByDeathYear(int yearFrom, int yearTo, ScientistSortOrder sort)
{
    vector<Scientist> matchingScientists;

    string scientis = "SELECT * FROM scientists WHERE death >= '" + to_string(yearFrom)
                      + "' AND birth <= '" + to_string(yearTo) + "'ORDER BY "
                      + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();

    query.exec(scientis.c_str());

    while(query.next())
    {
        matchingScientists.push_back(getNextScientistQuery(query));
    }

    return matchingScientists;
}

/*!
 * \brief DataManager::findBySex
 * \param sex
 * \param sort
 * \returns all scientists matching the selected sex
 */
vector<Scientist> DataManager::findBySex(string sex, ScientistSortOrder sort)
{
    vector<Scientist> matchingScientists;

    string scientis = "SELECT * FROM scientists WHERE sex = '" + sex + "' ORDER BY "
                      + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();

    query.exec(scientis.c_str());

    while(query.next())
    {
        matchingScientists.push_back(getNextScientistQuery(query));
    }

    return matchingScientists;
}

/*!
 * \brief DataManager::findComputerByBuildYear
 * \param yearFrom
 * \param yearTo
 * \param sort
 * \returns all computers built on given range
 */
vector<Computer> DataManager::findComputerByBuildYear (int yearFrom, int yearTo, ComputerSortOrder sort)
{
    vector<Computer> matchingComputers;

    string comp = "SELECT * FROM computers WHERE buildyear >= '" + to_string(yearFrom)
                      + "' AND buildyear <= '" + to_string(yearTo) + "' ORDER BY "
                      + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();

    query.exec(comp.c_str());

    while(query.next())
    {
        matchingComputers.push_back(getNextComputerQuery(query));
    }

    return matchingComputers;
}

/*!
 * \brief DataManager::findComputerByType
 * \param type
 * \param sort
 * \returns all computers matching the selected type
 */
vector<Computer> DataManager::findComputerByType (int type, ComputerSortOrder sort)
{
    vector<Computer> matchingComputers;

    string comp = "SELECT * FROM computers WHERE type = '" + to_string(type) + "' ORDER BY "
                  + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();

    query.exec(comp.c_str());

    while(query.next())
    {
        matchingComputers.push_back(getNextComputerQuery(query));
    }

    return matchingComputers;
}

/*!
 * \brief DataManager::findComputerByWasItBuilt
 * \param wasBuilt
 * \param sort
 * \returns all computers which were ether built or not, depends on what the user selected
 */
vector<Computer> DataManager::findComputerByWasItBuilt (bool wasBuilt ,ComputerSortOrder sort)
{
    vector<Computer> matchingComputers;

    string comp = "SELECT * FROM computers WHERE wasbuilt = '" + to_string(wasBuilt) + "' ORDER BY "
                  + sort.getSortByString() + " COLLATE NOCASE " + sort.getDirectionString();

    query.exec(comp.c_str());

    while(query.next())
    {
        matchingComputers.push_back(getNextComputerQuery(query));
    }

    return matchingComputers;
}

/*!
 * \brief DataManager::getAge
 * Calculates age of scientist
 * \param oneScientist
 * \returns the age of the selected scientist
 */
int DataManager::getAge(Scientist oneScientist)
{
    if(oneScientist.getDeathYear() == 0)
    {
        return 2015 - oneScientist.getBirthYear();
    }
    return oneScientist.getDeathYear() - oneScientist.getBirthYear();
}

/*!
 * \brief DataManager::updateScientist
 * Updates the selected scientist with something new instead of the old
 * \param scientis
 */
void DataManager::updateScientist(Scientist scientis)
{
    string update = "";

    if (scientis.getDeathYear() == 0)
    {
         update = "INSERT OR REPLACE INTO scientists(ID,name,sex,birth,about)"
              "VALUES('" + to_string(scientis.getID())
                 + "','" + scientis.getName()
                 + "','" + scientis.getSex()
                 + "','" + to_string(scientis.getBirthYear())
                 + "','" + scientis.getAbout() + "')";
    }
    else
    {
        update = "INSERT OR REPLACE INTO scientists(ID,name,sex,birth,death,about)"
             "VALUES('" + to_string(scientis.getID())
                + "','" + scientis.getName()
                + "','" + scientis.getSex()
                + "','" + to_string(scientis.getBirthYear())
                + "','" + to_string(scientis.getDeathYear())
                + "','" + scientis.getAbout() + "')";
    }

    query.exec(update.c_str());
}

/*!
 * \brief DataManager::updateComputergit push
 * Updates the selected computer with something new instead of the old
 * \param comp
 */
void DataManager::updateComputer(Computer comp)
{
    query.prepare("INSERT OR REPLACE INTO computers(ID,name,buildyear,type,wasbuilt,about)"
                  " VALUES(:id, :name, :buildyear, :type, :wasbuilt, :about)");
    query.bindValue(":id", comp.getID());
    query.bindValue(":name", comp.getName().c_str());
    query.bindValue(":buildyear", comp.getBuildYear());
    query.bindValue(":type", comp.getType());
    query.bindValue(":wasbuilt", comp.getWasItBuilt());
    query.bindValue(":about", comp.getAbout().c_str());
    query.exec();
}
