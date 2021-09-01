#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int N;
int cnt;
array<int, 15> position; // array�� ���Ҵ� �ش� col�� queen�� ��ġ�� row��
						// position[1] = 14���, ù��° ���� ��ġ�� row = 14, col = 1

bool canPut(int row, int col, int nQueens) {
	for (int i = 1; i <= nQueens; i++) {
		if (position[i] == row || abs(row - position[i]) == abs(col - i)) {
			return false;
		}
	}
	return true;
}

void dfs(int nQueens) {
	if (nQueens == N) {
		cnt++;
		return;
	}
	for (int i = 1; i <= N; i++) { // col
		if (position[i] == 0) { // ���� ��ġ���� ���� col ã��
			for (int j = 1; j <= N; j++) { // �̹� ��ġ�� queen��� ���� �Ұ����� rowã��
				if (canPut(j, i, nQueens)) { // ���� ���� �� �ִٸ�
					position[i] = j; // �� ����					
					dfs(nQueens+1);
					position[i] = 0;
				}
				
			}
			return;
		}		
	}
}

int main() {	
	cin >> N;
	dfs(0);	
	cout << cnt << endl;
}