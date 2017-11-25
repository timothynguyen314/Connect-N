// Player.cpp

#include "interface.h"
#include "support.h"
#include <iostream>
#include <cmath>
using namespace std;

//HUMAN PLAYER

class HumanPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty() == 0)
        return -1;
    int col = -1;
    
    //repeats prompting for move until valid col is inputted
    while(col < 1 || col > s.cols() || s.checkerAt(col, s.levels()) != VACANT)
    {
        cout << "Choose column: ";
        cin >> col;
    }
    
    return col;
}

//BAD PLAYER
//AI, makes random moves

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty() == 0)
        return -1;
    
    int col = rand()%s.cols() + 1;
    
    //repeats prompting for move until valid col is inputted
    while(s.checkerAt(col, s.levels()) != VACANT)
        col = rand()%s.cols() + 1;
    
    return col;
}

//SMART PLAYER
//AI, makes best possible move

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty() == 0)
        return -1;
    
    Scaffold sc = s;
    map<int, int> score;
    score =  smartcol(&sc, N, color, 1);
    
    map<int, int>::iterator it = score.end();
    it--;
    return it->second;
}

//******************** Player derived class functions *************************

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
