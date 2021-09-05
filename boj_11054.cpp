#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int N; // 수열의 크기
int maximum; // 최대값
array<array<int, 1001>,2> sequence; // 0 -> 올바르게, 1-> 거꾸로
array<array<int, 1001>,2> dp; // 0 -> 올바르게, 1-> 거꾸로


void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int k;
		cin >> k;
		sequence[0][i] = k;
		sequence[1][N - i + 1] = k;
	}
}

void dfs(int direction, int start) {
	if (start == N) {
		dp[direction][start] = 1;
		return;
	}
	for (int i = start+1; i <= N; i++) {
		if (sequence[direction][start] > sequence[direction][i]) {
			if (dp[direction][i] == 0) {
				dfs(direction, i);
			}
			dp[direction][start] = max(dp[direction][start], dp[direction][i] + 1);
		}
		if (dp[direction][start] == 0) {
			dp[direction][start] = 1;
		}
	}	
}

int main() {
	input();
	for (int i = 1; i <= N; i++) {		
		dfs(0, i);
		dfs(1, i);
	}
	
	for (int i = 1; i <= N; i++) {		
		maximum = max(maximum, dp[0][i] + dp[1][N-i+1] - 1);
	} 
	cout << maximum;
}