#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int N; // �� ������
int cnt;  // ����
array<array<int, 17>, 17> home;
array<array<array<int, 17>, 17>, 3> dp;

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
		case 0: // ���� �������� ���η� ���� ���												
			if (dp[state][row][col + 1] == 0) {
				if (col + 1 <= N && home[row][col + 1] == 0) { // ���� ����														
					dfs(row, col + 1, 0);					
				}
			}
						
			if (row + 1 <= N && col + 1 <= N && home[row + 1][col + 1] == 0
				&& home[row][col + 1] == 0 && home[row + 1][col] == 0) { // �밢�� ����
				dfs(row + 1, col + 1, 2);				
			}
			
			break;
		case 1: // ���� �������� ���η� ���� ���

			if (row + 1 <= N && home[row + 1][col] == 0) { // ���� ����
				dfs(row + 1, col, 1); {
				}
				if (row + 1 <= N && col + 1 <= N && home[row + 1][col + 1] == 0
					&& home[row][col + 1] == 0 && home[row + 1][col] == 0) { // �밢�� ����
					dfs(row + 1, col + 1, 2);
				}
				break;

		case 2:

			if (col + 1 <= N && home[row][col + 1] == 0) { // ���� ����
				dfs(row, col + 1, 0);
			}

			if (row + 1 <= N && home[row + 1][col] == 0) { // ���� ����

				dfs(row + 1, col, 1);
			}
			if (row + 1 <= N && col + 1 <= N && home[row + 1][col + 1] == 0
				&& home[row][col + 1] == 0 && home[row + 1][col] == 0) { // �밢�� ����				
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
