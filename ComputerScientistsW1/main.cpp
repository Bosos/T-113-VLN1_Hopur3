#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


//#include <iostream>
//#include <Console.h>
//#include "DataManager.h"

//using  namespace std;

//int main()
//{


//    Console console(dataMan);

//    console.run();

//    delete dataMan;

//    return 0;
//}
