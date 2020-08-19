#include "includes/game.h"

using namespace std;

int main(){
    int N, M; 

    cin >> N >> M;

    vector <vector<int>> board(N, vector<int>(M));
    vector <pair<char, pair<int, int>>> players;

    int P; 

    cin >> P;

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
        pair <int, int> result = simulate_game(source, board);
        if (result.first != -1 && result.second != -1){
            winners.push_back({players[i].first, result});
        }
    }

    sort(winners.begin(), winners.end(), rank_players);

    if (winners.size() == 0)
        cout << "SEM VENCEDORES" << endl;
    else
        cout << winners[0].first << endl << winners[0].second.first << endl;
  
    return 0;
}
