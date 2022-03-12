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
	int size; // 크기
	int dir; // 방향
	int speed; // 속도

};

int R, C, M;// R x C , M : 상어의 수
int ans; // 낚시왕이 잡은 상어의 크기 합
array<array<Shark, 101>, 101> board;
array<array<Shark, 101>, 101> new_board;
map<int, pii> delta = { {1,{-1,0}}, {-1,{1,0}}, {2,{0,-1}}, {-2,{0,+1}} }; // 상 하 좌 우 

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
			if (board[i][c].size !=0 ) { // 땅과 가장 가까운 상어의 위치
				ans += board[i][c].size;
				board[i][c].size = 0; // 상어 없애줌
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
				if (board[i][j].size != 0) { // 어떤 칸에 상어가 있다면 이동시켜줌
					Shark cur = board[i][j]; // 현재 상어
					pii pos = cur.pos;					
					int nr = 0, nc = 0;
					int d = cur.dir;
					int s = cur.speed;					
					if (abs(d) == 2) { // 방향이 좌우인 경우
						int col_gap = 0;
						nr = pos.first;
						if (pos.second + (delta[d].second * s) > C || pos.second + (delta[d].second * s) < 1) {
							if (d < 0) { // 방향이 오른쪽인 경우 c = C 에 붙임
								col_gap = C - pos.second;
							}
							else {
								col_gap = pos.second - 1; // 방향이 왼쪽인 경우 c = 1 에 붙임
							}
							d *= -1; // 벽에 부딪혔으므로 방향 전환해줌
							s -= col_gap; // col_gap만큼 이동한 후 총 이동해야 하는 칸 수
							int m = s / (C - 1);
							int n = s % (C - 1);
							if (m % 2 == 0) { // 짝수 만큼 나오면
								if (d < 0) { // 오른쪽 보는 경우
									nc = 1 + n;
								}
								else {
									nc = C - n;
								}
							}
							else { // 홀수 일 때
								if (d < 0) { // 오른쪽 보는 경우
									nc = C - n;
								}
								else {
									nc = 1 + n;
								}
								d *= -1; // 홀수만큼 나오면 방향 한 번 더 틀어줘야 함
							}
						}
						else {
							nc = pos.second + delta[d].second * s;
						}
						
					}
					else { // 방향이 상하인 경우						
						int row_gap = 0;
						nc = pos.second;
						if (pos.first + (delta[d].first * s) > R || pos.first + (delta[d].first * s) < 1) {
							if (d > 0) { // 방향이 위인 경우 r = 1 에 붙임
								row_gap = pos.first - 1;
							}
							else {
								row_gap = R - pos.first; // 방향이 아래인 경우 r = R 에 붙임
							}
							s -= row_gap; // col_gap만큼 이동한 후 총 이동해야 하는 칸 수
							d *= -1;
							int m = s / (R - 1);
							int n = s % (R - 1);
							if (m % 2 == 0) { // 짝수 만큼 나오면
								if (d > 0) { // 위쪽 보는 경우
									nr = R - n;
								}
								else {
									nr = 1 + n;
								}
							}
							else { // 홀수 일 때
								if (d > 0) { // 위쪽 보는 경우
									nr = 1 + n;
								}
								else {
									nr = R - n;
								}
								d *= -1; // 홀수만큼 나오면 방향 한 번 더 틀어줘야 함
							}
						}
						else {
							nr = pos.first + delta[d].first * s;
						}
					}									
					if (new_board[nr][nc].size == 0) { // 다음 칸에 상어가 없으면
						board[pos.first][pos.second].size = 0; // 현재 위치에 상어 없애주고
						new_board[nr][nc].size = cur.size; // 새로운 상어 넣어줌
						new_board[nr][nc].speed = cur.speed;
						new_board[nr][nc].pos = make_pair(nr, nc);
						new_board[nr][nc].dir = d;						
					}
					else { // 상어가 있으면 사이즈 큰 애를 먼저 넣어줌
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
낚시왕이 오른쪽으로 한 칸 이동한다.
낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다. 상어를 잡으면 격자판에서 잡은 상어가 사라진다.
상어가 이동한다.
칸이 격자판의 경계를 넘는 경우에는 방향을 반대로 바꿔서 속력을 유지한채로 이동한다.
*/