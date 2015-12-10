//#ifndef CONSOLE_H
//#define CONSOLE_H
//#include <DataManager.h>

///*!
// * \brief The Console class
// * Responsible for outputing data to the console and prompting the user for input
// */
//class Console
//{
//public:
//    Console(DataManager* dataMan);
//    void run();

//private:
//    // Class variables
//    DataManager* dataMan;

//    // Top menus
//    void menuEditDatabase();
//    void menuSeeDatabase();

//    // Computers
//    void showComputers();
//    vector<Computer> promptGetComputers();
//    void promptAddComputer();
//    int promptFindComputer();
//    void findComputerToEdit();
//    void findComputerToDelete();
//    void changeComputer(Computer comp);
//    void deleteComputer(Computer comp);
//    void promptAddNewTypeOfComputer();

//    // Scientists
//    void showScientists();
//    vector<Scientist> promptGetScientists();
//    void promptAddScientist();
//    int promptFindScientist();
//    void findScientistToEdit();
//    void findScientistToDelete();
//    void changeScientist(Scientist scientis);
//    void deleteScientist(Scientist scientis);

//    // Relation
//    void findSciAndComToMakeUser();
//    void deleteSCRelation();
//    void promptShowWhatComputersAScientistUsed();
//    void promptShowWhatScientistsUsedAComputer();

//    // Short prompts
//    void promptEnterToContinue();
//    bool promptYesNo(string prompt);
//    int promptForInt(string prompt);
//    string promptForName();
//    string promptForAbout();
//    int promptForBirthYear();
//    int promptDeathYear(int birthYear);
//    int promptForComputerMakeYear();
//    char promptForSex();
//    bool promptForIfItWasItBuilt();

//    // Longer prompts
//    ScientistSortOrder promptMenuScientistSort();
//    ComputerSortOrder promptMenuComputerSort();
//    Direction promptMenuSortDirection();
//    int promptMenuTypeOfComputer();

//    // Checkers
//    bool isNameValid(string name);
//    bool welcomeShown;

//    // Printers
//    void clearScreen();
//    void displayScientists(vector<Scientist> scientis);
//    void displayComputers(vector<Computer> computers);
//    void welcome();
//    string frameText(string emphasize);
//};

//#endif // CONSOLE_H
