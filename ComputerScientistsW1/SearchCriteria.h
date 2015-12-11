#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H
#include <qstring.h>

struct ScientistSearch
{
    void setSex(QString sex);
    QString getSex();
    QString name = "";
    QString birth = "";
    QString death = "";
    QString about = "";
private:
    QString sex = "";
};


class SearchCriteria
{
public:
    SearchCriteria();
};

#endif // SEARCHCRITERIA_H