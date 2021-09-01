#include <iostream>
#include <fstream>
#include <array>
using namespace std;

array<array<int, 10>, 10> board;
int emptyNum = 0;

void input() {
	//ifstream in("test.txt");
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {			
			cin >> board[i][j];
			if (board[i][j] == 0) {
				emptyNum++;
			}
		}
	}
}

bool can_inputNum(int row, int col, int k) {
	for (int i = 1; i <= 9; i++) {
		if (board[row][i] == k || board[i][col] == k) {
			return false;
		}
	} // °¡·Î¼¼·Î °Ë»ç
	
	// 3x3 °Ë»ç
	if (row >= 1 && row <= 3) {
		row = 1;
	}
	else if (row <= 6) {
		row = 4;
	}
	else if (row <= 9) {
		row = 7;
	}
	if (col >= 1 && col <= 3) {
		col = 1;
	}
	else if (col <= 6) {
		col = 4;
	}
	else if (col <= 9) {
		col = 7;
	}

	for (int i = row; i <= row + 2; i++) {
		for (int j = col; j <= col + 2; j++) {
			if (board[i][j] == k) {
				return false;
			}
		}
	}
	return true;
}
void print() {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

int dfs() {		
	if (emptyNum == 0) {		
		return 1;
	}
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (board[i][j] == 0) { // ºóÄ­ Ã£±â
				for (int k = 1; k <= 9; k++) {
					if (can_inputNum(i,j,k)) { // k¸¦ ±× ÀÚ¸®¿¡ ³ÖÀ» ¼ö ÀÖÀ¸¸é						
						board[i][j] = k;
						emptyNum--; // ºóÄ­ °³¼ö --
						if (dfs() == 0) {
							board[i][j] = 0;
							emptyNum++; // ºóÄ­ °³¼ö ++
						}
						else {
							return 1;
						}
						
					}
				}
				return 0;
			}			
		}
	}	
}


int main() {
	input();
	dfs();		
	print();
}