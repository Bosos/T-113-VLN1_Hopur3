#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "hello world" << endl;
    return a.exec();
}

