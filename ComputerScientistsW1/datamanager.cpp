#include "DataManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <CSVWriter.h>
#include <CSVReader.h>
#include <algorithm>
#include <cstring>
#include <QSqlQuery>
#include <QSqlRecord>

void DataManager::initializeTables()
{
    query.exec("create table IF NOT EXISTS scientists ("
               "ID INTEGER primary key NOT NULL,"
               "name varchar(100) NOT NULL,"
               "sex char(1) NOT NULL,"
               "birth INT NOT NULL,"
               "death INT,"
               "About text)"
              );

    query.exec("create table IF NOT EXISTS pctype ("
               "ID INTEGER primary key NOT NULL,"
               "type varchar(100) NOT NULL)"
              );

    query.exec("create table IF NOT EXISTS computers ("
               "ID INTEGER primary key NOT NULL,"
               "name varchar(255) NOT NULL,"
               "buildyear INT,"
               "type INT REFERENCES pctype(ID) NOT NULL,"
               "wasbuilt INT,"
               "About text)"
              );

    query.exec("create table users ("
               "ID INTEGER primary key NOT NULL,"
               "scientistID INT REFERENCES scientists(ID) NOT NULL,"
               "computerID INT REFERENCES computers(ID) NOT NULL)"
              );

    query.exec("INSERT OR REPLACE INTO pctype VALUES (1, 'Electronic')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (2, 'Mecanic')");
    query.exec("INSERT OR REPLACE INTO pctype VALUES (3, 'Transistor Machine')");
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

vector<Computer> DataManager::getComputers(Scientist scientis)
{
    // TODO
    return vector<Computer>();
}

vector<Scientist> DataManager::getScientists(Computer scientis)
{
    // TODO
    return vector<Scientist>();
}

vector<TypeOfComputer> DataManager::getTypeOfComputers()
{
    vector<TypeOfComputer> returnTypes;

    QSqlQuery record("SELECT * FROM pctype");
    while (record.next())
    {
        int id = record.value(0).toUInt();
        string name = record.value(1).toString().toStdString();
        TypeOfComputer newType(id,name);
        returnTypes.push_back(newType);
    }
    return returnTypes;
}

void DataManager::addTypeOfComputer(TypeOfComputer type)
{
    // TODO
}

// edit type?



DataManager::~DataManager(){}

/*!
 * \brief DataManager::parseInput takes a vector of strings from the input and parses it into the correct format
 * \param csvLine
 * \returns a Scientist
 */
Scientist DataManager::parseInput(vector<string> csvLine, int ID)
{
    return Scientist(csvLine[0], csvLine[1].c_str()[0], stoi(csvLine[2]), stoi(csvLine[3]), csvLine[4], ID);
}

/*!
 * \brief DataManager::addScientist Adds a scientist to the cvs file
 * \param Scientist
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

    query.exec(currScientist.c_str());
}

void DataManager::addComputer(Computer comp)
{
    string currComp = "";

    currComp = "INSERT INTO computers(name, buildyear, type, wasbuilt, about)"
               "VALUES('" + comp.getName()
               + "','" + to_string(comp.getBuildYear())
               + "','" + comp.getType()
               + "','" + to_string(comp.getWasItBuilt())
               + "','" + comp.getAbout() + "')";

    query.exec(currComp.c_str());
}

/*!
 * \brief DataManager::scientistToVector
 * \param Scientist
 * \returns a vector of strings
 */
vector<string> DataManager::scientistToVector(Scientist scientis)
{
    //Changes the scientist class to a vector
    return vector<string>
    {
        scientis.getName(),
        to_string(scientis.getSex()),
        to_string(scientis.getBirthYear()),
        to_string(scientis.getDeathYear()),
        scientis.getAbout()
    };
}


vector<Scientist> DataManager::getAllScientists(SortOrder sort)
{
    /*vector<Scientist> allScientists;
    vector<vector<string>> newScientists;
    CSVReader docReader(fileName);//initialize the CSVReader class
    newScientists = docReader.readAll();//gets vectors of vectors of strings which are essentially vectors of scientist in strings
    for(unsigned i = 0; i < newScientists.size(); i++)//goes through all of the scientists
    {
        allScientists.push_back(parseInput(newScientists[i], i));//changes vectors of strings into scientist classes
    }
    return sortBy(allScientists, sort);//return the scientist in the sort chosen*/
    vector<Scientist> allScientists;

    if(db.open())
    {
        int id;
        string name;
        string sex;
        int birth;
        int death;
        string about;

        QSqlQuery query(db);

        // Otputs the list as the user wants it sorted
        if(sort.sortBy == NAME)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM scientists ORDER BY name DESC");
            else
                query.exec("SELECT * FROM scientists ORDER BY name ASC");
        }
        else if(sort.sortBy == SEX)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM scientists ORDER BY sex DESC");
            else
                query.exec("SELECT * FROM scientists ORDER BY sex ASC");
        }
        else if(sort.sortBy == BIRTH)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM scientists ORDER BY birth DESC");
            else
                query.exec("SELECT * FROM scientists ORDER BY birth ASC");
        }
        else if(sort.sortBy == DEATH)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM scientists ORDER BY death DESC");
            else
                query.exec("SELECT * FROM scientists ORDER BY death ASC");
        }
        else
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM scientists ORDER BY id DESC");
            else
                query.exec("SELECT * FROM scientists ORDER BY id ASC");
        }

        // Creates a scientist from the values and inserts the scientist to a vector
        while(query.next())
        {
            cout << "*" << endl;
            id = query.value("ID").toUInt();
            name = query.value("name").toString().toStdString();
            sex = query.value("sex").toString().toStdString();
            birth = query.value("birth").toUInt();
            death = query.value("death").toUInt();
            about = query.value("About").toString().toStdString();

            Scientist sci(name, sex[0], birth, death, about, id);
            allScientists.push_back(sci);
        }
    }

    return allScientists;
}

vector<Computer> DataManager::getAllComputers(SortOrder sort)
{
   vector<Computer> allComputers;

   if(db.open())
    {
        string name;
        int buildYear;
        string type;
        bool wasItBuilt;
        string about;
        int id;

        QSqlQuery query(db);

        // Otputs the list as the user wants it sorted
        if(sort.sortBy == NAME)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM computers ORDER BY name DESC");
            else
                query.exec("SELECT * FROM computers ORDER BY name ASC");
        }
        else if(sort.sortBy == SEX)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM computers ORDER BY sex DESC");
            else
                query.exec("SELECT * FROM computers ORDER BY sex ASC");
        }
        else if(sort.sortBy == BIRTH)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM computers ORDER BY birth DESC");
            else
                query.exec("SELECT * FROM computers ORDER BY birth ASC");
        }
        else if(sort.sortBy == DEATH)
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM computers ORDER BY death DESC");
            else
                query.exec("SELECT * FROM computers ORDER BY death ASC");
        }
        else
        {
            if(sort.direction == DESCENDING)
                query.exec("SELECT * FROM computers ORDER BY id DESC");
            else
                query.exec("SELECT * FROM computers ORDER BY id ASC");
        }

        // Creates a computer from the values and inserts the scientist to a vector
        while(query.next())
        {
            id = query.value("ID").toUInt();
            name = query.value("name").toString().toStdString();
            buildYear = query.value("buildyear").toUInt();
            type = query.value("type").toString().toStdString();
            wasItBuilt = query.value("wasbuilt").toUInt();
            about = query.value("about").toString().toStdString();

            Computer comp(name, buildYear, type, wasItBuilt, about, id);
            allComputers.push_back(comp);
        }

        return allComputers;
    }
}

vector<Scientist> DataManager::findScientistByName(string subString, SortOrder sort)
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

vector<Computer> DataManager::findComputerByName(string subString, SortOrder sort)
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

vector<Scientist> DataManager::findByBirthYear(int yearFrom, int yearTo, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's birth year matches year parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(allScientists[i].getBirthYear() > yearFrom && allScientists[i].getBirthYear() < yearTo)
        {
            matchingScientists.push_back(allScientists[i]);
        }
    }

    return matchingScientists;
}

vector<Scientist> DataManager::findByDeathYear(int yearFrom, int yearTo, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's death year matches year parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(allScientists[i].getDeathYear() > yearFrom && allScientists[i].getDeathYear() < yearTo)
        {
            matchingScientists.push_back(allScientists[i]);
        }
    }

    return matchingScientists;
}

vector<Scientist> DataManager::findBySex(string sex, SortOrder sort)
{
    vector<Scientist> allScientists = getAllScientists(sort);
    vector<Scientist> matchingScientists;

    //Checks all scientists and inserts the ones who's sex matches sex parameter into the vector matchingScientists
    for(unsigned int i = 0; i < allScientists.size(); i++)
    {
        if(allScientists[i].getSex() == sex[0])
        {
            matchingScientists.push_back(allScientists[i]);
        }
    }
    return matchingScientists;
}

/*!
 * \brief DataManager::getage Calculates age of scientist.
 * \param oneScientist
 * \returns the age of the given scientist
 */
int DataManager::getage(Scientist oneScientist){

    if(oneScientist.getDeathYear() == 0){
        return 2015 - oneScientist.getBirthYear();
    }

   return oneScientist.getDeathYear() - oneScientist.getBirthYear();
}



struct sortByName
{
    /*inline*/ bool operator() (const Scientist& name1, const Scientist& name2)
    {
        return (name1.getName() < name2.getName());
    }
};

struct sortByBirth
{
    /*inline*/ bool operator() (const Scientist& birth1, const Scientist& birth2)
    {
        return (birth1.getBirthYear() < birth2.getBirthYear());
    }
};

struct sortByDeath
{
    /*inline*/ bool operator() (const Scientist& death1, const Scientist& death2)
    {
        return (death1.getDeathYear() < death2.getDeathYear());
    }
};


struct sortBySex
{
    /*inline */ bool operator() (const Scientist& sex1, const Scientist& sex2)
    {
        return (sex1.getSex() < sex2.getSex());
    }
};


// This function gets an input from the user and sorts it.
vector<Scientist> DataManager::sortBy(vector<Scientist> scientists, SortOrder sortOrder )
{
    switch(sortOrder.sortBy)
    {
        case NONE:
            return scientists;

        // Sorts names in alphabetical order.
        case NAME:
            sort(scientists.begin(), scientists.end(), sortByName());
            break;

        // Sorts birthyear "lowest to highest".
        case BIRTH:
            sort(scientists.begin(), scientists.end(), sortByBirth());
            break;

        // Sorts deathyear "lowest to highest".
        case DEATH:
            sort(scientists.begin(), scientists.end(), sortByDeath());
            break;

        // Sorts gender.
        case SEX:
            sort(scientists.begin(), scientists.end(), sortBySex());
            break;

        default:
            return scientists;

    }
    // Reverses the elements in the Scientists vector.
    if(sortOrder.direction == DESCENDING){
        reverse (scientists.begin(), scientists.end());
    }
    return scientists;
}

void DataManager::writeNewScientistVectorToFile(vector<Scientist> scientists)
{
    CSVWriter csvW(fileName);
    csvW.clear();
    for (size_t i = 0; i < scientists.size(); i++)
    {
        csvW.add(scientistToVector(scientists[i]));
    }
}
