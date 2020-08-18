#ifndef GAME_BFS_TP
#define GAME_BFS_TP

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm> 
#include <utility>

using namespace std;

pair<int, int> BFS(pair<int, int>, vector<vector<int>>);
bool compare(const pair<char, pair<int, int>>, const pair<char, pair<int, int>>);
bool allow(int n, int m, int x, int y);

#endif
