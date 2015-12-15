#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H
#include <qstring.h>

struct ScientistSearch
{
    void setSex(QString sex);
    int getAge();
    QString getSex();
    QString name = "";
    QString birth = "";
    QString death = "";
    QString about = "";
private:
    QString sex = "";
};

struct ComputerSearch
{
    void setType(int type);
    void setWasItBuilt(int wasBuilt);
    QString getType();
    QString getWasItBuilt();
    QString name = "";
    QString buildYear = "";
    QString about = "";
private:
    QString type = "";
    QString wasItBuilt = "";
};


class SearchCriteria
{
public:
    SearchCriteria();
};

#endif // SEARCHCRITERIA_H
