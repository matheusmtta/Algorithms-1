#include <bits/stdc++.h>

using namespace std;

#define INF (int)0x3f3f3f3f
#define MAX_W 17000
#define MAX_N 260

vector <int> diamonds;
int memo[MAX_N][MAX_W], n, total;

int solve(){
	memset(memo, 0, sizeof memo);

	for (int i = 0; i <= total/2; i++)
		memo[0][i] = i - diamonds[0] >= 0 ? diamonds[0] : 0;

	for (int i = 1; i < n; i++){
		for (int j = 0; j <= total/2; j++){
			int skip = memo[i-1][j];
			int take = j - diamonds[i] >= 0 ? diamonds[i] + memo[i-1][j - diamonds[i]] : -INF;
			memo[i][j] = max(take, skip);
		}
	} 

	return total - 2*memo[n-1][total/2];
}

int main(int argc, char* argv[]){
    if (argc <= 1)
        exit(0);

    ifstream input;
    input.open(argv[1]);

    input >> n;
	
	diamonds.resize(n);

	for (int &x : diamonds){
		input >> x;
		total += x;
	}

	int ans = solve();

	cout << ans << endl;

	return 0;
}