#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;

int T; // tc 개수
int l; // 체스판 사이즈 ㅣ x l
int cur_row, cur_col;
int dest_row, dest_col;
array<array<int, 300>, 300> board;
array<array<int, 300>, 300> visit;
array<int, 8> drow = {-2, -1, -2, -1, +1, +2, +1, +2};
array<int, 8> dcol = {-1, -2, +1, +2, +2, +1, -2, -1};
vector<int> result;


void init() {
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			board[i][j] = 0;
			visit[i][j] = 0;
		}
	}
}

void input() {
	init();
	cin >> l;
	cin >> cur_row >> cur_col;
	cin >> dest_row >> dest_col;
}

void bfs() {
	queue<pii> q;
	q.push(make_pair(cur_row, cur_col));
	board[cur_row][cur_col] = 0;
	visit[cur_row][cur_col] = 1;
	while (!q.empty()) {
		pii s = q.front();
		q.pop();
		for (int i = 0; i < 8; i++) {
			if (s.first + drow[i] < l && s.first + drow[i] >= 0
				&& s.second + dcol[i] < l && s.second + dcol[i] >= 0
				&& visit[s.first + drow[i]][s.second + dcol[i]] == 0) {
				q.push(make_pair(s.first + drow[i], s.second + dcol[i]));
				visit[s.first + drow[i]][s.second + dcol[i]] = 1;
				board[s.first + drow[i]][s.second + dcol[i]] = board[s.first][s.second] + 1;
			}
		}
	}
}

void print() {
	for (int ans : result) {
		cout << ans << "\n";
	}
}

int main() {	
	cin >> T;
	for (int i = 0; i < T; i++) {
		input();
		bfs();
		result.push_back(board[dest_row][dest_col]);		
	}
	print();
}