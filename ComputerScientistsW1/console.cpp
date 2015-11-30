#include "Console.h"
#include <iostream>
#include <SortBy.h>
#include <string>
#include "DataManager.h"

using namespace std;

Console::Console(DataManager* dataManage)
{
    this->dataMan = dataManage;
}

Console::~Console()
{

}

void Console::run()
{
    cout << "\n-----------------------------------"
            "\nWelcome to the Computer Scientists database. Enter a number"
            "\n1: Edit database"
            "\n2: See database"
            "\nAnything else will quit the program\n:";

    int select = 0;
    cin >> select;

    switch (select) {

    case 1:
        //TODO
        editDatabase();
        return;

    case 2:
        showScientists();
        return;

    default:
        cout << "Error, bad input, quitting\n";
        return;
    }
}
void Console::editDatabase()
{
    cout << "\n-----------------------------------"
            "\n1: Add to the database"
            "\n2: Edit an entry in the database"
            "\n3: Delete an entry in the database\n:";

    int select = 0;
    cin >> select;

    switch (select) {
    case 1:
        //TODO
        insertScientist();
        return;

    case 2:
        //TODO EDIT
        return;

    case 3:
        //TODO DELETE
        return;
    default:
        cout << "Error, bad input, quitting\n";
        return;
    }
}

void Console::insertScientist()
{
    cout << "\n-----------------------------------"
            "\nPlease fill inn all the information about the scientist"
            "\nFull name:";

    string name, sex;
    int birthYear, deathYear;

    cin.ignore(); // make sure there is nothing in the buffer
    getline(cin, name);
    cout << "Sex (M/F):";
    getline(cin, sex);
    cout << "Year of birth:";
    cin >> birthYear;
    cout << "Year of death(0 if still alive):";
    cin >> deathYear;

    cout << "\n-----------------------------------" << endl
         << "Is this correct?:" << endl
         << name << endl
         << sex << endl
         << birthYear << endl
         << deathYear << endl;

    this->dataMan->addScientist(Scientist(name, sex[0], birthYear, deathYear));
}

void Console::showScientists()
{
    vector<Scientist> scientists = getScientist();
    if (scientists.size() == 0) { cout << "No Scientist found"; }

    for(size_t i = 0; i < scientists.size(); i++)
    {
        // print each Scientist
        // TODO
        Scientist currentScientist = scientists[i];
        cout << currentScientist.getName();
    }
}

vector<Scientist> Console::getScientist()
{
    int select = 0;

    cout << endl
         << "-----------------------------------" << endl << endl
         << "1: Show a list of them all" << endl
         << "2: Search by a string or substring" << endl
         << "3: Search by year" << endl
         << "4: Search by sex" << endl
         << "Anything else will quit the program" << endl
         << ":";

    cin >> select;

    if (select == 0) { return vector<Scientist>(); }

    SortBy sortBy = getSort();
    Direction direction = ASCENDING;

    if (sortBy != NONE) { direction = getDirection(); }

    switch (select) {

    case 1:
        return dataMan->getAllScientists (sortBy, direction);

    case 2:
        return dataMan->findByName ("string", sortBy, direction);

    case 3:
        return dataMan->findByBirthYear("String", sortBy, direction);

    case 4:
        return vector<Scientist>();

    default:
        cout << "Error, bad input, quitting" << endl;
        return vector<Scientist>();
    }
}

SortBy Console::getSort()
{
    int choice;

    cout << endl
         << "-----------------------------------" << endl
         << "How do you want your list sorted?" << endl
         << "1: No sorting" << endl
         << "2: Sort by name" << endl
         << "3: Sort by year of birth" << endl
         << "4: Sort by year of death" << endl
         << "5: Sort by sex" << endl
         << ":";

    cin >> choice;

    switch ( choice )
    {
    case 1:
        return NONE;

    case 2:
        return NAME;

    case 3:
        return BIRTH;

    case 4:
        return DEATH;

    case 5:
        return SEX;

    default:
        cout << endl << "Error, bad input, No sorting used\n\n";
        return NONE;
    }
}

Direction Console::getDirection(){
    int choice;

    cout << "\n-----------------------------------"
            "\nAscending or descending?\n"
            "1: Ascending\n"
            "2: Descending?\n:";

    cin >> choice;

    switch ( choice )
    {
    case 1:
        return ASCENDING;

    case 2:
        return DESCENDING;

    default:
        cout<<"\nError, bad input, ascending used\n\n";
        return ASCENDING;
    }
}
