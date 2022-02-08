#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int N; // 집의 개수
int ans; // 정답
array<array<int, 3>, 1001> dp;
array<array<int, 3>, 1001> cost;

void input() {
	//ifstream in("test.txt");
	cin >> N;		
	for (int i = 1; i <= N; i++) {		
		for (int j = 0; j < 3; j++) {
			cin >> cost[i][j];
		}		
	}
}

void solve() {
	dp[1] = cost[1];
	for (int i = 2; i <= N; i++) {
		dp[i][0] = cost[i][0] + min(dp[i - 1][1], dp[i - 1][2]);
		dp[i][1] = cost[i][1] + min(dp[i - 1][0], dp[i - 1][2]);
		dp[i][2] = cost[i][2] + min(dp[i - 1][0], dp[i - 1][1]);
	}
	ans = min(dp[N][0], min(dp[N][1], dp[N][2]));
}

void print() {
	cout << ans;
}
int main() {
	input();
	solve();
	print();
}