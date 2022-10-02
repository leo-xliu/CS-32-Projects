
#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
    :mRows(nRows), mCols(nCols)
{
    for (int r = 0; r < nRows; r++)
    {
        for (int c = 0; c < nCols; c++)
        {
            mGrid[r][c] = '.'; //Initiates the given rows and columns with periods
        }
    }
}

bool History::record(int r, int c)
{
    if ((r > mRows) || (r <= 0) || (c > mCols) || (c <= 0))
    {
        return false; 
    }
    int nr = r -1;
    int nc = c - 1;
    if ((mGrid[nr][nc] >= 'A') && (mGrid[nr][nc] < 'Z')) //Increments for A-Y
    {
        mGrid[nr][nc]++;
    }
    else if (mGrid[nr][nc] == '.') //Period to become A
    {
        mGrid[nr][nc] = 'A';
    }
    //Nothing happens if it is on Z
    return true;
}

void History::display() const
{
    clearScreen();
    for (int r = 0; r < mRows; r++)
    {
        for (int c = 0; c < mCols; c++)
        {
            cout<<mGrid[r][c]; //Prints the grid incremently
        }
        cout<<endl;
    }
    cout<<endl;
}
