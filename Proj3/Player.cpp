// Player.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct results
{
    int col;
    int score;
};

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
    {
        return 0;
    }
    int move;
    while (true)
    {
        cout<<"Enter a valid column to move: ";
        cin>>move;
        //Check for valid integer range
        if (move > 0 && move <= s.cols())
        {
            //Check for full column
            if (s.checkerAt(move, s.levels()) == VACANT)
            {
                break;
            }
        }
        cout<<"Invalid or full column."<<endl;
    }
    return move;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
    {
        return 0;
    }
    int i = 1;
    //Loop to find left most column with empty slot
    while (i <= s.cols())
    {
        if (s.checkerAt(i, s.levels()) == VACANT)
        {
            break;
        }
        i++;
    }
    return i;
}

//Helper function declarations
bool rateMove(const Scaffold& s, int N, int c, int& score, int color, int marker);

results determineBestMove(Scaffold s, int N, int color, int marker);

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int marker = color;
    return determineBestMove(s, N, color, marker).col;
}

//color needs to alternate
results determineBestMove(Scaffold s, int N, int color, int marker)
{
    //Stores move column and score
    vector<results> path(s.cols()+1); //Path[0] will never be called, path[1]-path[s.cols()] will be used for readability
    for (int c = 1; c < s.cols()+1; c++)
    {
        if (s.makeMove(c, color)) //If no moves can be made for that column it will cause the column to be void
        {
            if (!rateMove(s, N, c, path[c].score, color, marker)) //Rate move will return true and update score if game is won or tied otherwise it will return false and not alter score
            {
                //Game is not over so next player will move through all paths using recursion
                //Note if the game had been a draw (no available moves) it will not be recursive so we will never have to consider a case of all void columns
                if (color == RED)
                {
                    path[c].score = determineBestMove(s, N, color+1, marker).score;
                }
                else
                {
                    path[c].score = determineBestMove(s, N, color-1, marker).score;
                }
            }
            path[c].col = s.undoMove();
        }
        else
        {
            path[c].col = -1;
        }
    }
    //Find first VALID column path
    int best = 1;
    while (path[best].col == -1)
    {
        best++;
    }
    if (color == marker) //Decides if it should find greatest score or lowest
    {
        for (int i = best+1; i < s.cols()+1; i++)
        {
            //Skip void columns
            if (path[i].col == -1)
            {
                continue;
            }
            if (path[best].score < path[i].score)
            {
                best = i;
            }
        }
    }
    else
    {
        for (int i = best+1; i < s.cols()+1; i++)
        {
            if (path[i].col == -1)
            {
                continue;
            }
            if (path[best].score > path[i].score)
            {
                best = i;
            }
        }
    }
    return path[best];
}

bool rateMove(const Scaffold& s, int N, int c, int& score, int color, int marker)
{
    //Uses a helper function to see if game is complete
    if (completedHelper(s, N, c))
    {
        if (color == marker)
        {
            //Uses number of empty proxy to calculate score
            score = (1 + s.numberEmpty());
        }
        else
        {
            score = -(1 + s.numberEmpty());
        }
        return true;
    }
    else if (s.numberEmpty() == 0)
    {
        score = 0;
        return true;
    }
    else
    {
        return false;
    }
}


//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
