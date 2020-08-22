#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]){	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));

	if (argc <= 1)
		return 0;

	int N, J;
	N = atoi(argv[1]);
	J = min(26, N);
	cout << N << " " << N << endl;
	cout << J << endl;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cout << rand()%N;
			j == N-1 ? cout << endl : cout << ' ';
		}
	}

	for (int i = 0; i < J; i++){
		cout << rand()%N << " " << rand()%N << endl; 
	}

	return 0;
}