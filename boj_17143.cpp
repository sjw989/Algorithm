#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <map>
#include <vector>
#define pii pair<int,int>
using namespace std;

struct Shark {	
	pii pos;
	int size; // ũ��
	int dir; // ����
	int speed; // �ӵ�

};

int R, C, M;// R x C , M : ����� ��
int ans; // ���ÿ��� ���� ����� ũ�� ��
array<array<Shark, 101>, 101> board;
array<array<Shark, 101>, 101> new_board;
map<int, pii> delta = { {1,{-1,0}}, {-1,{1,0}}, {2,{0,-1}}, {-2,{0,+1}} }; // �� �� �� �� 

void input() {
	//ifstream in("test.txt");
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		switch (d) {
			case 1:
				d = 1;
				break;
			case 2:
				d = -1;
				break;
			case 3:
				d = -2;
				break;
			case 4:
				d = 2;
				break;
		}
		Shark ns;
		ns.pos = make_pair(r, c);
		ns.size = z;
		ns.dir = d;
		ns.speed = s;		
		board[r][c] = ns;
	}
}
void solve() {
	for (int c = 1; c <= C; c++) { // 100
		for (int i = 1; i <= R; i++) { // 100			
			if (board[i][c].size !=0 ) { // ���� ���� ����� ����� ��ġ
				ans += board[i][c].size;
				board[i][c].size = 0; // ��� ������
				break;
			}
		}
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				new_board[i][j].size = 0;
			}
		}		
		for (int i = 1; i <= R; i++) { // 10^4 
			for (int j = 1; j <= C; j++) {
				if (board[i][j].size != 0) { // � ĭ�� �� �ִٸ� �̵�������
					Shark cur = board[i][j]; // ���� ���
					pii pos = cur.pos;					
					int nr = 0, nc = 0;
					int d = cur.dir;
					int s = cur.speed;					
					if (abs(d) == 2) { // ������ �¿��� ���
						int col_gap = 0;
						nr = pos.first;
						if (pos.second + (delta[d].second * s) > C || pos.second + (delta[d].second * s) < 1) {
							if (d < 0) { // ������ �������� ��� c = C �� ����
								col_gap = C - pos.second;
							}
							else {
								col_gap = pos.second - 1; // ������ ������ ��� c = 1 �� ����
							}
							d *= -1; // ���� �ε������Ƿ� ���� ��ȯ����
							s -= col_gap; // col_gap��ŭ �̵��� �� �� �̵��ؾ� �ϴ� ĭ ��
							int m = s / (C - 1);
							int n = s % (C - 1);
							if (m % 2 == 0) { // ¦�� ��ŭ ������
								if (d < 0) { // ������ ���� ���
									nc = 1 + n;
								}
								else {
									nc = C - n;
								}
							}
							else { // Ȧ�� �� ��
								if (d < 0) { // ������ ���� ���
									nc = C - n;
								}
								else {
									nc = 1 + n;
								}
								d *= -1; // Ȧ����ŭ ������ ���� �� �� �� Ʋ����� ��
							}
						}
						else {
							nc = pos.second + delta[d].second * s;
						}
						
					}
					else { // ������ ������ ���						
						int row_gap = 0;
						nc = pos.second;
						if (pos.first + (delta[d].first * s) > R || pos.first + (delta[d].first * s) < 1) {
							if (d > 0) { // ������ ���� ��� r = 1 �� ����
								row_gap = pos.first - 1;
							}
							else {
								row_gap = R - pos.first; // ������ �Ʒ��� ��� r = R �� ����
							}
							s -= row_gap; // col_gap��ŭ �̵��� �� �� �̵��ؾ� �ϴ� ĭ ��
							d *= -1;
							int m = s / (R - 1);
							int n = s % (R - 1);
							if (m % 2 == 0) { // ¦�� ��ŭ ������
								if (d > 0) { // ���� ���� ���
									nr = R - n;
								}
								else {
									nr = 1 + n;
								}
							}
							else { // Ȧ�� �� ��
								if (d > 0) { // ���� ���� ���
									nr = 1 + n;
								}
								else {
									nr = R - n;
								}
								d *= -1; // Ȧ����ŭ ������ ���� �� �� �� Ʋ����� ��
							}
						}
						else {
							nr = pos.first + delta[d].first * s;
						}
					}									
					if (new_board[nr][nc].size == 0) { // ���� ĭ�� �� ������
						board[pos.first][pos.second].size = 0; // ���� ��ġ�� ��� �����ְ�
						new_board[nr][nc].size = cur.size; // ���ο� ��� �־���
						new_board[nr][nc].speed = cur.speed;
						new_board[nr][nc].pos = make_pair(nr, nc);
						new_board[nr][nc].dir = d;						
					}
					else { // �� ������ ������ ū �ָ� ���� �־���
						if (new_board[nr][nc].size < cur.size) {
							new_board[nr][nc].size = cur.size;
							new_board[nr][nc].speed = cur.speed;
							new_board[nr][nc].pos = make_pair(nr, nc);
							new_board[nr][nc].dir = d;
						}
					}
				}				
			}
		}
		board = new_board;
	}
}
void print() {
	cout << ans;
}

int main() {
	input();
	solve();
	print();
}

/*
���ÿ��� ���������� �� ĭ �̵��Ѵ�.
���ÿ��� �ִ� ���� �ִ� ��� �߿��� ���� ���� ����� �� ��´�. �� ������ �����ǿ��� ���� �� �������.
�� �̵��Ѵ�.
ĭ�� �������� ��踦 �Ѵ� ��쿡�� ������ �ݴ�� �ٲ㼭 �ӷ��� ������ä�� �̵��Ѵ�.
*/