#include <iostream>
#include <Console.h>
#include "DataManager.h"

using  namespace std;

int main()
{
    cout << "hello world";
    string fileLocation = "database.sqlite";
    DataManager* dataMan = new DataManager(fileLocation);
    Console console(dataMan);

    console.run();

    delete dataMan;


    return 0;
}
