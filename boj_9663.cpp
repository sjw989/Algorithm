#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int N;
int cnt;
array<int, 15> position; // array의 원소는 해당 col의 queen이 위치한 row값
						// position[1] = 14라면, 첫번째 퀸의 위치는 row = 14, col = 1

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
		if (position[i] == 0) { // 아직 배치되지 않은 col 찾기
			for (int j = 1; j <= N; j++) { // 이미 배치된 queen들과 공격 불가능한 row찾기
				if (canPut(j, i, nQueens)) { // 퀸을 놓을 수 있다면
					position[i] = j; // 퀸 놓기					
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