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
             << "3: Quit";

        int select = getInt("");    //stores the user's choice

        switch (select) {   //Calls appropriate function based on the user's choice

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

void Console::seeDatabase()
{
    while(true)
    {
        clearScreen();

        cout << frameText("What do you want to see?")
             << "1: Scientists" << endl
             << "2: Computers";
                //TODO more to see

        int select = getInt("");    //stores the user's choice

        switch (select) {   //Calls appropriate function based on the user's choice

        case 1:
            showScientists();
            break;

        case 2:
            showComputers();
            break;

        default:
            // Repeat while loop
            //cout << "The number should be between 1 and 2";
            return;
        }
    }
}

void Console::showComputers()
{
    //Creates a vector containing all scientists in currently database
        vector<Computer> computers = getComputer();

        if (computers.size() == 0) { cout << "No No computer found"; }

        //Prints out the scientists currently in database
        else
        {
            clearScreen();
            displayComputers(computers);
        }

        // Wait for user input so the results can stay on screen
        string continues;
        getline(cin,continues);
}

/*!
 * \brief Console::editDatabase
 * runs the editing part of the program
 */
void Console::editDatabase()
{
    clearScreen();

    cout << frameText("Edit the Database")
         << "1: Add a scientist to the database" << endl
         << "2: Add a computer to the database" << endl
         << "3: Add a scientist - computer relation" << endl
         << "4: Edit an entry in the database" << endl
         << "5: Delete a scientst from the database" << endl
         << "6: Delete a computer from the database" << endl
         << "Other numbers: Go back to the start";

    int select = getInt("");    //Stores the user's choice

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
            insertUser();
        }while(promptYesNo("Do you want to add another scientist - computer relation? Y/N"));

        return;

    case 4:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the scientist you want to edit");
            findScientistToEdit();
        }while(promptYesNo("Do you want to edit another computer scientist? Y/N"));
        return;

    case 5:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the scientist you want to delete");
            findScientistToDelete();
        }while(promptYesNo("Do you want to delete another computer scientist? Y/N"));
        return;
    case 6:
        do
        {
            clearScreen();
            cout << frameText("Please enter the name of the computer you want to delete");
            findComputerToDelete();
        }while(promptYesNo("Do you want to delete another computer? Y/N"));
    default:
        cout << "1-3 not selected, going back\n";
        return;
    }
}

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
               "\nName: " + name +
               "\ntype: " + dataMan->getTypeOfComputerFromId(type) +
               "\nYear built: " + to_string(buildYear) +
               "\nWas it built? " + ans +
               "\nAbout: " + about +
               "\nIs this correct? Y/N";

    }while(!promptYesNo(info));

    // adds the new computer to the database
    this->dataMan->addComputer(Computer(name, buildYear, type, wasItBuilt, about, 0));
}

void Console::insertUser()
{
    findScientistToEdit();
}

/*!
 * \brief Console::showScientists
 * prints out scientists in sorted order
 */
void Console::showScientists()
{
    //Creates a vector containing all scientists in currently database
    vector<Scientist> scientists = getScientist();

    if (scientists.size() == 0) { cout << "No Scientist found"; }

    //Prints out the scientists currently in database
    else
    {
        clearScreen();
        displayScientists(scientists);
    }

    // Wait for user input so the results can stay on screen
    string continues;
    getline(cin,continues);
}

/*!
 * \brief Console::insertScientist
 * for inserting into the datafile
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
               "\nIs this correct? Y/N";

    }while(!promptYesNo(info));

    //adds the new scientist to the database
    this->dataMan->addScientist(Scientist(name, sex, birthYear, deathYear, about, 0));
}

int Console::findScientist()
{
    string name = promptName();

    //finds all the scientists whos names match the user input and inserts them to a vector of scientists
    vector<Scientist> allScientists = dataMan->findScientistByName(name, SortOrder());

    //If there are more than 1 scientists that match the user input,
    //the program shows all of them to the user and then
    //the user chooses the id of the scientist he want's to edit
    if(allScientists.size() > 1)
    {
        clearScreen();
        cout << "Matching scientists:\n";

        displayScientists(allScientists);

        cout <<"Insert the ID of the scientist you want to select: ";

        // ask user to select and return the selected id
        return getInt("");
    }

    //if there are no matching scientists
    else if(allScientists.size() == 0)
    {
        cout << "\nSorry, there is no matching scientist in datafile\n";
        return 0;
    }

    //return the only scientist, if there is only one scientist who's name matches the input
    else
    {
        return allScientists.at(0).getID();
    }
}

int Console::findComputer()
{
    string name = promptName();

    //finds all the computers whos names match the user input and inserts them to a vector of computers
    vector<Computer> allComputers = dataMan->findComputerByName(name, SortOrder());

    //If there are more than 1 computer that match the user input,
    //the program shows all of them to the user and then
    //the user chooses the id of the scientist he want's to edit
    if(allComputers.size() > 1)
    {
        clearScreen();
        cout << "Matching computers:\n";

        displayComputers(allComputers);

        cout <<"Insert the ID of the computer you want to select: ";

        // ask user to select and return the selected id
        return getInt("");
    }

    //if there are no matching computers
    else if(allComputers.size() == 0)
    {
        cout << "\nSorry, there is no matching computer in datafile\n";
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
    int id = findScientist();

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
    int id = findScientist();

    // if no id was found
    if (!id) { return; }

    //deletes the scientist who's ID matches id
    deleteScientist(dataMan->getScientistFromId(id));
}

void Console::findComputerToDelete()
{
    int id = findComputer();

    // if no id was found
    if (!id) { return; }

    //deletes the scientist who's ID matches id
    deleteComputer(dataMan->getComputerFromId(id));
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
                info = "-------------------------------------------------------------"
                      "\n" + scientis.getName() + "'s information is now: \n"
                      "-------------------------------------------------------------"
                      "\nName: " + scientis.getName() +
                      "\nSex: " + scientis.getSex() +
                      "\nYear of birth: " + to_string(scientis.getBirthYear()) +
                      "\nYear of death: " + to_string(scientis.getDeathYear()) +
                      "\nAbout: " + scientis.getAbout() +
                      "\nDone editing? Y/N";

        // if yes? maybe
        //saves the modifications to database

        //TODO save changes to scientist
        //dataMan->writeNewScientistVectorToFile(scientis);
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
 * \returns a name
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
    cout << "\nAbout: ";
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
        cout << "Year of birth: ";
        birthYear = getInt("");

        //Only allows birthyear to be greater than or equals to 1200 and less than 2016
        if(birthYear >= 1200 && birthYear <= 2015) { return birthYear; }

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
        cout << "When was the computer made/theorized: ";
        makeYear = getInt("");

        //Only allows birthyear to be greater than or equals to 1200 and less than 2016
        if(makeYear >= 1800 && makeYear <= 2015) { return makeYear; }

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

int Console::promptType()
{
    vector<TypeOfComputer> types = dataMan->getTypeOfComputers();
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
    clearScreen();

    int select = 0;
    cout << frameText("Look inside the database")
         << "1: Show a list of them all" << endl
         << "2: Search by a string or substring" << endl
         << "3: Search by birth year" << endl
         << "4: Search by death year" << endl
         << "5: Search by sex";

    select = getInt("");
    string sex = "";
    if (select == 0) { return vector<Scientist>(); }

    //Fetches a function according to the user's input
    switch (select) {

    case 1:
        return dataMan->getAllScientists (getSort());

    case 2:
        return dataMan->findScientistByName (promptName(), getSort());

    case 3:
        return dataMan->findByBirthYear(getInt("Enter the birth year you want to start looking from")
                                       ,getInt("Enter the birth year you want to look until"), getSort());
    case 4:
        return dataMan->findByDeathYear(getInt("Enter the death year you want to start looking from")
                                       ,getInt("Enter the death year you want to look until"), getSort());
    case 5:
        sex = promptSex();
        return dataMan->findBySex(sex, getSort());

    default:
        return getScientist();
    }
}

vector<Computer> Console::getComputer()
{
    clearScreen();
    int select = 0;

    cout << frameText("Look inside the database")
         << "1: Show a list of them all" << endl
         << "2: Search by a string or substring" << endl
         << "3: Search by build year" << endl
         << "4: Search by type" << endl
         << "5: Search by was built" << endl
         << "Other numbers will go back";

    select = getInt("");
    string sex = "";
    if (select == 0) { return vector<Computer>(); }

    //Fetches a function according to the user's input
    switch (select) {

    case 1:
        return dataMan->getAllComputers (getSort());
        //TODO add more cases

    default:
        return getComputer();
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

    cout << frameText("How do you want your list sorted?")
         << "1: No sorting" << endl
         << "2: Sort by name" << endl
         << "3: Sort by year of birth" << endl
         << "4: Sort by year of death" << endl
         << "5: Sort by sex";

    choice = getInt("");

    //Fetches the desired sorting information
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

    // Numbers are allowed, but user is prompted
    for(size_t i = 0; i < name.length(); i++)
    {
        if (isdigit(name[i]))
        {
            if(!promptYesNo("Did you mean to leave a number in the name? Y/N")){ return false; }
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
                if(!promptYesNo("")){ return false; }
                else { i++; }
            }
        }

    }
    return true;
}

/*!
 * \brief Console::prompt
 * For use in Yes / No prompts
 * \returns a true if user types y and false if user types in n,
 * loops until it gets either.
 */
bool Console::promptYesNo(string prompt){
    while(true){
        cout << prompt << endl << ":";
        string answer = "";
        cin.clear();
        getline(cin, answer);
        if (answer[0] == 'n' || answer[0] == 'N') { return false; }
        else if (answer[0] == 'y' || answer[0] == 'Y') { return true; }
        else { cout << "Invalid input, try again"<< endl << ":"; }
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
    system("clear");
    system("CLS");
}

/*!
 * \brief Console::displayScientists
 * A printer that displays all the relevant info about the scientists
 * \param scientists
 */
void Console::displayScientists(vector<Scientist> scientists)
{
    cout << "-------------------------------------------------------------" << endl
         << setw(5) << left << "ID"
         << setw(5) << left << "Age"
         << setw(5) << left << "Sex"
         << setw(7) << left << "Birth"
         << setw(8) << left << "Death"
         << setw(30) << left << "Name"
         << setw(50) << left << "About"<< endl
         << "-------------------------------------------------------------" << endl;
    for(size_t i = 0; i < scientists.size(); i++)
    {
        cout << setw(5) << left << scientists[i].getID()
             << setw(5) << left << scientists[i].getAge()
             << setw(5) << left << scientists[i].getSex()
             << setw(7) << left << scientists[i].getBirthYear()
             << setw(8) << left;
        if(scientists[i].getDeathYear() != 0){ cout << scientists[i].getDeathYear(); }
        else{cout << "Alive";}
        cout << setw(30) << left << scientists[i].getName()
             << setw(50) << left << scientists[i].getAbout()
             << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
}

void Console::displayComputers(vector<Computer> computers)
{
    cout << "-------------------------------------------------------------" << endl
         << setw(5) << left << "ID"
         << setw(8) << left << "Built"
         << setw(11) << left << "Type"
         << setw(6) << left << "Year"
         << setw(30) << left << "Name"
         << setw(50) << left << "About"<< endl
         << "-------------------------------------------------------------" << endl;
    for(size_t i = 0; i < computers.size(); i++)
    {
        string wasBuilt = "Yes";
        if (computers[i].getWasItBuilt()) {wasBuilt = "No"; }
        cout << setw(5) << left << computers[i].getID()
             << setw(8) << left << wasBuilt
             << setw(11) << left << dataMan->getTypeOfComputerFromId(computers[i].getType())
             << setw(6) << left << computers[i].getBuildYear()
             << setw(30) << left << computers[i].getName()
             << setw(50) << left << computers[i].getAbout()
             << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
}

string Console::frameText(string emphasize)
{
    return "●▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬●\n"
         + emphasize
         + "\n●▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬●\n";
}

