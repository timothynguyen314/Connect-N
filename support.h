#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include "interface.h"
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

bool victory(Scaffold* m_game, int col, int N, int turn);
map<int, int> smartcol(Scaffold* m_game, int N, int turn, int t);
#endif