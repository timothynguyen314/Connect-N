// Game.cpp

#include "interface.h"
#include "support.h"
#include <vector>
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
    ~GameImpl();
private:
    Scaffold* m_game;
    Player* r_sauce;
    Player* b_sauce;
    
    int goal;
    int last;
    int turn;
    int win;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    r_sauce = red;
    b_sauce = black;
    goal = N;
    last = -1;
    m_game = new Scaffold(nColumns, nLevels);
    
    turn = BLACK;
}

GameImpl::~GameImpl()
{
    delete m_game;
}

bool GameImpl::completed(int& winner) const
{
    if(last == -1)
        return false;
    
    if (victory(m_game, last, goal, turn))
    {
        winner = turn;
        return true;
    }
    
    if(m_game->numberEmpty() == 0)
    {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
}

bool GameImpl::takeTurn()
{
    if(completed(win))
        return false;
    
    if(turn)
    {
        cout << r_sauce->name() << "\'s turn (RED)" << endl;
        last = r_sauce->chooseMove(*m_game, goal, RED);
        m_game->makeMove(last, RED);
        turn = RED;
    }
    else
    {
        cout << b_sauce->name() << "\'s turn (BLACK)" << endl;
        last = b_sauce->chooseMove(*m_game, goal, BLACK);
        m_game->makeMove(last, BLACK);
        turn = BLACK;
    }
    
    return true;
}

void GameImpl::play()
{
    m_game->display();
    
    
    if(!r_sauce->isInteractive() && !b_sauce->isInteractive()) //if both are computers
        while(takeTurn())
        {
            m_game->display();
            cout << "Hit enter to continue" << endl;
            cin.ignore(1000, '\n');
        }
    else
        while(takeTurn())
            m_game->display();
    
    if(win == RED)
        cout << "RED wins" << endl;
    else if(win == BLACK)
        cout << "BLACK wins" << endl;
    else if(win == TIE_GAME)
        cout << "TIE game" << endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return m_game->checkerAt(c, r);
}

//******************** Game functions *******************************


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
