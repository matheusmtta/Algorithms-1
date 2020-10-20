#include <bits/stdc++.h>

using namespace std;

//( value % 100 ) is in the range 0 to 99
//( value % 100 + 1 ) is in the range 1 to 100
//( value % 30 + 1985 ) is in the range 1985 to 2014

int main(int argc, char *argv[]){	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));

	if (argc <= 1)
		return 0;

	int N;
	N = atoi(argv[1]);
	cout << N << endl;

	for (int i = 0; i < N; i++)
		cout << rand()%51 + 1 << ' ';
	cout << endl;

	return 0;
}