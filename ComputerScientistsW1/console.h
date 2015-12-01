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
    DataManager* dataMan;
    SortOrder getSort();
    Direction getDirection();
    void editDatabase();
    void showScientists();
    void insertScientist();
    vector<Scientist> getScientist();
    string promptName();
    string promptAbout();
    char promptSex();
    int promptBirthYear();
    int promptDeathYear(int birthYear);
    bool isNameValid(string name);
    bool isAboutValid(string about);
    bool promptAgain(string prompt);
    int getInt(string prompt);
    void clearScreen();
    void findScientistToEdit();
    void findScientistToDelete();
    void changeScientist(vector<Scientist> scientis, int id);
    void deleteScientist(vector<Scientist> scientis, int id);
    void displayScientists(vector<Scientist> scientis);
};

#endif // CONSOLE_H
