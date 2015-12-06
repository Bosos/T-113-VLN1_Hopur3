#ifndef CONSOLE_H
#define CONSOLE_H
#include <DataManager.h>

class Console
{
public:
    Console(DataManager* dataMan);
    ~Console();
    void run();
private:
    // Class variables
    DataManager* dataMan;

    // Menus
    void editDatabase();
    void showScientists();
    void insertScientist();
    int findScientist();
    int findComputer();
    void findScientistToEdit();
    void findScientistToDelete();
    void findComputerToDelete();
    void deleteComputer(Computer comp);
    void findSciAndComToMakeUser();
    void changeScientist(Scientist scientis);
    void deleteScientist(Scientist scientis);
    ScientistSortOrder getSort();
    Direction getDirection();
    vector<Scientist> getScientist();
    void clearScreen();
    void insertComputer();
    void insertUser();
    void showComputers();

    vector<Computer> getComputer();
    void seeDatabase();

    // Promts
    bool promptYesNo(string prompt);
    string promptName();
    string promptAbout();
    char promptSex();
    int promptBirthYear();
    int promptComputerMakeYear();
    int promptDeathYear(int birthYear);
    int getInt(string prompt);
    int promptType();
    bool promptWasItBuilt();
    void makeNewTypeOfComputer();
    void showWhatComputersAScientistUsed();
    void showWhatScientistsUsedAComputer();
    void promptEnterToContinue();

    // Checkers
    bool isNameValid(string name);
    //bool isAboutValid(string about);
    bool welcomeShown;

    // Printers
    void displayScientists(vector<Scientist> scientis);
    void displayComputers(vector<Computer> computers);
    void displayRelation(Scientist scientist);
    void welcome();
    string frameText(string emphasize);

};

#endif // CONSOLE_H
