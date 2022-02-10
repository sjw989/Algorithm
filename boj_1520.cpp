#include <iostream>
#include <fstream>
#include <array>
#define MAX_SIZE 500+1
using namespace std;

int N, M;
array<array<int, MAX_SIZE>, MAX_SIZE> board;
array<array<int, MAX_SIZE>, MAX_SIZE> dp;
array<int, 4> drow = {1,-1,0,0};
array<int, 4> dcol = {0,0,1,-1};


void input() {
	//ifstream in("test.txt");
	cin >> M >> N;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

void dfs(int row, int col) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int next_row = row + drow[i];
		int next_col = col + dcol[i];

		if (next_row >= 1 && next_row <= M && next_col >= 1 && next_col <= N) {
			if (board[row][col] > board[next_row][next_col]) { // 다음 칸의 높이가 더 낮은 경우 전진
				
				if (dp[next_row][next_col] > 0) {
					cnt += dp[next_row][next_col];
					continue;
				}
				if (dp[next_row][next_col] == -1) {
					continue;
				}
				if (next_row == M && next_col == N) {
					cnt++;
					continue;
				}
				dfs(next_row, next_col);
				
				if (dp[next_row][next_col] > 0) {
					cnt += dp[next_row][next_col];
				}
			}
		}
	}
	if (cnt == 0) {
		dp[row][col] = -1;
	}
	else {
		dp[row][col] = cnt;
	}
	
}

void print() {
	if (dp[1][1] > 0) {
		cout << dp[1][1];
	}
	else {
		cout << 0;
	}
}

int main() {
	input();
	dp[M][N] = 1;
	dfs(1,1);
	print();
}