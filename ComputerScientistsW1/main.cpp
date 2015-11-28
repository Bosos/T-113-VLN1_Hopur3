#include <QCoreApplication>
#include <iostream>
#include <Console.h>
#include <DataManager.h>

using  namespace std;

int main()
{

    DataManager* dataMan = new DataManager("file location");
    Console console(dataMan);

    console.run();

    delete dataMan;

    return 0;
}

