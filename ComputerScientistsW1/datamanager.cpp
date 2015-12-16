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
using namespace std;

/*!
 * \brief DataManager::DataManager
 * DataManager constructer, he takes in the database location and remembers it
 * \param dataBaseLocation
 */
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
 * \brief DataManager::makeScientistFromSearchCriteria
 * \param scientistSearch
 * \return Scientist
 */
Scientist DataManager::makeScientistFromSearchCriteria(ScientistSearch scientistSearch)
{
    return Scientist(scientistSearch.name,
                     scientistSearch.getSex().toStdString().at(0),
                     scientistSearch.birth.toInt(),
                     scientistSearch.death.toInt(),
                     scientistSearch.about,
                     0
                     );
}

/*!
 * \brief DataManager::addScientist
 * Adds a scientist to the database
 * \param Scientis
 */
void DataManager::addScientist(ScientistSearch scientistSearch)
{
    Scientist scientist = makeScientistFromSearchCriteria(scientistSearch);
    string currScientist = "";

    if (scientist.getDeathYear() == 0)
    {
        currScientist = "INSERT INTO scientists(name,sex,birth,about)"
                      "VALUES('" + scientist.getName().toStdString()
                         + "','" + scientist.getSex()
                         + "','" + to_string(scientist.getBirthYear())
                         + "','" + scientist.getAbout().toStdString() + "')";
    }
    else
    {
        currScientist = "INSERT INTO scientists(name,sex,birth,death,about)"
                     "VALUES('" + scientist.getName().toStdString()
                        + "','" + scientist.getSex()
                        + "','" + to_string(scientist.getBirthYear())
                        + "','" + to_string(scientist.getDeathYear())
                        + "','" + scientist.getAbout().toStdString() + "')";
    }

    query.clear();
    query.exec(currScientist.c_str());
    qDebug() << "string put into query: " << currScientist.c_str();
    qDebug() << "the real thing: " << query.executedQuery();

}

/*!
 * \brief DataManager::deleteScientist
 * deletes a scientist in the database
 * \param Scientis
 */
void DataManager::deleteScientist(int id)
{
    stringstream ss;
    ss << id;
    string strID = ss.str();

    query.prepare("DELETE FROM scientists"
                  " WHERE id = :id");

    query.bindValue(":id", strID.c_str());
    query.exec();

}

/*!
 * \brief DataManager::search
 * A "search all fields" type of search to find scientists with bits and pieces of information
 * \param ScientistSearch
 * \returns a QSqlQueryModel which table views can display
 */
QSqlQueryModel* DataManager::search(ScientistSearch scientist)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(db);

    string meme = "SELECT s.id, s.name as Name, sex.value as Sex, s.birth as Birth, s.death as Death, s.about"
                  " FROM scientists s"
                  " JOIN sex USING (sex)"
                  " where name like '%" + scientist.name.toStdString() + "%'"
                  " and sex like '%" + scientist.getSex().toStdString() + "%'"
                  " and birth like '%" + scientist.birth.toStdString() + "%'"
                  " and ifnull (death,'') like '%" + scientist.death.toStdString() + "%'"
                  " and about like '%" + scientist.about.toStdString() + "%'";

    qDebug() << meme.c_str();
    query->exec(meme.c_str());
    model->setQuery(*query);
    return model;
}

/*!
 * \brief DataManager::storeScientistPicture
 * Stores an image in the database as a blob, each scientist can only have one picture
 * \param fileName
 * \param scientistId
 */
void DataManager::storeScientistPicture(QString fileName, int scientistId)
{
    if(fileName.isEmpty()) { return; }

    QImage image(fileName);

    int x = image.width();
    int y = image.height();
    setScaling(x,y);

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QRect rect(0,0,x,y);
    item->setPixmap(item->pixmap().scaled(x,y,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    item->setPixmap(item->pixmap().copy(rect));

    QByteArray inByteArray;
    QBuffer inBuffer( &inByteArray );
    inBuffer.open( QIODevice::WriteOnly );
    item->pixmap().save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format
    query.clear();
    query.prepare( "INSERT OR REPLACE INTO imgTableScientist (scientistID, filename, imagedata)"
                   " VALUES (:scientistid, 'profile.png', :imageData)" );
    query.bindValue( ":scientistid", scientistId );
    query.bindValue( ":imageData", inByteArray );
    qDebug() << query.lastQuery();
    if(!query.exec()){ qDebug() << "Error inserting image into table:\n" << query.lastError();}
}

/*!
 * \brief DataManager::setScaling
 * Calculates the correct porportions for the image width and height
 * \param x
 * \param y
 */
void DataManager::setScaling(int& x, int& y)
{
    double scale = 215.0/y;
    x = x*scale;
    y = 215;
}

/*!
 * \brief DataManager::getScientistPicture
 * A getter for the scientist picture, converts the blob into a QPixmap
 * \param scientistId
 * \return
 */
QPixmap DataManager::getScientistPicture(int scientistId)
{
    query.prepare("SELECT imagedata from imgTableScientist WHERE scientistID = :sciID");
    query.bindValue( ":sciID", scientistId );
    qDebug() << query.lastQuery();

    if(!query.exec()){ qDebug() << "Error getting image from table:\n" << query.lastError(); }

    query.first();

    QByteArray outByteArray = query.value( 0 ).toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray );

    return outPixmap;
}

/*!
 * \brief DataManager::storeComputerPicture
 * Stores an image in the database as a blob, each computer can only have one picture
 * \param fileName
 * \param scientistId
 */
void DataManager::storeComputerPicture(QString fileName, int computerId)
{
    if(fileName.isEmpty()) { return; }

    QImage image(fileName);

    int x = image.width();
    int y = image.height();
    setScaling(x,y);

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QRect rect(0,0,x,y);
    item->setPixmap(item->pixmap().scaled(x,y,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    item->setPixmap(item->pixmap().copy(rect));

    QByteArray inByteArray;
    QBuffer inBuffer( &inByteArray );
    inBuffer.open( QIODevice::WriteOnly );
    item->pixmap().save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format
    query.clear();
    query.prepare( "INSERT OR REPLACE INTO imgTableComputer (computerID, filename, imagedata)"
                   " VALUES (:computerID, 'profile.png', :imageData)" );
    query.bindValue( ":computerID", computerId );
    query.bindValue( ":imageData", inByteArray );
    qDebug() << query.lastQuery();
    if(!query.exec()){ qDebug() << "Error inserting image into table:\n" << query.lastError();}
}

/*!
 * \brief DataManager::getScientistPicture
 * A getter for the computer picture, converts the blob into a QPixmap
 * \param scientistId
 * \return
 */
QPixmap DataManager::getComputerPicture(int computerId)
{
    query.prepare("SELECT imagedata from imgTableComputer WHERE computerID = :computerID");
    query.bindValue( ":computerID", computerId );
    qDebug() << query.lastQuery();

    if(!query.exec()){ qDebug() << "Error getting image from table:\n" << query.lastError(); }

    query.first();

    QByteArray outByteArray = query.value( 0 ).toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray );

    return outPixmap;
}

/*!
 * \brief DataManager::initializeTables
 */
void DataManager::initializeTables()
{
    query.exec("CREATE TABLE IF NOT EXISTS sex"
               " (sex CHAR(1) primary key NOT NULL,"
               " value VARCHAR(20) NOT NULL) WITHOUT ROWID");

    query.exec("CREATE TABLE IF NOT EXISTS scientists ("
               " ID INTEGER primary key NOT NULL,"
               " Name VARCHAR(100) NOT NULL,"
               " Sex CHAR(1) REFERENCES sex(sex) NOT NULL,"
               " Birth INT NOT NULL,"
               " Death INT,"
               " About text,"
               " CONSTRAINT oneScientist UNIQUE (Name, Sex, Birth, Death))"
              );

    query.exec("CREATE TABLE IF NOT EXISTS pctype ("
               " ID INTEGER primary key NOT NULL,"
               " type VARCHAR(100) NOT NULL)"
              );

    query.exec("CREATE TABLE IF NOT EXISTS computers ("
               " ID INTEGER primary key NOT NULL,"
               " Name VARCHAR(255) NOT NULL,"
               " Buildyear INT,"
               " Type INT REFERENCES pctype(ID) NOT NULL,"
               " Wasbuilt INT,"
               " About text,"
               " CONSTRAINT oneComputer UNIQUE (Name, Buildyear, Type, Wasbuilt))"
              );

    query.exec("CREATE TABLE IF NOT EXISTS users ("
               " ID INTEGER primary key NOT NULL,"
               " scientistID INT NOT NULL REFERENCES scientists(ID) ON DELETE CASCADE,"
               " computerID INT NOT NULL REFERENCES computers(ID) ON DELETE CASCADE,"
               " CONSTRAINT oneUser UNIQUE (scientistID,computerID))"
              );

    query.exec("CREATE TABLE IF NOT EXISTS imgTableScientist ("
               " scientistID INT NOT NULL REFERENCES scientists(ID) ON DELETE CASCADE,"
               " filename TEXT,"
               " imagedata BLOB,"
               " CONSTRAINT onePicture UNIQUE (scientistID))"
               );

    query.exec("CREATE TABLE IF NOT EXISTS imgTableComputer ("
               " computerID INT NOT NULL REFERENCES computers(ID) ON DELETE CASCADE,"
               " filename TEXT,"
               " imagedata BLOB,"
               " CONSTRAINT onePicture UNIQUE (computerID))"
               );

    query.exec("INSERT OR REPLACE INTO sex VALUES ('F', 'Female')");
    query.exec("INSERT OR REPLACE INTO sex VALUES ('M', 'Male')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (1, 'Electronic')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (2, 'Mecanic')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (3, 'Transistor')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (4, 'Electromechanical')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (5, 'Other')");
    query.exec("PRAGMA foreign_keys = ON");
    query.exec("PRAGMA encoding = \"UTF-8\";");
}

/*!
 * \brief DataManager::search
 * A "search all fields" type of search to find computers with bits and pieces of information
 * \param ComputerSearch
 * \returns a QSqlQueryModel which table views can display
 */
QSqlQueryModel* DataManager::searchComputer(ComputerSearch computerSearch)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(db);

    string computer = "SELECT c.ID, c.Name, t.type AS Type, c.Buildyear AS 'Year',"
                      " CASE c.wasbuilt WHEN 1 THEN 'Yes'"
                      " ELSE 'No'"
                      " END AS 'Was it built?',"
                      " c.About"
                      " FROM computers c JOIN pctype t ON c.Type = t.ID"
                      " WHERE c.Name LIKE '%" + computerSearch.name.toStdString() + "%'"
                      " AND c.Type LIKE '%" + computerSearch.getType().toStdString() + "%'"
                      " AND c.Buildyear LIKE '%" + computerSearch.buildYear.toStdString() + "%'"
                      " AND c.Wasbuilt LIKE '%" + computerSearch.getWasItBuilt().toStdString() + "%'"
                      " AND c.About LIKE '%" + computerSearch.about.toStdString() + "%'";

    qDebug() << ( computer.c_str() );
    query->exec(computer.c_str());
    model->setQuery(*query);

    return model;
}

/*!
 * \brief DataManager::addComputer
 * Adds the given computer to the database
 * \param computerSearch
 */
void DataManager::addComputer(ComputerSearch computerSearch)
{
    bool wasItBuilt = computerSearch.getWasItBuilt().toInt();

    Computer computer(computerSearch.name.toStdString(),
                      computerSearch.buildYear.toInt(),
                      computerSearch.getType().toInt(),
                      wasItBuilt,
                      computerSearch.about.toStdString(),
                      0);


    query.prepare("INSERT INTO computers(name, buildyear, type, wasbuilt, about)"
                  "VALUES(:name, :buildyear, :type, :wasbuilt, :about)");
    query.bindValue(":name", computer.getName().c_str());
    query.bindValue(":buildyear", computer.getBuildYear());
    query.bindValue(":type", computer.getType());
    query.bindValue(":wasbuilt", computer.getWasItBuilt());
    query.bindValue(":about", computer.getAbout().c_str());
    query.exec();
}

/*!
 * \brief DataManager::updateScientistDatabase
 * Updates the scientist database
 * \param scientistSearch
 * \param id
 */
void DataManager::updateScientistDatabase(ScientistSearch scientistSearch, int id)
{
    query.prepare("UPDATE scientists"
                  " SET name = :name, birth = :birth, death = :death, about = :about, sex = :sex "
                  " WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":name", scientistSearch.name);
    query.bindValue(":birth", scientistSearch.birth);
    query.bindValue(":death", scientistSearch.death);
    query.bindValue(":sex", scientistSearch.getSex());
    query.bindValue(":about", scientistSearch.about);
    query.exec();
}

/*!
 * \brief DataManager::updateComputerDatabase
 * Updates the computer database
 * \param computerSearch
 * \param id
 */
void DataManager::updateComputerDatabase(ComputerSearch computerSearch, int id)
{
    query.prepare("UPDATE computers"
                  " SET name = :name, type = :type, buildyear = :buildyear, wasbuilt = :wasbuilt, about = :about"
                  " WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":name", computerSearch.name);
    query.bindValue(":buildyear", computerSearch.buildYear);
    query.bindValue(":type", computerSearch.getType());
    query.bindValue(":wasbuilt", computerSearch.getWasItBuilt());
    query.bindValue(":about", computerSearch.about);
    query.exec();
}

/*!
 * \brief DataManager::deleteComputer
 * Deletes a computer from the database, relations are handled and deleted when appropriate by the database
 * \param id
 */
void DataManager::deleteComputer(int id)
{
    stringstream ss;
    ss << id;
    string strID = ss.str();

    query.prepare("DELETE FROM computers"
                  " WHERE id = :id");

    query.bindValue(":id", strID.c_str());
    query.exec();
}

/*!
 * \brief DataManager::searchScientistToComputer
 * Finds the "Users" of a given computer
 * \param id
 * \return
 */
QSqlQueryModel* DataManager::searchScientistToComputer(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(db);

    stringstream ss;
    ss << id;
    string strID = ss.str();

    string search = "SELECT s.id, s.name, sex.value as Sex, s.birth as 'Birth year', s.death as 'Death year', s.about"
                    " FROM users u JOIN scientists s ON u.scientistID = s.ID"
                    " JOIN sex USING (sex)"
                    " WHERE u.computerID = '" + strID + "'";

    QString sci = search.c_str();
    qDebug() << ( sci );
    query->exec(search.c_str());
    model->setQuery(*query);

    return model;
}

/*!
 * \brief DataManager::searchComputerToScientist
 * Finds the computers the "User" has used
 * \param id
 * \return
 */
QSqlQueryModel* DataManager::searchComputerToScientist(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(db);

    stringstream ss;
    ss << id;
    string strID = ss.str();

    string search = "SELECT c.ID, c.Name, p.type AS Type, c.Buildyear AS 'Year',"
                    " CASE c.wasbuilt WHEN 1 THEN 'Yes'"
                    " ELSE 'No'"
                    " END AS 'Was it built?', c.about"
                    " FROM computers c"
                    " JOIN users u ON u.computerID = c.ID"
                    " JOIN pctype p ON p.ID = c.type"
                    " WHERE u.scientistID = '" + strID + "'";

    QString sci = search.c_str();
    qDebug() << ( sci );
    query->exec(search.c_str());
    model->setQuery(*query);

    return model;
}

/*!
 * \brief DataManager::addUser
 * Adds a connection between a scientist and a computer,
 * computer owned by scientist\scientist owned a computer
 * \param userId
 * \param computerId
 */
void DataManager::addCSRelation(int userId, int computerId)
{
    string newType = "INSERT OR REPLACE INTO users (scientistID,computerID) VALUES ('"
            + to_string(userId) + "','"
            + to_string(computerId) + "' )";

    query.exec(newType.c_str());
    db.commit();
}

/*!
 * \brief DataManager::removeCSRelation
 * Deletes the relation between the id's selected
 */
void DataManager::removeCSRelation(int userId, int computerId)
{
    string deleteUser = "DELETE FROM users"
                        " WHERE scientistID = " + to_string(userId) +
                        " AND computerID = " + to_string(computerId);
    query.exec(deleteUser.c_str());
    db.commit();
}

/*!
 * \brief DataManager::relationExists
 * Builds a list of messages to be returned to a warn the user if a relation already exists
 */
vector<QString> DataManager::relationExists(int sID, int cID)
{
    stringstream ss, cs;
    ss << sID;
    cs << cID;
    string sciID = ss.str();
    string compID = cs.str();

    vector<QString> message;
    string search = "SELECT COUNT(*) AS count"
                    " FROM users"
                    " WHERE computerID = '" + compID + "'"
                    " AND scientistID = '" + sciID + "'";

    query.exec(search.c_str());
    query.next();

    if(query.value("count").toInt()) { message.push_back("This relation already exists"); }

    return message;
}

/*!
 * \brief DataManager::scientistExists
 * Builds a list of messages to be returned to a warn the user if all the required information is there for this scientist
 * Calls scientistExistsEdit for the complete package
 * \param scientistSearch
 * \return
 */
vector<QString> DataManager::scientistExists(ScientistSearch scientistSearch)
{
    vector<QString> message = scientistExistsEdit(scientistSearch);
    string search = "SELECT COUNT(*) AS count"
                    " FROM scientists"
                    " WHERE name = '" + scientistSearch.name.toStdString() + "'" +
                    " AND sex = '" + scientistSearch.getSex().toStdString() + "'" +
                    " AND birth = " + scientistSearch.birth.toStdString();

    query.exec(search.c_str());
    query.next();

    if (query.value("count").toInt()){message.push_back("This scientist seems to exist already");}
    return message;
}

/*!
 * \brief DataManager::scientistExistsEdit
 * Same as scientistExists but without the count to see if the scientist exist, which is not always needed
 * \param scientistSearch
 * \return
 */
vector<QString> DataManager::scientistExistsEdit(ScientistSearch scientistSearch)
{
    vector<QString> message;
    if (scientistSearch.getSex() == ""){message.push_back("Please select the correct gender");}
    if (scientistSearch.birth.toInt() < 1200){message.push_back("No computer scientist is born before 1200!");}
    if (scientistSearch.getAge() > 120){ message.push_back("Age should be realistic, not over 120 years old");}
    else if (scientistSearch.birth == ""){ message.push_back("Birth year can not be empty"); }
    if (scientistSearch.name == ""){message.push_back("Name can not be empty");}
    if (scientistSearch.death != "" && (scientistSearch.birth.toInt() >= scientistSearch.death.toInt()))
    {
        message.push_back("One can not die before he is born");
    }
    return message;
}

/*!
 * \brief DataManager::computerExists
 * Builds a list of messages to be returned to a warn the user if all the required information is there for this computer
 * Calls computerExistsEdit for the complete package
 * \param computerSearch
 * \return
 */
vector<QString> DataManager::computerExists(ComputerSearch computerSearch)
{
    vector<QString> message;

    string search = "SELECT COUNT(*) AS count"
                    " FROM computers"
                    " WHERE Name = '" + computerSearch.name.toStdString() + "'" +
                    " AND Type = '" + computerSearch.getType().toStdString() + "'" +
                    " AND Buildyear = '" + computerSearch.buildYear.toStdString() + "'" +
                    " AND Wasbuilt = '" + computerSearch.getWasItBuilt().toStdString()+ "'";

    query.exec(search.c_str());
    query.next();

    if (query.value("count").toInt()){message.push_back("This computer seems to exist already");}

    return message;
}

/*!
 * \brief DataManager::computerExistsEdit
 * Same as computerExists but without the count to see if the computer exist, which is not always needed
 * \param ComputerSearch
 * \return
 */
vector<QString> DataManager::computerExistsEdit(ComputerSearch computerSearch)
{
    vector<QString> message;

    if (computerSearch.name == ""){message.push_back("Name can not be empty");}
    if (computerSearch.getType() == ""){message.push_back("Please select the correct type");}
    if (computerSearch.buildYear != "")
    {   // no computer was theorized this early as far as we know
        if (computerSearch.buildYear.toInt() < 1200){message.push_back("No computer was made before 1200");}
        if (computerSearch.buildYear.toInt() > 2015){message.push_back("Can't enter a computer from the future");}
    }
    else if(computerSearch.buildYear == "") {message.push_back("Build year can not be empty"); }
    if (computerSearch.getWasItBuilt() == ""){message.push_back("Has to be specified if the computer was built");}

    return message;
}
