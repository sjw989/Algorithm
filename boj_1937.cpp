#include <iostream>
#include <fstream>
#include <array>
#define MAX_SIZE 500+1
using namespace std;

int N; // N x N
int ans;
array<int, 4> drow = { 1,-1,0,0 };
array<int, 4> dcol = { 0,0,1,-1 };
array<array<int, MAX_SIZE>, MAX_SIZE> forest;
array<array<int, MAX_SIZE>, MAX_SIZE> dp;


void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> forest[i][j];
		}
	}
}
void solve(int r, int c) {

	int pivot = forest[r][c];
	for (int i = 0; i < 4; i++) {
		int next_r = r + drow[i];
		int next_c = c + dcol[i];

		if (next_r >= 1 && next_r <= N && next_c >= 1 && next_c <= N
			&& pivot < forest[next_r][next_c]) {
			
			if (dp[next_r][next_c] == 0) {
				solve(next_r, next_c);
			}
			dp[r][c] = max(dp[r][c], dp[next_r][next_c] + 1);
		}
	}
	if (dp[r][c] == 0) {
		dp[r][c] = 1;
	}
}
void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ans = max(ans, dp[i][j]);
		}		
	}
	cout << ans;
}
int main() {
	input();
	for (int i = 1;  i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			solve(i,j);
		}
	}	
	print();
}



