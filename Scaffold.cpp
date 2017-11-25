// Scaffold.cpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>

#include "interface.h"
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
    int m_cols;
    int m_levels;
    int emptyNum;
    
    vector <vector<int>> scaffold;
    stack <int> c_history;
    stack <int> l_history;
    
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if(nColumns > 0 && nLevels > 0)
    {
        m_cols = nColumns;
        m_levels = nLevels;
        
        emptyNum = nColumns * nLevels;
        
        scaffold.resize(m_cols);
        for(int i = 0; i < m_cols; i++)
            scaffold[i].resize(m_levels, VACANT);
    }
    else
        exit(1);
}

int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    return emptyNum;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    column--;
    level--;
    
    if(column >= cols() || column < 0 || level >= levels() || level < 0)
        return VACANT;
    
    if(scaffold[column][level] == RED || scaffold[column][level] == BLACK)
        return scaffold[column][level];
    else
        return VACANT;
}

void ScaffoldImpl::display() const
{
    //displays the scaffold
    for(int i = m_levels - 1; i > -1; i--)
    {
        cout << "|";
        for(int j = 0; j < m_cols; j++)
        {
            if(scaffold[j][i] == RED)
                cout << "R";
            else if(scaffold[j][i] == BLACK)
                cout << "B";
            else if(scaffold[j][i] == VACANT)
                cout << " ";
            cout << "|";
        }
        cout << endl;
    }
    
    //bottom row
    cout << "+";
    for(int i = 0; i < m_cols; i++)
        cout << "-+";
    
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    //makes a move
    if(column > 0 && column <= m_cols)
    {
        column--;
        int i = 0;
        
        for(; i < m_levels; i++)
            if(scaffold[column][i] == VACANT)
                break;
        
        if(i == m_levels)
            return false; //column full
        
        if(color == RED || color == BLACK)
            scaffold[column][i] = color;
        else
            return false; //invalid color
        
        c_history.push(column);
        l_history.push(i);
        
        emptyNum--;
        return true;
    }
    else
        return false; //column out of bounds
}

int ScaffoldImpl::undoMove()
{
    //undos most recent addition
    if(emptyNum == m_cols * m_levels)
        return 0; //scaffold empty
    else
    {
        int c_top = c_history.top();
        
        scaffold[c_history.top()][l_history.top()] = VACANT;
        
        c_history.pop();
        l_history.pop();
        
        emptyNum++;
        return c_top;
    }
}

//******************** Scaffold functions *******************************

Scaffold::Scaffold(int nColumns, int nLevels) //done
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

int Scaffold::cols() const //done
{
    return m_impl->cols();
}

int Scaffold::levels() const //done
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
