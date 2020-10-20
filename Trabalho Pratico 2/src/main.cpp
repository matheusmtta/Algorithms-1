#include <vector>
#include <iostream>
#include <algorithm> 
#include <fstream>

using namespace std;

int solve(int total, vector <int> diamonds){
	//Definimos nosso vetor de memoização inicializado
	//com todas as entradas iguais a 0.
	vector <int> ans(total, 0);

	//Para cada elemento, extraimos qual é o máximo que
	//podemos obter de valor, i.e, peso de diamantes, com
	//uma capacidade j, adicionando ou não ou elemento
	for (int i = 0; i < (int)diamonds.size(); i++)
		for (int j = total/2; j - diamonds[i] >= 0; j--)
			ans[j] = max(ans[j], ans[j - diamonds[i]] + diamonds[i]);

	//Como demonstrado na documentação, obtemos a solução 
	//para o problema tomando D = S - 2B, onde S = total
	//e B o valor máximo obtido pela mochila
	return total - 2*ans[total/2];
}

int main(int argc, char* argv[]){
	//Recebemos os valores de entrada e definimos
	//a matriz/grafo que será usada como tabuleiro
    if (argc <= 1)
        exit(0);

    ifstream input;
    input.open(argv[1]);

    int n; 
    //Número de diamantes
    
    input >> n;
	vector <int> diamonds(n);
	int total = 0;

	//Adicionamos os diamantes a um vetor
	for (int &x : diamonds){
		input >> x;
		total += x;
	}

	//Computamos a resposta
	int ans = solve(total, diamonds);

	cout << ans << endl;

	return 0;
}