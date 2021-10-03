#include <iostream>
#include <fstream>
#include <array>
#define MAX 2188
using namespace std;

int N; // 행렬 사이즈
int arr[MAX][MAX]; // 최대크기 2187x2187
array<int, 9> drow = {0, 0, 0, 1, 1, 1, 2, 2, 2 };
array<int, 9> dcol = {0, 1, 2, 0, 1, 2, 0, 1, 2 };
array<int, 3> ans = { 0,0,0 }; // 정답 -1, 0, 1


void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

bool can_use(int start_row, int start_col, int n) {	
	int ans = arr[start_row][start_col]; // 처음값
	for (int i = start_row; i <= start_row + n - 1; i++) {
		for (int j = start_col; j <= start_col + n - 1; j++) {
			if (ans != arr[i][j]) { // 다른 숫자가 등장할 시 
				return false; // 사용 불가능
			}
		}	
	}
	return true; // 사용 가능
}

void divide_conquer(int start_row, int start_col, int n) {	
	if (can_use(start_row,start_col,n)) {
		if (arr[start_row][start_col] == -1) {
			ans[0]++;
		}
		else if (arr[start_row][start_col] == 0) {
			ans[1]++;
		}
		else {
			ans[2]++;
		}
		return;
	}
	for (int i = 0; i < 9; i++) {
		divide_conquer(start_row + n/3 * drow[i], start_col + n/3 * dcol[i], n / 3);
	}	
}

void print() {
	for (int i = 0; i < 3; i++) {
		cout << ans[i] << endl;
	}
}

int main() {
	input();
	divide_conquer(1,1,N);	
	print();	
}