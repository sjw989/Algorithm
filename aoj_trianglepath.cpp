#include <iostream>
#include <vector>
using namespace std;

int C; // tc 개수
int n; // 삼각형 사이즈
int maximum;
int board[101][101];
int memo[101][101];
vector<int> result;


void input() {
	cin >> n;
	int i = 1;
	while (i <= n) {
		for (int j = 1; j <= i; j++) {
			cin >> board[i][j];
		}
		i++;
	}
}

void solve(int row, int col, int add) {
	add += board[row][col];

	if (row == n) {
		maximum = max(maximum, add);
		return;
	}

	if (add <= memo[row][col]) {
		return;
	}
	else {
		solve(row + 1, col, add);
		solve(row + 1, col + 1, add);
		memo[row][col] = add;
	}
}


void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

int main() {

	cin >> C;
	for (int i = 0; i < C; i++) {
		maximum = 0;
		input();
		solve(1, 1, 0);
		result.push_back(maximum);
		for (int row = 1; row <= 100; row++) {
			for (int col = 1; col <= 100; col++) {
				board[row][col] = 0;
				memo[row][col] = 0;
			}
		}
	}
	print();

}