
#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int mRows;
        int mCols;
        char mGrid[MAXROWS][MAXCOLS];
    };

#endif //HISTORY_INCLUDED
