#include "Console.h"
#include <iostream>
#include <iomanip>
#include <SortBy.h>
#include <qstring.h>
#include "DataManager.h"
#include <locale>
#include <sstream>

using namespace std;

// constructor
Console::Console(DataManager* dataManage)
{
    this->dataMan = dataManage;
}

// de-constructor
Console::~Console(){}

/*!
 * \brief Console::run
 * Runs the console version of the app
 */
void Console::run()
{
    string menu = "-------------------------------------------------------------"
                  "\nWelcome to the Computer Scientists database. Enter a number\n"
                  "-------------------------------------------------------------"

                  "\n1: Edit database"
                  "\n2: See database"
                  "\n3: Quit";
    while(true)
    {
        clearScreen();
        int select = getInt(menu);

        switch (select) {

        case 1:
            //TODO
            editDatabase();
            break;

        case 2:
            showScientists();
            break;

        case 3:
            return; // quit

        default:
            break;
        }
    }
}

/*!
 * \brief Console::editDatabase
 * for editing entries in datafile
 *
 */
void Console::editDatabase()
{
    clearScreen();
    cout << "-------------------------------------------------------------"
            "\nEdit the Database\n"
            "-------------------------------------------------------------"
            "\n1: Add to the database"
            "\n2: Edit an entry in the database"
            "\n3: Delete an entry in the database"
            "\n other numbers: Go back to the start";

    int select = getInt("");

    switch (select) {
    case 1:
        do
        {
            clearScreen();
            insertScientist();
        }while(promptAgain("Do you want to add another computer scientist? Y/N"));

        return;

    case 2:
        do
        {
            clearScreen();
            editScientist();
        }while(promptAgain("Do you want to edit another computer scientist? Y/N"));
        return;

    case 3:
        //TODO DELETE
        return;
    default:
        cout << "1-3 not selected, going back\n";
        return;
    }
}

/*!
 * \brief Console::insertScientist
 * for inserting into the datafile
 */
void Console::insertScientist()
{
    cout << "-------------------------------------------------------------"
            "\nPlease fill inn all the information about the scientist\n"
            "-------------------------------------------------------------";

    string info = "";
    string name = "";
    char sex = ' ';
    int birthYear = 0;
    int deathYear = 0;
    string about = "";

    do   //So the user can modify before he finishes
    {
        name = promptName();
        sex = promptSex();
        birthYear = promptBirthYear();
        deathYear = promptDeathYear(birthYear);
        about = promptAbout();

        clearScreen();
        info = "-------------------------------------------------------------"
               "\nScientist information:\n"
               "-------------------------------------------------------------"
               "\nName: " + name +
               "\nSex: " + sex +
               "\nYear of birth: " + to_string(birthYear) +
               "\nYear of death: " + to_string(deathYear) +
               "\nAbout: " + about +
               "\nIs this correct? Y/N";

    }while(!promptAgain(info));


    this->dataMan->addScientist(Scientist(name, sex, birthYear, deathYear, about, 0));
}

void Console::editScientist()
{
    string info = "";
    SortOrder sort;
    sort.sortBy = NONE;
    sort.direction = ASCENDING;

    cout << "-------------------------------------------------------------"
            "\nPlease enter the full name of the scientist you want to edit";
    string name = promptName();
    vector<Scientist> allScientists = dataMan->findByName(name, sort);

    if(allScientists.size() > 1)
    {
        cout << "-------------------------------------------------------------"
                "\nMatching scientists:\n";

        cout << setw(5) << left << "ID"
             << setw(5) << left << "Age"
             << setw(5) << left << "Sex"
             << setw(20) << left << "Name"
             << setw(50) << left << "About"<< endl;
        for(size_t i = 0; i < allScientists.size(); i++)
        {
            // print each Scientistn

            cout << setw(5) << left << allScientists[i].getID()
                 << setw(5) << left << allScientists[i].getAge()
                 << setw(5) << left << allScientists[i].getSex()
                 << setw(20) << left << allScientists[i].getName()
                 << setw(50) << left << allScientists[i].getAbout()
                 << endl;
        }

        cout << "-------------------------------------------------------------"
                "\nInsert the ID of the scientist you want to edit: ";
        int id = getInt("");

        changeScientist(dataMan->getAllScientists(sort)[id]);
    }
    else if(allScientists.size() == 0)
    {
        cout << "\nSorry, there is no matching scientist in datafile\n";
    }
    else
    {
        changeScientist(allScientists[0]);
    }
}

void Console::changeScientist(Scientist& scientis)
{
    clearScreen();

    string info;

    do{
        cout << "-------------------------------------------------------------"
                "\nWhat would you like to change about " + scientis.getName() + "?"
                "\n1: Name"
                "\n2: Sex"
                "\n3: Year of birth"
                "\n4: Year of death"
                "\n5: About";

        int select = getInt("");

        switch(select){ //User chooses which attribute to edit
        case 1:
        {
            scientis.setName(promptName());
            return;
        }
        case 2:
        {
            scientis.setSex(promptSex());
            return;
        }
        case 3:
        {
            scientis.setBirthYear(promptBirthYear());
            return;
        }
        case 4:
        {
            scientis.setDeathYear(promptDeathYear(scientis.getBirthYear()));
            return;
        }
        case 5:
        {
            scientis.setAbout(promptAbout());
            return;
        }
        default:
        {
            cout << "1-3 not selected, going back\n";
            return;
        }
        }

        //Show the user the modified scientist
        clearScreen();
                info = "-------------------------------------------------------------"
                      "\n" + scientis.getName() + "'s information is now: "
                      "\nName: " + scientis.getName() +
                      "\nSex: " + scientis.getSex() +
                      "\nYear of birth: " + to_string(scientis.getBirthYear()) +
                      "\nYear of death: " + to_string(scientis.getDeathYear()) +
                      "\nAbout: " + scientis.getAbout();
    }while(!promptAgain(info));
}

/*!
 * \brief Console::promptName
 * \return name
 */
string Console::promptName()
{
    string name = "";
    do
    {
        cout << "\nName: ";
        getline(cin, name);
    } while (!isNameValid(name));
    return name;
}
string Console::promptAbout()
{
    string about = "";
    do
    {
        cout << "\nAbout: ";
        getline(cin, about);
    } while (!isAboutValid(about));
    return about;
}
/*!
 * \brief Console::promptSex
 * \return sex
 */
char Console::promptSex()
{
    string sex = "";
    while(true)
    {
        cout << "Sex (M/F): ";
        getline(cin, sex);

        //Makes sure that sex is upper-case
        sex[0] = toupper(sex[0]);

        //Only allows M and F
        if(sex[0] == 'M' || sex[0] == 'F') { return sex[0]; }
        else { cout << "Please enter a valid sex.\n"; }
    }
}

/*!
 * \brief Console::promptBirthYear
 * \return birthYear
 */
int Console::promptBirthYear()
{
    int birthYear = 0;
    while(true)
    {
        cout << "Year of birth: ";
        birthYear = getInt("");

        //Only allows birthyear to be greater than or equals to 1200 and less than 2016
        if(birthYear >= 1200 && birthYear <= 2015) { return birthYear; }

        // we dont get here if the year was valid
        cout << "Please enter a valid birth year.(1200-2015)\n";
    }
}

/*!
 * \brief Console::promptDeathYear
 * \param birthYear
 * \return deathYear
 */
int Console::promptDeathYear(int birthYear)
{
    int deathYear = 0;
    while(true)
    {
        cout << "Year of death (0 if still alive):";
        deathYear = getInt("");

        // Only allows deathyear to be 0 or greater than birthyear and less than 2016
        // the scientist can not be older than 110
        if    ((deathYear == 0 && 2015 - birthYear <= 110)
           || ((deathYear > birthYear && deathYear <= 2015)
           &&  (deathYear - birthYear <= 110)))
        {
            return deathYear;
        }

        // we dont get here if the year was valid
        cout << "Please enter a valid birth year. The scientist can not be older than 110 years and can not have died before being born\n";
    }
}

/*!
 * \brief Console::showScientists
 * prints out scientists in sorted order
 */
void Console::showScientists()
{

    vector<Scientist> scientists = getScientist();
    if (scientists.size() == 0) { cout << "No Scientist found" << flush; return; }

    clearScreen();
    cout << "-------------------------------------------------------------" << endl
         << setw(5) << left << "ID"
         << setw(5) << left << "Age"
         << setw(5) << left << "Sex"
         << setw(30) << left << "Name"
         << setw(50) << left << "About"<< endl
         << "-------------------------------------------------------------" << endl;
    for(size_t i = 0; i < scientists.size(); i++)
    {
        // print each Scientistn

        cout << setw(5) << left << scientists[i].getID()
             << setw(5) << left << scientists[i].getAge()
             << setw(5) << left << scientists[i].getSex()
             << setw(30) << left << scientists[i].getName()
             << setw(50) << left << scientists[i].getAbout()
             << endl;
    }
    string continues;
    getline(cin,continues);
}

/*!
 * \brief Console::getScientist
 * \return Scientist
 */
vector<Scientist> Console::getScientist()
{
    clearScreen();

    int select = 0;
    cout << "-------------------------------------------------------------" << endl
         << "Look inside the database" << endl
         << "-------------------------------------------------------------" << endl
         << "1: Show a list of them all" << endl
         << "2: Search by a string or substring" << endl
         << "3: Search by birth year" << endl
         << "4: Search by death year" << endl
         << "5: Search by sex" << endl
         << "Other numbers will go back";

    select = getInt("");

    if (select == 0) { return vector<Scientist>(); }

//    SortOrder sort = getSort();
//    Direction direction = ASCENDING;
//    if (sort != NONE) { direction = getDirection(); }

    string name = "";
    string sex = "";
    int birthYear = 0;
    int deathYear = 0;

    switch (select) {

    case 1:
        return dataMan->getAllScientists (getSort());

    case 2:
        name = promptName();
        return dataMan->findByName (name, getSort());

    case 3:
        birthYear = getInt("Enter birth year");
        return dataMan->findByBirthYear(birthYear, getSort());

    case 4:
        deathYear = getInt("Enter death year");
        return dataMan->findByDeathYear(deathYear, getSort());

    case 5:
        sex = promptSex();
        return dataMan->findBySex(sex, getSort());

    default:
        cout << "Searching for no one" << endl;
        return vector<Scientist>();
    }
}

/*!
 * \brief Console::getSort
 * \return SortOrder
 */
SortOrder Console::getSort()
{
    int choice;
    SortOrder sort;

    clearScreen();
    cout << "-------------------------------------------------------------" << endl
         << "How do you want your list sorted?" << endl
         << "-------------------------------------------------------------" << endl
         << "1: No sorting" << endl
         << "2: Sort by name" << endl
         << "3: Sort by year of birth" << endl
         << "4: Sort by year of death" << endl
         << "5: Sort by sex";

    choice = getInt("");

    switch ( choice )
    {
    case 1:
        sort.sortBy = NONE;
        sort.direction = ASCENDING;
        return sort;

    case 2:
        sort.sortBy = NAME;
        break;

    case 3:
        sort.sortBy = BIRTH;
        break;

    case 4:
        sort.sortBy = DEATH;
        break;

    case 5:
        sort.sortBy = SEX;
        break;

    default:
        cout << endl << "Error, bad input, No sorting used\n\n";
        sort.sortBy = NONE;
        sort.direction = ASCENDING;
        return sort;
    }

    sort.direction = getDirection();
    return sort;
}

/*!
 * \brief Console::getDirection
 * \return
 */
Direction Console::getDirection(){
    int choice;

    cout << "\n-------------------------------------------------------------"
            "\nAscending or descending?\n"
            "1: Ascending\n"
            "2: Descending?";

    choice = getInt("");

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

/*!
 * \brief Console::isNameValid
 * Checks for user intent, all names are allowed, but weird characters are checked
 * and the user gets prompted on if the name should contain that character
 * \param Takse in a name to check
 * \return True if name is normal or if the user intends to use special characters
 */
bool Console::isNameValid(string name)
{
    // QStrings alow us to use UTF8 encoding and comparison
    QString listOfBadCharacters = QString::fromUtf8(".;:¡@¢‰^{[]}–<>!\"#$%&/()=?_*~");
    QString unicodeName = QString::fromUtf8(name.c_str());

    // CSV uses commas to seperate values, we simply dont allow commas to follow that rule
    for(size_t i = 0; i < name.length(); i++)
    {
        if (name[i] == ',')
        {
            cout << "\nCommas in names are not allowed";
            return false;
        }
    }

    // Numbers are allowed, but user is prompted
    for(size_t i = 0; i < name.length(); i++)
    {
        if (isdigit(name[i]))
        {
            if(!promptAgain("Did you mean to leave a number in the name? Y/N")){ return false; }
            else { break; }
        }

    }

    // Special characters are allowed, but user is prompted
    for(int i = 0; i < listOfBadCharacters.length(); i++)
    {
        for(int j = 0; j < unicodeName.length(); j++)
        {
            if (unicodeName.contains( listOfBadCharacters.midRef(i, 1)))
            {
                cout << "Did you mean to leave a \'" << listOfBadCharacters.midRef(i, 1).toUtf8().constData() << "\' in the name? Y/N";
                if(!promptAgain("")){ return false; }
                else { i++; }
            }
        }

    }
    return true;
}
bool Console::isAboutValid(string about)
{
    //DOTO
    return true;
}
/*!
 * \brief Console::prompt
 * For use in Yes / No prompts
 * \returns a true if user types y and false if user types in n,
 * loops until it gets either.
 */
bool Console::promptAgain(string prompt){
    while(true){
        cout << prompt << endl << ":";
        string answer = "";
        cin.clear();
        getline(cin, answer);
        if (answer[0] == 'n' || answer[0] == 'N') { return false; }
        else if (answer[0] == 'y' || answer[0] == 'Y') { return true; }
        else { cout << "Invalid input, try again:"; }
        cout << answer;
    }
}

/*!
 * \brief Console::getInt
 * Some code taken from http://www.cplusplus.com/forum/articles/6046/
 * \param prompt
 * \return myNumber
 */
int Console::getInt(string prompt){
    string input = "";
    int myNumber = 0;
    while (true) {
        cout << prompt << endl << ":";
        getline(cin, input);

        // This code converts from string to number safely.
        stringstream myStream(input);
        if (myStream >> myNumber) { break; }
        cout << "Invalid number, please try again" << endl;
    }
    return myNumber;
}

/*!
 * \brief Console::clearScreen
 * Dirty way of making the console look nicer when running
 */
void Console::clearScreen(){
    system("CLS");
    system("clear");
}
