#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

int n;
unsigned int dp[3000][3001], ans = 1;
pair <int, int> cycles[3000];
vector <vector <int>> child;

unsigned int dfs(int v) {
	if (child[v].empty()) {
		for (int i = 0; i <= cycles[v].second; i++) {dp[v][i] = 1;}
	} 
	else {
		for (int i : child[v]) {
			dfs(i);
		}
	}
	for (int i = cycles[v].second + 1; i <= 3000; i++) {dp[v][i] = 0;}
	unsigned int s = 0;
	for (int i = 3000; i >= 0; i--) {
		s += dp[v][i];
		if (cycles[v].first < 0) {
			dp[-cycles[v].first-1][i] *= s;
		}
		if (i == cycles[v].first) {
			return s;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= 3000; j++) {
			dp[i][j] = 1;
		}
	}
	child.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> cycles[i].first >> cycles[i].second;
		if (cycles[i].first < 0) {
			child[-cycles[i].first-1].push_back(i);
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (cycles[i].first >= 0) {
			ans *= dfs(i);
		}
	}
	cout << ans;

	return 0;
}