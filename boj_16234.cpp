#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <iomanip>
#define pii pair<int,int>
using namespace std;

int N; // N x N
int L, R; // 인구 제한 L <= 인구 차 <= R
int days; // 인구이동이 일어난 날 수
bool is_moved = false;
array<array<int, 51>, 51> board;
array<array<int, 51>, 51> union_board;
array<array<int, 51>, 51> new_board;
array<array<int, 51>, 51> moved_check;
array<array<int, 51>, 51> visit;
array<int, 4> drow = {1,-1,0,0};
array<int, 4> dcol = {0,0,1,-1};

void input() {
	//ifstream in("test.txt");
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}	
}

void make_union(int cnt, int start_row, int start_col) {		
	queue<pii> q; // bfs돌릴 q
	q.push(make_pair(start_row, start_col)); // 연합만들기 시작지점
	visit = { 0, }; 	
	visit[start_row][start_col] = 1; // 시작지점 visit처리
	union_board[start_row][start_col] = cnt; // union_board 

	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];						
			if (next_row >= 1 && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] != 1 ) { // 방문가능한 경우												
				int differ = abs(board[cur.first][cur.second] - board[next_row][next_col]); // 인구 차이

				if (L <= differ && differ <= R) { // 인구이동이 가능한 경우					
					visit[next_row][next_col] = 1; // 방문처리
					union_board[cur.first][cur.second] = cnt;
					union_board[next_row][next_col] = cnt; // 연합 번호 표시					
					q.push(make_pair(next_row, next_col));
				}
			}
		}
	}

}

void move_population(int row, int col, int union_num) {
	queue<pii> q;
	q.push(make_pair(row, col));
	visit = { 0, };
	visit[row][col] = 1; // 시작지점 visit처리
	vector<pii> union_list;
	union_list.push_back(make_pair(row, col));

	int sum = board[row][col]; // 연합끼리의 인구수 합
	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];

			if (next_row >= 1 && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] != 1) {
				if (union_board[next_row][next_col] == union_num) { // 연합 번호가 같으면
					is_moved = true;
					union_list.push_back(make_pair(next_row, next_col)); // 연합 리스트에 추가
					visit[next_row][next_col] = 1; // 방문처리
					q.push(make_pair(next_row, next_col)); // q에 추가
					sum += board[next_row][next_col]; // 연합 총 인구수 + 해줌
				}
			}
		}
	} // union_list 만들기

	for (pii u : union_list) { // 인구이동 시켜주기
		new_board[u.first][u.second] = sum / union_list.size();
		moved_check[u.first][u.second] = 1;
	}

}

void solve() {
	queue<pii> q;
	q.push(make_pair(1, 1));	
	while (true) {				
		is_moved = false;
		union_board = { 0, };
		moved_check = { 0, };

		int cnt = 1; // 연합 번호
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (union_board[i][j] == 0) { // 아직 연합이 없는 칸을 찾으면					
					make_union(cnt, i, j); // 연합만들기					
					cnt++; // 연합번호 +1					
				}				
			}
		} // 국경개방하고 연합만들기 		
		

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) { // 인구이동 시키기
				if (moved_check[i][j] == 0) { // 아직 인구이동을 하지 않은 칸
					move_population(i, j, union_board[i][j]);
				}
			}			
		}		
		if (is_moved) { // 여러 연합중 인구이동이 한 번이라도 일어났으면
			board = new_board; // 인구이동 후 board 업데이트
			days++; // 인구이동 후 날짜 +1
		}		
		else {
			return;
		}

	}
}
void print() {
	cout << days << endl;	
}

int main() {
	input();
	solve();
	print();

}