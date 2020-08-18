#include <bits/stdc++.h>

using namespace std;

bool comp(const pair<char, pair<int, int>> &player1, const pair<char, pair<int, int>> &player2){
    int dist_1 = player1.second.first;
    int dist_2 = player2.second.first;
    int last_jump_1 = player1.second.second;
    int last_jump_2 = player2.second.second;

    if (dist_1 == dist_2 && last_jump_1 == last_jump_2)
        return player1.first < player2.first;

    if (dist_1 == dist_2)
        return last_jump_1 < last_jump_2;
    
    return dist_1 < dist_2;
}

bool allow(int n, int m, int x, int y){
    if (x > n-1 || x < 0) return false;
    if (y > m-1 || y < 0) return false;
    return true;
}

pair<int, int> BFS(pair<int, int> source, vector<vector<int>> board){
    int n, m;

    pair<int, int> ans = {-1, -1};

    n = board.size();
    n > 0 ? m = board[0].size() : m = 0;

    if (n == 0 || m == 0)
        return ans; 

    vector <pair<int, int>> move = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    vector <vector<bool>> visited(n, vector<bool>(m, false));
    vector <vector<int>> distance(n, vector<int>(m, 0));
    vector <vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));

    queue <pair<int, int>> q;

    q.push(source);

    visited[source.first][source.second] = true;
    distance[source.first][source.second] = 0;

    parent[source.first][source.second] = {-1, -1};

    if (source.first == n-1 && source.second == m-1)
        return {0, 0};

    while (!q.empty()){
        pair<int, int> v = q.front();
        q.pop();

        int v_i = v.first;
        int v_j = v.second;

        int dist = distance[v_i][v_j];

        if (v_i == n-1 && v_j == m-1){
            int previous_i = parent[v_i][v_j].first;
            int previous_j = parent[v_i][v_j].second;

            if (previous_i == -1 && previous_j == -1)
                return {dist, 0};

            int lst_i = parent[previous_i][previous_j].first;
            int lst_j = parent[previous_i][previous_j].second;

            int last_jump = board[lst_i][lst_j];

            ans = {dist, last_jump};

            return ans;
        }

        int jump = board[v_i][v_j];

        if (jump == 0) continue;

        for (pair<int, int> u : move){
            int nx = v_i  + (jump * u.first);
            int ny = v_j  + (jump * u.second);

            if (allow(n, m, nx, ny) && visited[nx][ny] == false){
                visited[nx][ny] = true;
                distance[nx][ny] = dist + 1;
                q.push({nx, ny});
                parent[nx][ny] = {v_i, v_j};
            }
        }
    }

    return {-1, -1};
}

int main(){
    int N, M; cin >> N >> M;
    vector <vector<int>> board(N, vector<int>(M));
    vector <pair<char, pair<int, int>>> players;

    int P; cin >> P;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> board[i][j];

    char tag = 'A';

    for (int i = 0; i < P; i++, tag++){
        int x, y; cin >> x >> y;
        players.push_back({tag, {x, y}});
    }

    vector <pair<char, pair<int, int>>> winners;

    for (int i = 0; i < P; i++){
        pair <int, int> source = players[i].second;
        pair <int, int> result = BFS(source, board);
        if (result.first != -1 && result.second != -1){
            winners.push_back({players[i].first, result});
        }
    }

    sort(winners.begin(), winners.end(), comp);

    if (winners.size() == 0)
        cout << "SEM VENCEDORES" << endl;
    else
        cout << winners[0].first << endl << winners[0].second.first << endl;
  
    return 0;
}
