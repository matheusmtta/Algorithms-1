#include "includes/game.h"

using namespace std;

//Haja vista que não podemos ter empates devemos ordenar
//os potenciais vencedores de acordo com:
//1) distância percorrida (número de saltos)
//2) ordem de jogadas na rodada vencedora
//3) ordem lexicográfica
bool rank_players(const pair<char, pair<int, int>> &player1, const pair<char, pair<int, int>> &player2){
    char name1 = player1.first;
    char name2 = player2.first;
    int dist_1 = player1.second.first;
    int dist_2 = player2.second.first;
    int last_jump_1 = player1.second.second;
    int last_jump_2 = player2.second.second;

    //Caso condições 1) e 2) sejam iguais, devemos ordenar
    //de acordo com a ordem lexicografica
    if (dist_1 == dist_2 && last_jump_1 == last_jump_2)
        return name1 < name2;

    //Caso a distância percorrida seja igual, aquele que
    //jogou primeiro vence
    if (dist_1 == dist_2)
        return last_jump_1 < last_jump_2;
    
    //O jogador que percorreu a menor distância é o vencedor
    return dist_1 < dist_2;
}





//Verifca se o movimento que será realizado
//está dentro das restrições de tamanho da
//matriz que representa o tabuleiro do jogo
bool allow_move(int n, int m, int x, int y){
    if (x > n-1 || x < 0) return false;
    if (y > m-1 || y < 0) return false;
    return true;
}




//Essa função irá reduzir o problema do jogo do pulo em problema de caminhamento 
//em grafos, onde as entradas da matriz serão os vértices e seus potenciais
//pulos as arestas do grafo.
pair<int, int> simulate_game(pair<int, int> source, vector<vector<int>> board){
    //obtemos as dimensões do tabuleiro
    int n, m;

    n = board.size();
    n > 0 ? m = board[0].size() : m = 0;

    //inicializa a variavel de resposta
    //com um valor que será descartado
    //caso uma resposta válida não seja
    //encontrada
    pair<int, int> ans = {-1, -1};

    //checa a existência do tabuleiro
    if (n == 0 || m == 0)
        return ans; 

    //define o vetor de movimentos do jogador no tabuleiro
    vector <pair<int, int>> move = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    //vetores auxiliares que serão usados para manipular a busca 
    //ótima ao vértice {n-1, m-1}, mantendo a informação dos vértices
    //já pesquisados
    vector <vector<bool>> visited(n, vector<bool>(m, false));
    vector <vector<int>> distance(n, vector<int>(m, 0));
    vector <vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));

    //define a fila de pesquisa que irá guiar
    //a busca ótima
    queue <pair<int, int>> q;

    //adiciona o vértice fonte do jogador
    q.push(source);

    //inicializa os vetores auxiliares com casos base
    //para o vértice fonte
    visited[source.first][source.second] = true;
    distance[source.first][source.second] = 0;

    //Como é o primeiro, ele não possui um vértice pai
    parent[source.first][source.second] = {-1, -1};

    //Caso o vértice já seja a resposta, apenas retornarmos
    if (source.first == n-1 && source.second == m-1){
        ans = {0, 0};
        return ans;
    }


    //Enquanto houver algum vértice descoberto, com a adjacência
    //ainda não pesquisada
    while (!q.empty()){
        //Seja v o vértice a ter a adjacência pesquisada
        pair<int, int> v = q.front();
        q.pop();

        //Definimos suas coordenadas no tabuleiro
        int v_i = v.first;
        int v_j = v.second;

        //Distância percorrida até v
        int dist = distance[v_i][v_j];

        //Caso a coordenada de v seja igual a {n-1, m-1}, temos
        //nossa condição de parada
        if (v_i == n-1 && v_j == m-1){
            //Obtemos as coordenadas do pai de v, para ter informação
            //acerca de sua prioridade de jogada na rodada vencedora
            int previous_i = parent[v_i][v_j].first;
            int previous_j = parent[v_i][v_j].second;

            //Para isso precisamos de saber o valor associado ao vértice
            //que levou o jogador até a célula anterior a célula {n-1, m-1}
            int lst_i = parent[previous_i][previous_j].first;
            int lst_j = parent[previous_i][previous_j].second;

            //Consideramos o caso no qual o vértice anterior é
            //o vértice inicial
            if (lst_i == -1 && lst_j == -1)
                return {dist, 0};

            int last_jump = board[lst_i][lst_j];

            //Retornamos a distância percorrida e o pulo que define
            //a prioridade do jogador na rodada em que ele vence
            ans = {dist, last_jump};

            return ans;
        }

        int jump = board[v_i][v_j];

        if (jump == 0) continue;


        //Testamos os 4 potenciais pulos a partir da entrada {v_i, v_j},
        //i.e, pesquisamos a adjacência de v
        for (pair<int, int> u : move){
            int nx = v_i  + (jump * u.first);
            int ny = v_j  + (jump * u.second);

            //checa se é possível saltar para o vértice {nx, ny} e se
            //{nx, ny} ainda não foi visitado.
            if (allow_move(n, m, nx, ny) && visited[nx][ny] == false){
                visited[nx][ny] = true;
                distance[nx][ny] = dist + 1;
                q.push({nx, ny});
                parent[nx][ny] = {v_i, v_j};
            }
        }
    }

    //Não há mais vértices para serem pesquisados,
    //o jogador não alcança o vértice {n-1, m-1}
    return ans;
}