// Game.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    Scaffold s;
    int connectN;
    Player* p[2]; //First one is red, second is black
    int nWinner;
    int moveCol; //Represents column for last move
    int whoseTurn; //Keep track of whose turn it is (either 0 or 1)
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
: s(nColumns, nLevels)
{
    connectN = N;
    p[0] = red;
    p[1] = black;
    nWinner = 5; //Arbitrary number to not represent global constants
    whoseTurn = 0;
}

bool GameImpl::completed(int& winner) const
{
    //Return false is game just started
    if (s.numberEmpty() == s.cols()*s.levels())
    {
        return false;
    }
    //Use helper function to determine if game is won
    if (completedHelper(s, connectN, moveCol))
    {
        int row = s.levels();
        while (s.checkerAt(moveCol, row) == VACANT)
        {
            row--;
        }
        winner = s.checkerAt(moveCol, row);
        return true;
    }
    else if (s.numberEmpty() == 0)
    {
        winner = TIE_GAME;
        return true;
    }
    else
    {
        return false;
    }
}

bool GameImpl::takeTurn()
{
    //Check if game is won using completed
    if (completed(nWinner))
    {
        return false;
    }
    //Make new move depending on whose turn it is
    s.makeMove(p[whoseTurn]->chooseMove(s, connectN, whoseTurn), whoseTurn);
    //Assign new last move column
    moveCol = s.undoMove();
    s.makeMove(moveCol, whoseTurn);
    //Assign new value to determine whose turn it is on
    if (whoseTurn == 0)
    {
        whoseTurn++;
    }
    else
    {
        whoseTurn--;
    }
    return true;
}

void GameImpl::play()
{
    //Determine if press enter is needed
    bool notInter = false;
    if (!p[0]->isInteractive() && !p[1]->isInteractive())
    {
        notInter = true;
    }
    int counter = 1;
    //Initial screen display
    cout<<"Connect "<<connectN<<" to win!"<<endl;
    s.display();
    
    cout<<p[whoseTurn]->name()<<" goes first."<<endl;
    //Keeps looping until game is over
    while (takeTurn())
    {
        s.display();
        if (whoseTurn == 0)
        {
            cout<<p[whoseTurn+1]->name()<<" has moved."<<endl;
        }
        else
        {
            cout<<p[whoseTurn-1]->name()<<" has moved."<<endl;
        }
        //Prompt user to press enter every 3 moves
        if (counter % 3 == 0 && notInter == true)
        {
            cout<<"Press ENTER to continue.";
            cin.ignore(10000,'\n');
        }
        counter++;
    }
    if (nWinner != TIE_GAME)
    {
        cout<<p[nWinner]->name();
    }
    else
    {
        cout<<"Nobody";
    }
    cout<<" won the game!"<<endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return (s.checkerAt(c, r));
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
