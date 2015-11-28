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
    void showScientists();
    vector<Scientist> getScientist();
};

#endif // CONSOLE_H
