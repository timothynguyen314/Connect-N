#include "support.h"
#include <iostream>

bool victory(Scaffold* m_game, int col, int N, int turn)
{
    int connect = 0;
    
    //VERTICALLY
    int level = m_game->levels();
    for (int i = 1; i <= m_game->levels(); i++)
    {
        if(m_game->checkerAt(col, i) == turn)
            connect++;
        else if(m_game->checkerAt(col, i) == VACANT)
        {
            level = i - 1;
            break;
        }
        else
            connect = 0;
        
        if (connect == N)
            return true;
    }
    
    //HORIZONTALLY
    connect = 0;
    for(int i = 1; i <= m_game->cols(); i++)
    {
        if(m_game->checkerAt(i, level) == turn)
            connect++;
        else
            connect = 0;
        
        if (connect == N)
            return true;
    }
    
    //UPWARD DIAGONAL
    connect = 0;
    
    int diag_c, diag_l;
    if(level - col < 0)
    {
        diag_c = ((level - col) * -1) + 1;
        diag_l = 1;
    }
    else
    {
        diag_c = 1;
        diag_l = level - col + 1;
    }
    while(diag_c <= m_game->cols() && diag_l <= m_game->levels())
    {
        if(m_game->checkerAt(diag_c, diag_l) == turn)
            connect++;
        else
            connect = 0;
        
        if (connect == N)
            return true;
        
        diag_c++;
        diag_l++;
    }
    
    //DOWNWARD DIAGONAL
    connect = 0;
    
    if(level + col > m_game->levels())
    {
        diag_c = level + col - m_game->levels();
        diag_l = m_game->levels();
    }
    else
    {
        diag_c = 1;
        diag_l = col + level - 1;
    }
    while(diag_c <= m_game->cols() && diag_l > 0)
    {
        if(m_game->checkerAt(diag_c, diag_l) == turn)
            connect++;
        else
            connect = 0;
        
        if (connect == N)
            return true;
        
        diag_c++;
        diag_l--;
    }
    return false;
}

map<int, int> smartcol(Scaffold* m_game, int N, int turn, int t)
{
    //returns a map
    //first is the outcome value
    //second is the column associated with it
    //outcome value is 0 if results in neither win nor loss
    //outcome value is (numberEmpty + 1)*t otherwise
    //t is 1 when it's my turn, and -1 when it's my foe's turn
    
    map<int, int> score;
    vector<int> cols;
    
    for(int i = 1; i <= m_game->cols(); i++)
        if(m_game->makeMove(i, turn)) //if a move is possible
        {
            if(victory(m_game, i, N, turn)) //if it leads to win
            {
                //numberEmpty decreases with each turn.
                //we add 1 so that numberEmpty is not 0 in case of victory at end
                score[(m_game->numberEmpty() + 1) * t] = i;
                m_game->undoMove();
                return score;
            }
            else if(m_game->numberEmpty() == 0) //if it leads to tie
            {
                score[0] = i;
                m_game->undoMove();
                return score;
            }
            
            m_game->undoMove();
            cols.push_back(i);
        }
    
    //the cols vector contains columns that allow legal moves, but don't result in wins or ties
    vector<int>::iterator it = cols.begin();
    
    map<int, int> test;
    while(it != cols.end())
    {
        m_game->makeMove(*it, turn);
        test = smartcol(m_game, N, 1 - turn, t * -1);
        //if turn = RED = 0, 1 - turn = 1 - 0 = 1 = BLACK
        //if turn = BLACK = 1, 1 - turn = 1 - 1 = 0 = RED
        
        if(t < 0)
        {
            //foe turn, because t = -1
            //foe assumes worst case, i.e. most positive from me
            map<int, int>::iterator it2 = test.end();
            it2--;
            score[it2->first] = *it;
        }
        else
        {
            //my turn, because t = 1
            //we assume worst case, i.e. most negative from foe
            score[test.begin()->first] = *it;
        }
        
        test.clear();
        m_game->undoMove();
        it++;
    }
    return score;
}