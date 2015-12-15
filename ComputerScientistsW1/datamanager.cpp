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
 * \param scientist
 * \return Scientist
 */
Scientist DataManager::makeScientistFromSearchCriteria(ScientistSearch scientist)
{
    return Scientist(scientist.name,
                     scientist.getSex().toStdString().at(0),
                     scientist.birth.toInt(),
                     scientist.death.toInt(),
                     scientist.about,
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

void DataManager::storeScientistPicture(QString fileName, int scientistId)
{
    if(fileName.isEmpty()) { return; }

    QImage image(fileName);

//        if(image.isNull())
//        {
//            QMessageBox::information(this,"Image Viewer","Error Displaying image");
//            return;
//        }

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QRect rect(0,0,138,178);
    item->setPixmap(item->pixmap().scaled(138,178,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
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

QSqlQueryModel* DataManager::searchComputer(ComputerSearch computerSearch)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(db);

    string computer = "SELECT c.ID, c.Name, t.type AS Type, c.Buildyear AS 'Build year',"
                      " CASE c.wasbuilt WHEN 1 THEN 'Built'"
                      " ELSE 'Not built'"
                      " END AS 'Was it built?',"
                      " c.About"
                      " FROM computers c JOIN pctype t ON c.Type = t.ID"
                      " WHERE c.Name LIKE '%" + computerSearch.name.toStdString() + "%'"
                      " AND c.Type LIKE '%" + computerSearch.getType().toStdString() + "%'"
                      " AND c.Buildyear LIKE '%" + computerSearch.buildYear.toStdString() + "%'"
                      " AND c.Wasbuilt LIKE '%" + computerSearch.getWasItBuilt().toStdString() + "%'";

    qDebug() << ( computer.c_str() );
    query->exec(computer.c_str());
    model->setQuery(*query);

    return model;
}

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

QSqlQueryModel* DataManager::searchComputerToScientist(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(db);

    stringstream ss;
    ss << id;
    string strID = ss.str();

    string search = "SELECT c.ID, c.name, c.type, c.buildyear, c.wasbuilt, c.about"
                    " FROM computers c JOIN users u ON u.computerID = c.ID"
                    " WHERE u.scientistID = '" + strID + "'";

    QString sci = search.c_str();
    qDebug() << ( sci );
    query->exec(search.c_str());
    model->setQuery(*query);

    return model;
}

int DataManager::scientistExists(ScientistSearch scientist)
{
    QSqlQueryModel model;
    int counter;

    string search = "SELECT COUNT(*) AS 'count'"
                    " FROM scientists"
                    " WHERE name LIKE '%" + scientist.name.toStdString() + "%'"
                    " AND sex LIKE '%" + scientist.getSex().toStdString() + "%'"
                    " AND birth LIKE '%" + scientist.birth.toStdString() + "%'"
                    " AND IFNULL (death,'') LIKE '%" + scientist.death.toStdString() + "%'";

    model.setQuery(search.c_str());

    counter = model.data(model.index(0, 0)).toInt();

    return counter;
}

int DataManager::computerExists(ComputerSearch computer)
{
    QSqlQueryModel model;
    int counter;

    string search = "SELECT COUNT(*)"
                    " FROM computers"
                    " WHERE Name LIKE '%" + computer.name.toStdString() + "%'"
                    " AND Type LIKE '%" + computer.getType().toStdString() + "%'"
                    " AND Buildyear LIKE '%" + computer.buildYear.toStdString() + "%'"
                    " AND Wasbuilt LIKE '%" + computer.getWasItBuilt().toStdString() + "%'";

    model.setQuery(search.c_str());

    counter = model.data(model.index(0, 0)).toInt();

    return counter;
}
