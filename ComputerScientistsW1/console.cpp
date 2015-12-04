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
        cout << "-------------------------------------------------------------"
                "\nWelcome to the Computer Scientists database. Enter a number\n"
                "-------------------------------------------------------------"
                "\n1: Edit database"
                "\n2: See database"
                "\n3: Quit";

        int select = getInt("");    //stores the user's choice

        switch (select) {   //Calls appropriate function based on the user's choice

        case 1:
            editDatabase();
            break;

        case 2:
            showScientists();
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
 * \brief Console::editDatabase
 * runs the editing part of the program
 */
void Console::editDatabase()
{
    clearScreen();
    cout << "-------------------------------------------------------------"
            "\nEdit the Database\n"
            "-------------------------------------------------------------"
            "\n1: Add a scientist to the database"
            "\n2: Add a computer to the database"
            "\n3: Edit an entry in the database"
            "\n4: Delete an entry in the database"
            "\nOther numbers: Go back to the start";

    int select = getInt("");    //Stores the user's choice

    //Calls appropriate functions based on the user's choice
    switch (select)
    {
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
            insertComputer();
        }while(promptAgain("Do you want to add another computer? Y/N"));
        return;
    case 3:
        do
        {
            clearScreen();
            findScientistToEdit();
        }while(promptAgain("Do you want to edit another computer scientist? Y/N"));
        return;

    case 4:
        do
        {
            clearScreen();
            findScientistToDelete();
        }while(promptAgain("Do you want to delete another computer scientist? Y/N"));
        return;
    default:
        cout << "1-3 not selected, going back\n";
        return;
    }
}

void Console::insertComputer()
{
    cout << "-------------------------------------------------------------"
            "\nPlease fill inn all the information about the computer\n"
            "-------------------------------------------------------------\n";

    //creating variables
    string info = "";
    string name = "";
    int buildYear = 0;
    string type = "";
    string about = "";
    bool wasItBuilt = false;
    string ans = "No";

    // The user can modify more than one field before he finishes
    do
    {
        //inserting information about the new scientist into the parameters
        name = promptName();
        int buildYear = promptBirthYear();
        type = promptType();
        about = promptAbout();
        wasItBuilt = promptWasItBuilt();

        if(wasItBuilt) {ans = "Yes";}

        clearScreen();
        info = "-------------------------------------------------------------"
               "\nComputer information:\n"
               "-------------------------------------------------------------"
               "\nName: " + name +
               "\ntype: " + type +
               "\nYear built: " + to_string(buildYear) +
               "\nWas it built? " + ans +
               "\nAbout: " + about +
               "\nIs this correct? Y/N";

    }while(!promptAgain(info));

    // adds the new computer to the database
    this->dataMan->addComputer(Computer(name, buildYear, type, wasItBuilt, about, 0));
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
    cout << "-------------------------------------------------------------"
            "\nPlease fill inn all the information about the scientist\n"
            "-------------------------------------------------------------";

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

    //adds the new scientist to the database
    this->dataMan->addScientist(Scientist(name, sex, birthYear, deathYear, about, 0));
}


/*!
 * \brief Console::findScientistToEdit
 * Asks for user input in the search of a scientists with mathcing names
 * will find substings but is case sensitive
 */
void Console::findScientistToEdit()
{
    //creating variables
    string info = "";
    SortOrder sort;
    sort.sortBy = NONE;
    sort.direction = ASCENDING;

    cout << "-------------------------------------------------------------"
            "\nPlease enter the name of the scientist you want to edit\n"
            "-------------------------------------------------------------";
    string name = promptName();

    //finds all the scientists whos names match the user input and inserts them to a vector of scientists
    vector<Scientist> allScientists = dataMan->findByName(name, sort);

    //If there are more than 1 scientists that match the user input, the program shows all of them to the user and then the user chooses the id of the scientist he want's to edit
    if(allScientists.size() > 1)
    {
        clearScreen();
        cout << "\nMatching scientists:\n";

        displayScientists(allScientists);

        cout <<"Insert the ID of the scientist you want to edit: ";
        int id = getInt("");    //Stores the ID of the chosen scientist

        changeScientist(dataMan->getAllScientists(sort), id);   //edits the scientist who's ID matches id
    }
    else if(allScientists.size() == 0)  //if there are no matching scientists
    {
        cout << "\nSorry, there is no matching scientist in datafile\n";
    }
    //if there is only one scientist who's name matches the input
    else
    {
        changeScientist(dataMan->getAllScientists(sort), allScientists.at(0).getID());  //edits the scientist
    }
}

/*!
 * \brief Console::findScientistToDelete
 * Finds the scientist the user wants to delete
 */
void Console::findScientistToDelete()
{
    //creating varibles
    string info = "";
    SortOrder sort;
    sort.sortBy = NONE;
    sort.direction = ASCENDING;

    cout << "-------------------------------------------------------------"
            "\nPlease enter the name of the scientist you want to delete\n"
            "-------------------------------------------------------------";
    //gets the name of the scientist the user want's to delete
    string name = promptName();
    //creates a vector of scientists who's name match the user's input
    vector<Scientist> allScientists = dataMan->findByName(name, sort);

    //if there are more than 1 matching scientists, the program prints all the matching scientists and the user chooses the scientist's ID
    if(allScientists.size() > 1)
    {
        clearScreen();
        cout << "\nMatching scientists:\n";

        //displays all the matching scientists
        displayScientists(allScientists);

        cout <<"Insert the ID of the scientist you want to delete: ";
        int id = getInt("");    //gets the id

        //deletes the scientist who's name and id match the user input
        deleteScientist(dataMan->getAllScientists(sort), id);
    }
    //if there are no matching scientists
    else if(allScientists.size() == 0)
    {
        cout << "\nSorry, there is no matching scientist in datafile\n";
    }
    //if there is one matching scientist, he is deleted
    else
    {
        deleteScientist(dataMan->getAllScientists(sort), allScientists.at(0).getID());
    }
}

/*!
 * \brief Console::changeScientist
 * \param scientis
 * \param id
 * Performs the edit on a scientist in parameter scientists that has an ID matching id
 */
void Console::changeScientist(vector<Scientist> scientis, int id)
{
    clearScreen();

    string info;

    do{
        cout << "-------------------------------------------------------------"
                "\nWhat would you like to change about " + scientis[id].getName() + "?"
                "\n1: Name"
                "\n2: Sex"
                "\n3: Year of birth"
                "\n4: Year of death"
                "\n5: About";

        int select = getInt("");

        switch(select){ //User chooses which attribute to edit
        case 1:
            //sets the chosen scientists name to user's input
            scientis[id].setName(promptName());
            break;

        case 2:
            //sets the chosen scientists sex to user's input
            scientis[id].setSex(promptSex());
            break;

        case 3:
            //sets the chosen scientists birth year to user's input
            scientis[id].setBirthYear(promptBirthYear());
            break;

        case 4:
            //sets the chosen scientists death year to user's input
            scientis[id].setDeathYear(promptDeathYear(scientis[id].getBirthYear()));
            break;

        case 5:
            //sets the chosen scientist's about to user's input
            scientis[id].setAbout(promptAbout());
            break;

        default:
            cout << "1-5 not selected, going back\n";
            return;
        }

        //Show the user the modified scientist
        clearScreen();
                info = "-------------------------------------------------------------"
                      "\n" + scientis[id].getName() + "'s information is now: \n"
                      "-------------------------------------------------------------"
                      "\nName: " + scientis[id].getName() +
                      "\nSex: " + scientis[id].getSex() +
                      "\nYear of birth: " + to_string(scientis[id].getBirthYear()) +
                      "\nYear of death: " + to_string(scientis[id].getDeathYear()) +
                      "\nAbout: " + scientis[id].getAbout() +
                      "\nDone editing? Y/N";

        // if yes? maybe
        //saves the modifications to database
        dataMan->writeNewScientistVectorToFile(scientis);
    }while(!promptAgain(info));
}

/*!
 * \brief Console::deleteScientist
 * \param scientis
 * \param id
 * Deletes a scientist in scientis who's ID matches id and saves the changes
 */
void Console::deleteScientist(vector<Scientist> scientis, int id)
{
    clearScreen();
    displayScientists(vector<Scientist>(1,scientis[id]));


    //User has to be sure if he want's to totally eliminate this scientist
    if(promptAgain("Sure you want to delete " + scientis[id].getName() + " Y/N"))
    {
        scientis.erase(scientis.begin() + id);
        dataMan->writeNewScientistVectorToFile(scientis);
        //scientist has been removed from database
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
        cout << "\nName: ";
        //gets the user's input
        getline(cin, name);
    } while (!isNameValid(name));

    //capitalize the name
    name[0] = toupper(name[0]);
    for(unsigned int i = 0; i < name.length(); i++)
    {
        if(i > 0 && name[i-1] == ' ')
        name[i] = toupper(name[i]);
    }

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
    //This loops while the "about" field is not valid
    do
    {
        cout << "\nAbout: ";
        //gets the user's input
        getline(cin, about);
    } while (!isAboutValid(about));
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

string Console::promptType()
{
    string type;
    int select;
    cout << "-------------------------------------------------------------" << endl
         << "Computer type: " << endl
         << "-------------------------------------------------------------" << endl
         << "1: Electronic" << endl
         << "2: Mecanic" << endl
         << "3: Transistor Machine" << endl
         << "4: Other";
    select = getInt("");

    switch(select)
    {
        case 1:
            type = "Electronic";
            return type;
        case 2:
            type = "Mecanic";
            return type;
        case 3:
            type = "Transistor Machine";
            return type;
        case 4:
            type = "Other";
            return type;
        default:
            cout << "\nPlease select a number between 1 and 4\n";
            type = promptType();
            return type;
    }

    return type;
}

bool Console::promptWasItBuilt()
{
    string ans;
    cout << "-------------------------------------------------------------" << endl
         << "Was the computer built? (Y/N) " << endl
         << "-------------------------------------------------------------\n" << endl;
    getline(cin, ans);
    if(ans[0] == 'Y' || ans[0] == 'y') {return true;}
    else if(ans[0] == 'N' || ans[0] == 'n') {return false;}
    else
    {
        cout << "\nPlease select either Y or N" << endl;
        return promptWasItBuilt();
    }
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
    string sex = "";
    if (select == 0) { return vector<Scientist>(); }

    //Fetches a function according to the user's input
    switch (select) {

    case 1:
        return dataMan->getAllScientists (getSort());

    case 2:
        return dataMan->findByName (promptName(), getSort());

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
    // CSV uses commas to seperate values, we simply dont allow commas to follow that rule
    for(size_t i = 0; i < about.length(); i++)
    {
        if (about[i] == ',')
        {
            cout << "\nCommas in names are not allowed";
            return false;
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
