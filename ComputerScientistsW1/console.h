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
    void findScientistToEdit();
    void findScientistToDelete();
    void changeScientist(vector<Scientist> scientis, int id);
    void deleteScientist(vector<Scientist> scientis, int id);
    bool promptAgain(string prompt);
    SortOrder getSort();
    Direction getDirection();
    vector<Scientist> getScientist();
    void clearScreen();

    // Promts
    string promptName();
    string promptAbout();
    char promptSex();
    int promptBirthYear();
    int promptDeathYear(int birthYear);
    int getInt(string prompt);

    // Checkers
    bool isNameValid(string name);
    bool isAboutValid(string about);

    // Printers
    void displayScientists(vector<Scientist> scientis);
    void welcome();
};

#endif // CONSOLE_H
