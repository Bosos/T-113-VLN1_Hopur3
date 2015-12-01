#ifndef SORTBY
#define SORTBY

enum SortBy {NONE = 0, NAME, BIRTH, DEATH, SEX};
enum Direction {ASCENDING = 0, DESCENDING};

struct SortOrder
{
    SortBy sortBy = NONE;
    Direction direction = ASCENDING;
};

#endif // SORTBY

