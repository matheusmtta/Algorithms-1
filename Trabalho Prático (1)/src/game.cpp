#include "includes/game.h"

using namespace std;

pair<int, int> BFS(pair<int, int> source, vector<vector<int>> board){
  int n, m; //define board dimensions

  vector <pair<int, int>> move = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  n = board.size();
  n > 0 ? m = board[0].size() : return {-1, -1}; 

  vector <vector<int>> visited(n, vector<int>(m));
  vector <vector<pair<int, int>>> parent(n, vector<int>(m));
  queue <pair<pair<int, int>, int>> q;

  memset(visited, -1, sizeof visited);
  memset(parent, -1, sizeof parent);

  q.push({source, 0});
  visited[source.first][source.second] = true;
  p[source] = -1;

  while (!q.empty()){
    int v = q.front();
    q.pop();

    for (int u = 0; u < graph[v].size(); u++){
      if (!visited[graph[v][u]]){
        visited[graph[v][u]] = true;
        q.push(graph[v][u]);
        d[graph[v][u]] = d[v] + 1;
        p[graph[v][u]] = v;
      }
    }
  }
}

bool compare(const pair<char, pair<int, int>> &player1, 
             const pair<char, pair<int, int>> &player2){

}