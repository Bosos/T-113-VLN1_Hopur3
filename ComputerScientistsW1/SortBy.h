#ifndef SORTBY
#define SORTBY
#include <string>

using namespace std;

/*!
 * \brief The ScientistSortBy enum
 * These enums and structs store sorting information that tells
 * the dataManager how to sort incoming data
 */
enum ScientistSortBy {SID = 0, SNAME, BIRTH, DEATH, SEX};
enum ComputerSortBy {CID = 0, CNAME, BUILT, TYPE, WASBUILT};
enum Direction {ASCENDING = 0, DESCENDING};

struct ScientistSortOrder
{
    ScientistSortOrder();
    ScientistSortOrder(ScientistSortBy sortBy);
    string getSortByString();
    string getDirectionString();
    ScientistSortBy sortBy = SID;
    Direction direction = ASCENDING;
};

struct ComputerSortOrder
{
    ComputerSortOrder();
    ComputerSortOrder(ComputerSortBy sortBy);
    string getSortByString();
    string getDirectionString();
    ComputerSortBy sortBy = CID;
    Direction direction = ASCENDING;
};



#endif // SORTBY

