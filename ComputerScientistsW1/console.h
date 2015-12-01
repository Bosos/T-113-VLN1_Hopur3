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
    SortBy getSort();
    Direction getDirection();
    void editDatabase();
    void showScientists();
    void insertScientist();
    vector<Scientist> getScientist();
    string promptName();
    char promptSex();
    int promptBirthYear();
    int promptDeathYear(int birthYear);
    bool isNameValid(string name);
    bool promptAgain(string prompt);
    int getInt(string prompt);

};

#endif // CONSOLE_H
