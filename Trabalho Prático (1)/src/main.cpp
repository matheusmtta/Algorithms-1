#include "includes/game.h"

#define INF (int)0x3f3f3f3f

using namespace std;

int main(){
	//Recebemos os valores de entrada e definimos
	//a matriz/grafo que será usada como tabuleiro
    int N, M; 

    cin >> N >> M;

    cout << N << " " << M << endl;

    //Checamos a validade da entrada
    if (N <= 0 || M <= 0) 
    	exit(0);

    //Definimos a matriz tabuleiro e o vetor de jogadores
    //definido por {nome, {coord i, coord j}}
    vector <vector<int>> board(N, vector<int>(M));
    vector <pair<char, pair<int, int>>> players;

    int P; 

    cin >> P;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> board[i][j];

    //Inicializamos a tag para o primeiro jogador
    //como A, e associamos a cada um deles uma tag
    //na ordem lexicografica de A...Z, o que é garantido 
    //pela especificação para P <= 11
    char tag = 'A';

    for (int i = 0; i < P; i++, tag++){
        int x, y; cin >> x >> y;
        players.push_back({tag, {x, y}});
    }

    //Definimos um vetor de potenciais vencedores
    vector <pair<char, pair<int, int>>> winners;

    for (int i = 0; i < P; i++){
    	//Simulamos o processo do jogo para cada jogador
        pair <int, int> source = players[i].second;
        pair <int, int> result = simulate_game(source, board);
        if (result.first != INF && result.second != INF){
        	//Caso o resultado seja válido, i.e, result != {INF, INF}
        	//adicionamos a resposta ao vetor de vencedores
            winners.push_back({players[i].first, result});
        }
    }

    //Ordenamos o vetor de potenciais vencedores em função
    //dos critérios de desempate
    sort(winners.begin(), winners.end(), rank_players);

    if (winners.size() == 0)
        cout << "SEM VENCEDORES" << endl;
    else
        cout << winners[0].first << endl << winners[0].second.first << endl;
  
    return 0;
}
