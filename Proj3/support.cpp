#include "support.h"
#include "provided.h"

//Used for Game::completed and rateMove to check for completed games
//n represents needed checkers in a row
bool completedHelper(const Scaffold& s, int n, int col)
{
    int hCounter = 1; //Horizontal win counter
    int vCounter = 1 ; //Vertical win counter
    int drCounter = 1; //Right diagonal counter
    int dlCounter = 1; //Left diagonal counter
    int row = s.levels();
    //Find move's row
    while (s.checkerAt(col, row) == VACANT)
    {
        row--;
    }
    int color = s.checkerAt(col, row);
    //Check for horizontal win
    for (int c = col+1; c < s.cols()+1; c++)
    {
        if (s.checkerAt(c, row) == color)
        {
            hCounter++;
        }
        else
        {
            break;
        }
    }
    for (int c = col-1; c > 0; c--)
    {
        if (s.checkerAt(c, row) == color)
        {
            hCounter++;
        }
        else
        {
            break;
        }
    }
    if (hCounter >= n)
    {
        return true;
    }
    //Check for vertical win
    for (int r = row-1; r > 0; r--)
    {
        if (s.checkerAt(col, r) == color)
        {
            vCounter++;
        }
        else
        {
            break;
        }
    }
    if (vCounter >= n)
    {
        return true;
    }
    //Check for right diagonally win
    for (int c = col+1, r = row+1; c < s.cols()+1 && r < s.levels()+1; c++, r++)
    {
        if (s.checkerAt(c, r) == color)
        {
            drCounter++;
        }
        else
        {
            break;
        }
    }
    for (int c = col-1, r = row-1; c > 0 && r > 0; c--, r--)
    {
        if (s.checkerAt(c, r) == color)
        {
            drCounter++;
        }
        else
        {
            break;
        }
    }
    if (drCounter >= n)
    {
        return true;
    }
    //Check for right diagonally win
    for (int c = col-1, r = row+1; c > 0 && r < s.levels()+1; c--, r++)
    {
        if (s.checkerAt(c, r) == color)
        {
            dlCounter++;
        }
        else
        {
            break;
        }
    }
    for (int c = col+1, r = row-1; c < s.cols()+1 && r > 0; c++, r--)
    {
        if (s.checkerAt(c, r) == color)
        {
            dlCounter++;
        }
        else
        {
            break;
        }
    }
    if (dlCounter >= n)
    {
        return true;
    }
    return false;
}
