#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int N; // 집 사이즈
int cnt;  // 개수
array<array<int, 17>, 17> home;

void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int k;
			cin >> k;
			home[i][j] = k;
		}
	}
}

void dfs(int row, int col, int state) {
	if (row == N && col == N) {		
		cnt++;
		return ;
	}
	switch (state) {		
		case 0: // 현재 파이프가 가로로 놓인 경우												

			if (col + 1 <= N && home[row][col + 1] == 0) { // 가로 진행														
				dfs(row, col + 1, 0);					
			}
			
						
			if (row + 1 <= N && col + 1 <= N && home[row + 1][col + 1] == 0
				&& home[row][col + 1] == 0 && home[row + 1][col] == 0) { // 대각선 진행
				dfs(row + 1, col + 1, 2);				
			}
			
			break;
		case 1: // 현재 파이프가 세로로 놓인 경우

			if (row + 1 <= N && home[row + 1][col] == 0) { // 세로 진행
				dfs(row + 1, col, 1); {
				}
				if (row + 1 <= N && col + 1 <= N && home[row + 1][col + 1] == 0
					&& home[row][col + 1] == 0 && home[row + 1][col] == 0) { // 대각선 진행
					dfs(row + 1, col + 1, 2);
				}
				break;

		case 2:

			if (col + 1 <= N && home[row][col + 1] == 0) { // 가로 진행
				dfs(row, col + 1, 0);
			}

			if (row + 1 <= N && home[row + 1][col] == 0) { // 세로 진행

				dfs(row + 1, col, 1);
			}
			if (row + 1 <= N && col + 1 <= N && home[row + 1][col + 1] == 0
				&& home[row][col + 1] == 0 && home[row + 1][col] == 0) { // 대각선 진행				
				dfs(row + 1, col + 1, 2);
			}
			break;
			}
	}	
}


int main() {
	input();
	dfs(1, 2, 0);
	cout << cnt << endl;
}
