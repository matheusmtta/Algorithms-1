#include <bits/stdc++.h>

using namespace std;

#define INF (int)0x3f3f3f3f
#define MAX_W 100000
#define MAX_N 2600

vector <int> diamonds;
int memo[MAX_N][MAX_W], n, total = 0;

int solve(int idx, int capacity){
	if (capacity < 0) 
		return -INF;
	if (idx == n)
		return 0;

	int &curr = memo[idx][capacity];

	if (curr != -1)
		return curr;

	int skip = solve(idx+1, capacity);
	int take = diamonds[idx] + solve(idx+1, capacity - diamonds[idx]);

	return curr = max(skip, take);
}

int main(int argc, char* argv[]){
    if (argc <= 1)
        exit(0);

    ifstream input;
    input.open(argv[1]);

    input >> n;
	
    memset(memo, -1, sizeof memo);

    diamonds.resize(n);

	for (int &x : diamonds){
		input >> x;
		total += x;
	}

	int ans = solve(0, total/2);

	cout << total - 2*ans << endl;

	return 0;
}