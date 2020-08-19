#ifndef GAME_GAME_TP
#define GAME_GAME_TP

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm> 
#include <utility>

using namespace std;

pair<int, int> simulate_game(pair<int, int> source, vector<vector<int>> board);
bool allow_move(int n, int m, int x, int y);
bool rank_players(const pair<char, pair<int, int>> &player1, const pair<char, pair<int, int>> &player2);

#endif
