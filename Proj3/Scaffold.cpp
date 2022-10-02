// Scaffold.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <utility>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    //Coord class for tracking moves
    class Coord
    {
    public:
        Coord(int row, int column) : r(row), c(column)
        {}
        int row() const
        {
            return r;
        }
        int col() const
        {
            return c;
        }
    private:
        int r;
        int c;
    };

    //Coord stack to track sequence of moves
    stack<Coord> tracker;
    int nCol;
    int nRow;
    vector<vector<char>> grid;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    //Checks for nonpositive parameters
    if (nColumns <= 0 || nLevels <= 0)
    {
        cerr<<"Column and level must be positive."<<endl;
        exit(1);
    }
    nCol = nColumns;
    nRow = nLevels;
    grid.resize(nRow);
    for (int i = 0; i < nRow; i++)
    {
        grid[i].resize(nCol);
    }
    for (int r = 0; r < nRow; r++)
    {
        for (int c = 0; c < nCol; c++)
        {
            grid[r][c] = ' ';
        }
    }
}

int ScaffoldImpl::cols() const
{
    return nCol;
}

int ScaffoldImpl::levels() const
{
    return nRow;
}

int ScaffoldImpl::numberEmpty() const
{
    int counter = 0;
    //Nested for loops to iterate entire grid
    for (int r = 0; r < nRow; r++)
    {
        for (int c = 0; c < nCol; c++)
        {
            //Character space represents empty
            if (grid[r][c] == ' ')
            {
                counter++;
            }
        }
    }
    return counter;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    //Return correct global constant at position
    if (grid[nRow-level][column-1] == 'R')
    {
        return RED;
    }
    else if (grid[nRow-level][column-1] == 'B')
    {
        return BLACK;
    }
    else
    {
        return VACANT;
    }
}

void ScaffoldImpl::display() const
{
    //Nested for loops to cout grid with side bars
    for (int r = 0; r < nRow; r++)
    {
        for (int c= 0; c < nCol; c++)
        {
            cout<<'|'<<grid[r][c];
        }
        cout<<'|'<<endl;
    }
    //Cout bottom joints
    for (int i = 0; i < nCol; i++)
    {
        cout<<'+'<<'-';
    }
    cout<<'+'<<endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    //Check validity
    if (column <= 0 || column > nCol)
    {
        return false;
    }
    if (color == RED || color == BLACK)
    {
        //Check vacancy
        if (grid[0][column-1] != ' ')
        {
            return false;
        }
        int r = 0;
        //Find lowest vacant position
        while (r < nRow)
        {
            if (grid[r][column-1] != ' ')
            {
                break;
            }
            r++;
        }
        r--;
        //Assign correct checker to position
        if (color == RED)
        {
            grid[r][column-1] = 'R';
        }
        else
        {
            grid[r][column-1] = 'B';
        }
        tracker.push(Coord(r, column-1));
        return true;
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    if (tracker.empty())
    {
        return 0;
    }
    //Pop top stacker value and return it
    Coord temp(tracker.top());
    tracker.pop();
    grid[temp.row()][temp.col()] = ' ';
    return (temp.col() + 1);
}



//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
