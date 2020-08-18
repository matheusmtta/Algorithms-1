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

//just check if the vertex to be visited is 
//within the board dimensions constraints
bool allow(int n, int m, int x, int y){
    if (x > n-1 || x < 0) return false;
    if (y > m-1 || y < 0) return false;
    return true;
}

pair<int, int> BFS(pair<int, int> source, vector<vector<int>> board){
    //define board dimensions
    int n, m;

    pair<int, int> ans = {-1, -1};

    n = board.size();
    n > 0 ? m = board[0].size() : m = 0;

    if (n == 0 || m == 0)
        return ans; 

    //movement vector
    vector <pair<int, int>> move = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    //auxiliary vectors to keep track of already computed subproblems answers
    vector <vector<bool>> visited(n, vector<bool>(m, false));
    vector <vector<int>> distance(n, vector<int>(m, 0));
    vector <vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));

    //define the search queue
    queue <pair<int, int>> q;

    //add the initial vertex at our queue
    q.push(source);

    //initialize the base case for each vector in function
    //of our source vertex
    visited[source.first][source.second] = true;
    distance[source.first][source.second] = 0;

    //Since it is the first one, it doesnt have a parent
    parent[source.first][source.second] = {-1, -1};

    if (source.first == n-1 && source.second == m-1)
        return {0, 0};

    //while we still have a matrix cell to search
    while (!q.empty()){
        //let v be the current search vertex
        pair<int, int> v = q.front();
        q.pop();

        int v_i = v.first;
        int v_j = v.second;

        int dist = distance[v_i][v_j];

        //We reached our answer
        if (v_i == n-1 && v_j == m-1){
            int previous_i = parent[v_i][v_j].first;
            int previous_j = parent[v_i][v_j].second;

            //The cell before the winning one is the source
            //of player_i, then if there's a tie the ordering
            //will be defined lexicographically
            if (previous_i == -1 && previous_j == -1)
                return {dist, 0};


            //get the cell that defines the ordering, i.e, the
            //cell value that defines the order of the round
            //before the last one. 
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

            //check if it is feasible to jump to nx, ny
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
