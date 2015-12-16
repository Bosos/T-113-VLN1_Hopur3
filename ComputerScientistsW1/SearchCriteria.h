#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H
#include <qstring.h>

/*!
 * \brief SearchCriteria
 * A loose version of scientist and computer that does not maintain its credibility
 * stores most information in QStrings for better compatibility with Qt in general
 */
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

#endif // SEARCHCRITERIA_H
