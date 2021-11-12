#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <iomanip>
#define pii pair<int,int>
using namespace std;

int N; // N x N
int L, R; // �α� ���� L <= �α� �� <= R
int days; // �α��̵��� �Ͼ �� ��
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
	queue<pii> q; // bfs���� q
	q.push(make_pair(start_row, start_col)); // ���ո���� ��������
	visit = { 0, }; 	
	visit[start_row][start_col] = 1; // �������� visitó��
	union_board[start_row][start_col] = cnt; // union_board 

	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];						
			if (next_row >= 1 && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] != 1 ) { // �湮������ ���												
				int differ = abs(board[cur.first][cur.second] - board[next_row][next_col]); // �α� ����

				if (L <= differ && differ <= R) { // �α��̵��� ������ ���					
					visit[next_row][next_col] = 1; // �湮ó��
					union_board[cur.first][cur.second] = cnt;
					union_board[next_row][next_col] = cnt; // ���� ��ȣ ǥ��					
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
	visit[row][col] = 1; // �������� visitó��
	vector<pii> union_list;
	union_list.push_back(make_pair(row, col));

	int sum = board[row][col]; // ���ճ����� �α��� ��
	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];

			if (next_row >= 1 && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] != 1) {
				if (union_board[next_row][next_col] == union_num) { // ���� ��ȣ�� ������
					is_moved = true;
					union_list.push_back(make_pair(next_row, next_col)); // ���� ����Ʈ�� �߰�
					visit[next_row][next_col] = 1; // �湮ó��
					q.push(make_pair(next_row, next_col)); // q�� �߰�
					sum += board[next_row][next_col]; // ���� �� �α��� + ����
				}
			}
		}
	} // union_list �����

	for (pii u : union_list) { // �α��̵� �����ֱ�
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

		int cnt = 1; // ���� ��ȣ
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (union_board[i][j] == 0) { // ���� ������ ���� ĭ�� ã����					
					make_union(cnt, i, j); // ���ո����					
					cnt++; // ���չ�ȣ +1					
				}				
			}
		} // ���氳���ϰ� ���ո���� 		
		

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) { // �α��̵� ��Ű��
				if (moved_check[i][j] == 0) { // ���� �α��̵��� ���� ���� ĭ
					move_population(i, j, union_board[i][j]);
				}
			}			
		}		
		if (is_moved) { // ���� ������ �α��̵��� �� ���̶� �Ͼ����
			board = new_board; // �α��̵� �� board ������Ʈ
			days++; // �α��̵� �� ��¥ +1
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