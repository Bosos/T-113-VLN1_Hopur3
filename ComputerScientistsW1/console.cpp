#include "Console.h"
#include <iostream>
#include <iomanip>
#include <SortBy.h>
#include <qstring.h>
#include "DataManager.h"
#include <locale>
#include <sstream>

using namespace std;

const string DASHES = "==========================================================================";

// constructor
Console::Console(DataManager* dataManage)
{
    this->dataMan = dataManage;
    welcomeShown = false;
}

// destructor
Console::~Console(){}

/*!
 * \brief Console::welcome()
 * Displays very cool WELCOME letters
 */
void Console::welcome()
{
    if (welcomeShown) { return; }
    cout << "__        __   _                         "
           "\n\\ \\      / /__| | ___ ___  _ __ ___   ___ "
           "\n \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\"
           "\n  \\ V  V /  __/ | (_| (_) | | | | | |  __/"
           "\n   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|\n";
    welcomeShown = true;
}

/*!
 * \brief Console::run
 * Runs the console version of the app
 */
void Console::run()
{
    while(true)
    {
        clearScreen();

        // welcome is only shown once
        welcome();
        cout << frameText("Welcome to the Computer Scientists database. Enter a number")
             << "1: Edit database" << endl
             << "2: See database" << endl
             << "3: Quit" << endl << DASHES << endl;

        //stores the user's choice
        int select = getInt("");

        //Calls appropriate function based on the user's choice
        switch (select) {
        case 1:
            editDatabase();
            break;

        case 2:
            seeDatabase();
            break;

        case 3:
            // quit
            return;

        default:
            // Repeat while loop
            cout << "The number should be between 1 and 3";
            break;
        }
    }
}

/*!
 * \brief Console::seeDatabase
 * Gives the option on what the user want to see
 */
void Console::seeDatabase()
{
    while(true)
    {
        clearScreen();

        cout << frameText("What do you want to see?")
             << "1: Scientists" << endl
             << "2: Computers" << endl
             << "3: List of what computers a scientist used" << endl
             << "4: list of scientist that used a computer" << endl << DASHES << endl;
                //TODO more to see

        //stores the user's choice
        int select = getInt("");

        //Calls appropriate function based on the user's choice
        switch (select)
        {
        case 1:
            showScientists();
            return;

        case 2:
            showComputers();
            return;

        case 3:
            showWhatComputersAScientistUsed();
            return;

        case 4:
            showWhatScientistsUsedAComputer();
            return;

        default:
            return;
        }
    }
}

/*!
 * \brief Console::showWhatComputersAScientistUsed
 * Prints out computers that were used by a selected scientist
 */
void Console::showWhatComputersAScientistUsed()
{
    int id = promptFindScientist();
    vector<Computer> scientistComputers = dataMan->getComputersFromScientistId(id);
    Scientist curScientist = dataMan->getScientistFromId(id);

    clearScreen();

    displayScientists(vector<Scientist>{curScientist});
    if (scientistComputers.size() == 0)
    {
        cout << endl
             << "This scientist has either not used any of the computers in this database or the" << endl
             << "relation has not yet been made. Select 1 at the main menu to edit the database" << endl;
    }
    else
    {
        cout << endl << "Used these computers" << endl;
        displayComputers(scientistComputers);
    }
    promptEnterToContinue();
}

/*!
 * \brief Console::showWhatScientistsUsedAComputer
 * Prints out scientists that used a selected computer
 */
void Console::showWhatScientistsUsedAComputer()
{
    int id = promptFindComputer();
    vector<Scientist> usersOfComputer = dataMan->getScientistsFromComputerId(id);
    Computer curComputer = dataMan->getComputerFromId(id);

    clearScreen();

    displayComputers(vector<Computer>{curComputer});
    if (usersOfComputer.size() == 0)
    {
        cout << endl << "No record of Users of this computer in the database, add them with the edit functions" << endl;
    }
    else
    {
        cout << endl << "Was used by:" << endl;
        displayScientists(usersOfComputer);
    }
    promptEnterToContinue();
}

/*!
 * \brief Console::showComputers
 * Prints out computers in sorted order
 */
void Console::showComputers()
{
    //Creates a vector containing all computers in currently database
    vector<Computer> computers = getComputer();

    if (computers.size() == 0)
    {
        cout << "No No computer found";
    }

    //Prints out the computers currently in database
    else
    {
        clearScreen();
        displayComputers(computers);
    }

    // Wait for user input so the results can stay on screen
    promptEnterToContinue();
}

/*!
 * \brief Console::editDatabase
 * Runs the editing part of the program
 */
void Console::editDatabase()
{
    clearScreen();

    cout << frameText("Edit the Database")
         << "1: Add a scientist to the database" << endl
         << "2: Add a computer to the database" << endl
         << "3: Add a scientist - computer relation" << endl
         << "4: Edit a scientist in the database" << endl
         << "5: Edit a computer in the database" << endl
         << "6: Delete a scientist from the database" << endl
         << "7: Delete a computer from the database" << endl
         << "Other numbers: Go back to the start" << endl << DASHES << endl;

    //Stores the user's choice
    int select = getInt("");

    //Calls appropriate functions based on the user's choice
    switch (select)
    {
    case 1:
        do
        {
            clearScreen();
            insertScientist();
        }while(promptYesNo("Do you want to add another computer scientist? Y/N"));

        return;
    case 2:
        do
        {
            clearScreen();
            insertComputer();
        }while(promptYesNo("Do you want to add another computer? Y/N"));
        return;
    case 3:
        do
        {
            clearScreen();
            findSciAndComToMakeUser();
        }while(promptYesNo("Do you want to add another scientist - computer relation? Y/N"));

        return;

    case 4:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the scientist you want to edit");
            findScientistToEdit();
        }while(promptYesNo("Do you want to edit another scientist? Y/N"));
        return;

    case 5:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the computer you want to edit");
            findComputerToEdit();
        }while(promptYesNo("Do you want to edit another computer? Y/N"));
        return;

    case 6:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the scientist you want to delete");
            findScientistToDelete();
        }while(promptYesNo("Do you want to delete another computer scientist? Y/N"));
        return;
    case 7:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the computer you want to delete");
            findComputerToDelete();
        }while(promptYesNo("Do you want to delete another computer? Y/N"));
    default:
        return;
    }
}

/*!
 * \brief Console::insertComputer
 * Makes a new computer and adds it to the database
 */
void Console::insertComputer()
{
    cout << frameText("Please fill inn all the information about the computer");

    //creating variables
    string info = "";
    string name = "";
    int buildYear = 0;
    int type = 0;
    string about = "";
    bool wasItBuilt = false;
    string ans = "No";

    // The user can modify more than one field before he finishes
    do
    {
        //inserting information about the new computer into the parameters
        name = promptName();
        buildYear = promptComputerMakeYear();
        type = promptType();
        about = promptAbout();
        wasItBuilt = promptYesNo("Was the computer built? Y/N");

        if(wasItBuilt) {ans = "Yes";}

        clearScreen();
        info = frameText("Computer information:") +
               "Name: " + name +
               "\ntype: " + dataMan->getTypeOfComputerFromId(type) +
               "\nYear built: " + to_string(buildYear) +
               "\nWas it built? " + ans +
               "\nAbout: " + about +
               "\nIs this correct? Y/N";

    }while(!promptYesNo(info));

    // adds the new computer to the database
    this->dataMan->addComputer(Computer(name, buildYear, type, wasItBuilt, about, 0));
}

/*!
 * \brief Console::showScientists
 * Prints out scientists in sorted order
 */
void Console::showScientists()
{
    //Creates a vector containing all scientists in currently database
    vector<Scientist> scientists = getScientist();


    if (scientists.size() == 0) { cout << "No Scientist found" << endl; }

    //Prints out the scientists currently in database
    else
    {
        clearScreen();
        displayScientists(scientists);
    }

    // Wait for user input so the results can stay on screen
    promptEnterToContinue();
}

/*!
 * \brief Console::insertScientist
 * For inserting into the datafile
 */
void Console::insertScientist()
{

    cout << frameText("Please fill inn all the information about the scientist");

    //creating variables
    string info = "";
    string name = "";
    char sex = ' ';
    int birthYear = 0;
    int deathYear = 0;
    string about = "";

    // The user can modify more than one field before he finishes
    do
    {
        //inserting information about the new scientist into the parameters
        name = promptName();
        sex = promptSex();
        birthYear = promptBirthYear();
        deathYear = promptDeathYear(birthYear);
        about = promptAbout();

        clearScreen();
        info = frameText("Scientist information:") +
               "Name: " + name +
               "\nSex: " + sex +
               "\nYear of birth: " + to_string(birthYear) +
               "\nYear of death: " + to_string(deathYear) +
               "\nAbout: " + about +
               "\nIs this correct? Y/N ";

    }while(!promptYesNo(info));

    //adds the new scientist to the database
    this->dataMan->addScientist(Scientist(name, sex, birthYear, deathYear, about, 0));
}

/*!
 * \brief Console::promptFindScientist
 * Finds out if there are more or less then 1 scientist,
 * if there are more then 1 scientist then it displays them
 * if there is no scientist, it says that
 * and if there is only 1 scientist it returns that scientist's ID
 */
int Console::promptFindScientist()
{
    cout << "Press enter to get a list of all scientists, substrings are accepted, search is not case sensitive" << endl;
    string name = promptName();

    //finds all the scientists whos names match the user input and inserts them to a vector of scientists
    vector<Scientist> allScientists = dataMan->findScientistByName(name, ScientistSortOrder());

    //If there are more than 1 scientists that match the user input,
    //the program shows all of them to the user and then
    //the user chooses the id of the scientist he want's to edit
    if(allScientists.size() > 1)
    {
        clearScreen();
        displayScientists(allScientists);

        cout <<"Matching scientists, insert the ID of the scientist you want to select";

        // ask user to select and return the selected id
        return getInt("");
    }

    //if there are no matching scientists
    else if(allScientists.size() == 0)
    {
        cout << "\nSorry, there is no matching scientist in database\n";
        return 0;
    }

    //return the only scientist, if there is only one scientist who's name matches the input
    else
    {
        return allScientists.at(0).getID();
    }
}

/*!
 * \brief Console::promptFindComputer
 * Finds out if there are more or less then 1 computer,
 * if there are more then 1 computer then it displays them
 * if there is no computer, it says that
 * and if there is only 1 computer it returns that computer's ID
 */
int Console::promptFindComputer()
{
    cout << "Press enter to get a list of all computers, substrings are accepted, \nsearch is not case sensitive" << endl;
    string name = promptName();

    //finds all the scientists whos names match the user input and inserts them to a vector of scientists
    vector<Computer> allComputers = dataMan->findComputerByName(name, ComputerSortOrder());

    //If there are more than 1 scientists that match the user input,
    //the program shows all of them to the user and then
    //the user chooses the id of the scientist he want's to edit
    if(allComputers.size() > 1)
    {
        clearScreen();
        displayComputers(allComputers);

        cout <<"Matching computers, insert the ID of the computer you want to select";

        // ask user to select and return the selected id
        return getInt("");
    }

    //if there are no matching computers
    else if(allComputers.size() == 0)
    {
        cout << "\nSorry, there is no matching computer in database\n";
        return 0;
    }

    //return the only computer, if there is only one computer who's name matches the input
    else
    {
        return allComputers.at(0).getID();
    }
}

/*!
 * \brief Console::findScientistToEdit
 * Asks for user input in the search of a scientists with mathcing names
 * will find substings but is case sensitive
 */
void Console::findScientistToEdit()
{
    int id = promptFindScientist();

    // if no id was found
    if (!id) { return; }

    //edits the scientist who's ID matches id
    changeScientist(dataMan->getScientistFromId(id));
}

/*!
 * \brief Console::findScientistToDelete
 * Finds the scientist the user wants to delete
 */
void Console::findScientistToDelete()
{
    int id = promptFindScientist();

    // if no id was found
    if (!id) { return; }

    //deletes the scientist who's ID matches id
    deleteScientist(dataMan->getScientistFromId(id));
}

/*!
 * \brief Console::findComputerToDelete
 * Finds the computer the user wants to delete
 */
void Console::findComputerToDelete()
{
    int id = promptFindComputer();

    // if no id was found
    if (!id)
    {
        return;
    }

    //deletes the scientist who's ID matches id
    deleteComputer(dataMan->getComputerFromId(id));
}

/*!
 * \brief Console::findScientistToEdit
 * Asks for user input in the search of a scientists and computers with mathcing names
 * will find substings but is case sensitive
 */
void Console::findSciAndComToMakeUser()
{
    cout << frameText("Find the computers a scientist used/theorized");
    int sciId = promptFindScientist();
    int comId = promptFindComputer();

    // if no id was found on either
    if (!sciId || !comId)
    {
        return;
    }

    //edits the scientist who's ID matches id
    dataMan->addUser(sciId, comId);
}

/*!
 * \brief Console::changeScientist
 * \param scientis
 * \param id
 * Performs the edit on a scientist in parameter scientists that has an ID matching id
 */
void Console::changeScientist(Scientist scientis)
{
    clearScreen();

    string info;

    do{
        cout << frameText("What would you like to change about " + scientis.getName() + "?")
             << "1: Name" << endl
             << "2: Sex" << endl
             << "3: Year of birth" << endl
             << "4: Year of death" << endl
             << "5: About" << endl << DASHES << endl;

        int select = getInt("");

        switch(select){ //User chooses which attribute to edit
        case 1:
            //sets the chosen scientists name to user's input
            scientis.setName(promptName());
            break;

        case 2:
            //sets the chosen scientists sex to user's input
            scientis.setSex(promptSex());
            break;

        case 3:
            //sets the chosen scientists birth year to user's input
            scientis.setBirthYear(promptBirthYear());
            break;

        case 4:
            //sets the chosen scientists death year to user's input
            scientis.setDeathYear(promptDeathYear(scientis.getBirthYear()));
            break;

        case 5:
            //sets the chosen scientist's about to user's input
            scientis.setAbout(promptAbout());
            break;

        default:
            cout << "1-5 not selected, going back\n";
            return;
        }

        //Show the user the modified scientist
        clearScreen();
                info = frameText(scientis.getName() + "'s information is now:") +
                      "Name: " + scientis.getName() +
                      "\nSex: " + scientis.getSex() +
                      "\nYear of birth: " + to_string(scientis.getBirthYear()) +
                      "\nYear of death: " + to_string(scientis.getDeathYear()) +
                      "\nAbout: " + scientis.getAbout() +
                      "\n" + DASHES +
                      "\nDone editing? Y/N";

        // if yes? maybe
        //saves the modifications to database

        dataMan->updateScientist(scientis);
    }while(!promptYesNo(info));
}

/*!
 * \brief Console::deleteScientist
 * \param scientis
 * \param id
 * Deletes a scientist in scientis who's ID matches id and saves the changes
 */
void Console::deleteScientist(Scientist scientis)
{
    clearScreen();
    displayScientists(vector<Scientist>(1,scientis));


    //User has to be sure if he want's to totally eliminate this scientist
    if(promptYesNo("Sure you want to delete " + scientis.getName() + " Y/N"))
    {
        //scientist has been removed from database
        dataMan->removeFromScientist(scientis.getID());
    }
}

/*!
 * \brief Console::deleteComputer
 * \param comp
 * \param id
 * Deletes a computer in computers who's ID matches id and saves the changes
 */
void Console::deleteComputer(Computer comp)
{
    clearScreen();
    displayComputers(vector<Computer>(1,comp));


    //User has to be sure if he want's to totally eliminate this computer
    if(promptYesNo("Sure you want to delete " + comp.getName() + " Y/N"))
    {
        //computer has been removed from database
        dataMan->removeFromComputer(comp.getID());
    }
}

/*!
 * \brief Console::promptName
 * Asks the user for input
 * \returns a "name" string
 */
string Console::promptName()
{
    string name = "";

    //This loops while the name is not valid
    do
    {
        cout << "Name: ";

        //gets the user's input
        getline(cin, name);
    } while (!isNameValid(name));

    return name;
}

/*!
 * \brief Console::promptAbout
 * Asks the user for input
 * \returns an "about" string
 */
string Console::promptAbout()
{
    string about = "";
    cout << "About: ";

    //gets the user's input
    getline(cin, about);
    return about;
}
/*!
 * \brief Console::promptSex
 * Asks the user to define which sex
 * \returns sex
 */
char Console::promptSex()
{
    string sex = "";

    //this loops if sex is not either m/M or f/F
    while(true)
    {
        cout << "Sex (M/F): ";

        //gets the user's input
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
        cout << "Year of birth";
        birthYear = getInt("");

        //Only allows birthyear to be greater than or equals to 1200 and less than 2016
        if(birthYear >= 1200 && birthYear <= 2015)
        {
            return birthYear;
        }

        // we dont get here if the year was valid
        cout << "Please enter a valid birth year.(1200-2015)\n";
    }
}

/*!
 * \brief Console::promptComputerMakeYear
 * \return birthYear
 */
int Console::promptComputerMakeYear()
{
    int makeYear = 0;
    while(true)
    {
        cout << "When was the computer made/theorized";
        makeYear = getInt("");

        //Only allows birthyear to be greater than or equals to 1200 and less than 2016
        if(makeYear >= 1800 && makeYear <= 2015)
        {
            return makeYear;
        }

        // we dont get here if the year was valid
        cout << "Please enter a valid year.(1800-2015)\n";
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
        cout << "Year of death (0 if still alive)";
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
 * \brief Console::promptType
 * \return type
 */
int Console::promptType()
{
    vector<TypeOfComputer> types = dataMan->getAllTypesOfComputers();
    size_t select;

    cout << frameText("Computer type:");

    for (size_t i = 0; i < types.size(); i++)
    {
        cout << i + 1 << ": " << types.at(i).getType() << endl;
    }
    cout << types.size() + 1 << ": Add another type";

    select = getInt("");

    if (select == types.size() + 1)
    {
        makeNewTypeOfComputer();
        return select;
    }
    else if (select > 0 && select <= types.size())
    {
        return select;
    }
    else
    {
        cout << "\nPlease select a number between 1 and " << types.size() + 1 << endl;
        return promptType();
    }
}

/*!
 * \brief Console::promptWasItBuilt
 * \return true if computer was built, false otherwise
 */
bool Console::promptWasItBuilt()
{
     return promptYesNo("Was the computer built?");
}

/*!
 * \brief Console::makeNewTypeOfComputer
 * If there is a need for another type of a computer
 */
void Console::makeNewTypeOfComputer()
{
    cout << "Enter the type: " << endl;
    string type = "";
    getline(cin, type);
    dataMan->addTypeOfComputer(type);
}

/*!
 * \brief Console::getScientist
 * \return Scientist
 */
vector<Scientist> Console::getScientist()
{
    int select = 0;
    int yearStart = 0;
    int yearStop = 0;
    string sex = "";
    string name = "";

    clearScreen();
    cout << frameText("Scientist search")
         << "1: Show a list of them all" << endl
         << "2: Search by name, full or partial" << endl
         << "3: Search by birth year" << endl
         << "4: Search by death year" << endl
         << "5: Search by sex" << endl
         << DASHES << endl;

    select = getInt("");

    //Fetches a function according to the user's input
    switch (select) {

    case 1:
        return dataMan->getAllScientists (getScientistSort());

    case 2:
        name = promptName();
        return dataMan->findScientistByName (name, getScientistSort());

    case 3:// we had to pull out these "getInt" methoods because windows add mac were not fetching them in the same order
        yearStart = getInt("Enter the birth year you want to start looking from");
        yearStop = getInt("Enter the birth year you want to look until");
        return dataMan->findByBirthYear(yearStart, yearStop, getScientistSort());
    case 4:
        yearStart = getInt("Enter the death year you want to start looking from");
        yearStop = getInt("Enter the death year you want to look until");
        return dataMan->findByDeathYear(yearStart, yearStop, getScientistSort());
    case 5:
        sex = promptSex();
        return dataMan->findBySex(sex, getScientistSort());

    default:
        return vector<Scientist>();
    }
}

/*!
 * \brief Console::getComputer
 * \return Computer
 */
vector<Computer> Console::getComputer()
{
    clearScreen();
    int select = 0;
    int yearStart = 0;
    int yearStop = 0;

    cout << frameText("Computer search")
         << "1: Show a list of them all" << endl
         << "2: Search by name, full or partial  (not working yet)" << endl
         << "3: Search by the build year         (not working yet)" << endl
         << "4: Search by type of computer       (not working yet)" << endl
         << "5: Search by if it was built or not (not working yet)" << endl
         << DASHES << endl;

    select = getInt("");

    //Fetches a function according to the user's input
    switch (select)
    {
    case 1:
        return dataMan->getAllComputers (getComputerSort());
    case 2:
        return dataMan->findComputerByName (promptName(), getComputerSort());
    case 3:
        yearStart = getInt("Enter the build year you want to start looking from");
        yearStop = getInt("Enter the build year you want to look until");
        return dataMan->findComputerByBuildYear(yearStart, yearStop, getComputerSort());
    case 4:
        return dataMan->findComputerByType (promptType() ,getComputerSort());
    case 5:
        return dataMan->findComputerByWasItBuilt (promptWasItBuilt() ,getComputerSort());
    default:
        return vector<Computer>();
    }
}

/*!
 * \brief Console::getSort
 * \return ScientistSortOrder
 */
ScientistSortOrder Console::getScientistSort()
{
    int choice;
    ScientistSortOrder sort;

    clearScreen();
    cout << frameText("How do you want your list sorted?")
         << "1: Sort by name" << endl
         << "2: Sort by year of birth" << endl
         << "3: Sort by year of death" << endl
         << "4: Sort by sex" << endl
         << "5+: No sorting" << endl
         << DASHES << endl;

    choice = getInt("");

    //Fetches the desired sorting information
    switch ( choice )
    {
    case 1: sort.sortBy = SNAME; break;
    case 2: sort.sortBy = BIRTH; break;
    case 3: sort.sortBy = DEATH; break;
    case 4: sort.sortBy = SEX; break;
    case 5:
    default:return ScientistSortOrder(SID);
    }

    sort.direction = getDirection();
    return sort;
}

/*!
 * \brief Console::getComputerSort
 * \return ComputerSortOrder
 */
ComputerSortOrder Console::getComputerSort()
{
    int choice;
    ComputerSortOrder sort;

    clearScreen();
    cout << frameText("How do you want your list sorted?")
         << "1: Sort by computer name" << endl
         << "2: Sort by year" << endl
         << "3: Sort by type" << endl
         << "4: Sort by whether or not it was built" << endl
         << "5+: No sorting" << endl
         << DASHES << endl;

    choice = getInt("");

    //Fetches the desired sorting information
    switch ( choice )
    {
    case 1: sort.sortBy = CNAME; break;
    case 2: sort.sortBy = BUILT; break;
    case 3: sort.sortBy = TYPE; break;
    case 4: sort.sortBy = BUILT; break;
    case 5:
    default:return ComputerSortOrder(CID);
    }

    sort.direction = getDirection();
    return sort;
}


/*!
 * \brief Console::getDirection
 * \return direction
 */
Direction Console::getDirection()
{
    cout << DASHES << endl <<
            "Ascending or descending?\n"
            "1: Ascending\n"
            "2: Descending?\n";

    int choice;
    choice = getInt("");
    switch ( choice )
    {
    case 1: return ASCENDING;
    case 2: return DESCENDING;
    default: return ASCENDING;
    }
}

/*!
 * \brief Console::isNameValid
 * Checks for user intent, all names are allowed, but weird characters are checked
 * and the user gets prompted on if the name should contain that character
 * \param Takes in a name to check
 * \return True if name is normal or if the user intends to use special characters
 */
bool Console::isNameValid(string name)
{
    // QStrings alow us to use UTF8 encoding and comparison
    QString listOfBadCharacters = QString::fromUtf8(".;:¡@¢‰^{[]}–<>!\"#$%&/()=?_*~");
    QString unicodeName = QString::fromUtf8(name.c_str());

    // Numbers are allowed, but user is prompted
    for(size_t i = 0; i < name.length(); i++)
    {
        if (isdigit(name[i]))
        {
            if(!promptYesNo("Did you mean to leave a number in the name? Y/N"))
            {
                return false;
            }
            else
            {
                break;
            }
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
                if(!promptYesNo(""))
                {
                    return false;
                }
                else
                {
                    i++;
                }
            }
        }

    }
    return true;
}

/*!
 * \brief Console::prompt
 * For use in Yes / No prompts
 * \returns a true if user types y and false if user types in n,
 * Loops until it gets either.
 */
bool Console::promptYesNo(string prompt){
    while(true){
        cout << prompt << ": ";
        string answer = "";
        cin.clear();
        getline(cin, answer);
        if (answer[0] == 'n' || answer[0] == 'N')
        {
            return false;
        }
        else if (answer[0] == 'y' || answer[0] == 'Y')
        {
            return true;
        }
        else
        {
            cout << "Invalid input, try again"<< endl << ":";
        }
        cout << answer;
    }
}

/*!
 * \brief Console::getInt
 * Some code taken from http://www.cplusplus.com/forum/articles/6046/
 * \param prompt
 * \return myNumber
 */
int Console::getInt(string prompt)
{
    string input = "";
    int myNumber = 0;
    while (true) {
        cout << prompt << ": ";
        getline(cin, input);

        // This code converts from string to number safely.
        stringstream myStream(input);
        if (myStream >> myNumber)
        {
            break;
        }
        cout << "Not a number, please try again";
    }
    return myNumber;
}

/*!
 * \brief Console::clearScreen
 * Dirty way of making the console look nicer when running
 */
void Console::clearScreen()
{
    //system("clear");
    system("CLS");
}

/*!
 * \brief Console::displayScientists
 * A printer that displays all the relevant info about the scientists
 * \param scientists
 */
void Console::displayScientists(vector<Scientist> scientists)
{
    cout << DASHES << endl
         << setw(5) << left << "ID"
         << setw(5) << left << "Age"
         << setw(5) << left << "Sex"
         << setw(7) << left << "Birth"
         << setw(8) << left << "Death"
         << setw(30) << left << "Name"
         << setw(50) << left << "About"<< endl
         << DASHES << endl;
    for(size_t i = 0; i < scientists.size(); i++)
    {
        cout << setw(5) << left << scientists[i].getID()
             << setw(5) << left << scientists[i].getAge()
             << setw(5) << left << scientists[i].getSex()
             << setw(7) << left << scientists[i].getBirthYear()
             << setw(8) << left;
        if(scientists[i].getDeathYear() != 0)
        {
            cout << scientists[i].getDeathYear();
        }
        else
        {
            cout << "Alive";
        }
        cout << setw(30) << left << scientists[i].getName()
             << setw(50) << left << scientists[i].getAbout()
             << endl;
    }
    cout << DASHES << endl;
}

/*!
 * \brief Console::displayComputers
 * A printer that displays all the relevant info about the computers
 * \param computers
 */
void Console::displayComputers(vector<Computer> computers)
{
    // This Could be moved into a function,
    // sets the with of the name column, they tend to differ wildly in lenght
    int longestComputerName = 4;
    int longestTypeName = 4;
    for (size_t i = 0; i < computers.size(); i++)
    {
        if (computers.at(i).getName().length() > longestComputerName)
        {
            longestComputerName = computers.at(i).getName().length();
        }
        if (dataMan->getTypeOfComputerFromId(computers[i].getType()).length() > longestTypeName)
        {
            longestTypeName = dataMan->getTypeOfComputerFromId(computers[i].getType()).length();
        }
    }
    longestComputerName += 2;
    longestTypeName += 2;


    cout << DASHES << endl
         << setw(4) << left << "ID"
         << setw(7) << left << "Built"
         << setw(longestTypeName) << left << "Type"
         << setw(6) << left << "Year"
         << setw(longestComputerName) << left << "Name"
         << setw(50) << left << "About"<< endl
         << DASHES << endl;
    for(size_t i = 0; i < computers.size(); i++)
    {
        cout << setw(4) << left << computers[i].getID()
             << setw(7) << left << computers[i].getWasItBuiltString()
             << setw(longestTypeName) << left << dataMan->getTypeOfComputerFromId(computers[i].getType())
             << setw(6) << left << computers[i].getBuildYear()
             << setw(longestComputerName) << left << computers[i].getName()
             << setw(50) << left << computers[i].getAbout()
             << endl;
    }
    cout << DASHES << endl;
}

/*!
 * \brief Console::frameText
 * It's the thing that makes is all look so pretty
 * \param emphasize
 */
string Console::frameText(string emphasize)
{
    return DASHES + "\n"
         + emphasize + "\n"
         + DASHES + "\n";
}

/*!
 * \brief Console::promptEnterToContinue
 * Enter to contine, need I say more
 */
void Console::promptEnterToContinue()
{
    cout << "Press enter to continue ";
    string stopHere;
    getline(cin,stopHere);
}

/*!
 * \brief Console::findComputerToEdit
 * Asks for user input in the search of computers with mathcing names
 * will find substings but is case sensitive
 */
void Console::findComputerToEdit()
{
    int id = promptFindComputer();

    // if no id was found
    if (!id) { return; }

    //edits the computer who's ID matches id
    changeComputer(dataMan->getComputerFromId(id));
}

/*!
 * \brief Console::changeComputer
 * \param comp
 * \param id
 * Performs the edit on a computer in parameter computers that has an ID matching id
 */
void Console::changeComputer(Computer comp)
{
    clearScreen();

    string info;

    do{
        cout << frameText("What would you like to change about " + comp.getName() + "?")
             << "1: Name" << endl
             << "2: Build year" << endl
             << "3: Type" << endl
             << "4: Was it built" << endl
             << "5: About" << endl
             << DASHES << endl;

        int select = getInt("");

        //User chooses which attribute to edit
        switch(select)
        {
        case 1:
            //sets the chosen computers name to user's input
            comp.setName(promptName());
            break;

        case 2:
            //sets the chosen computer build year to user's input
            comp.setBuildYear(promptComputerMakeYear());
            break;

        case 3:
            //sets the chosen computers type to user's input
            comp.setType(promptType());
            break;

        case 4:
            //sets the chosen computers was built to user's input
            comp.setWasItBuilt(promptYesNo("Was the computer built? Y/N"));
            break;

        case 5:
            //sets the chosen computers about to user's input
            comp.setAbout(promptAbout());
            break;

        default:
            cout << "1-5 not selected, going back\n";
            return;
        }

        //Show the user the modified scientist
        clearScreen();

                info = frameText(comp.getName() + "'s information is now:") +
                      "Name: " + comp.getName() +
                      "\nBuild Year: " + to_string(comp.getBuildYear()) +
                      "\nType: " + dataMan->getTypeOfComputerFromId(comp.getID()) +
                      "\nWas it built: " + comp.getWasItBuiltString() +
                      "\nAbout: " + comp.getAbout() +
                       "\n" + DASHES +
                      "\nDone editing? Y/N";

        dataMan->updateComputer(comp);
    }while(!promptYesNo(info));
}
