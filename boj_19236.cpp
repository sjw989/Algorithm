#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

typedef struct Fish {
	pii pos;
	int d, n;
	bool is_live;
};
array<array<Fish, 5>,5> board; // 물고기번호, 방향
array<pii, 9> delta = { make_pair(0,0), make_pair(-1,0), make_pair(-1,-1),make_pair(0,-1)
					,make_pair(1,-1),make_pair(1,0),make_pair(1,1),make_pair(0,1),make_pair(-1,1) };
int ans; // 정답
array<Fish, 17> fishes;
void print();
bool cmp(Fish a, Fish b) {
	return a.n < b.n;
}
void input() {
	//ifstream in("test.txt");
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int n, d;
			cin >> n >> d;
			Fish f;
			f.pos = make_pair(i, j);
			f.d = d;
			f.n = n;
			f.is_live = true;
			board[i][j] = f;
			fishes[n] = f;			
		}
	}
	sort(fishes.begin(), fishes.end(), cmp); // 번호순으로 움직이기 위해 정렬
}
void solve(int shark_num, pii shark_pos, int shark_dir) {			
	shark_dir = board[shark_pos.first][shark_pos.second].d;
	if (board[shark_pos.first][shark_pos.second].is_live) {
		board[shark_pos.first][shark_pos.second].is_live = false;
		shark_num += board[shark_pos.first][shark_pos.second].n;
	}	
	fishes[board[shark_pos.first][shark_pos.second].n].is_live = false;
	
	for (Fish f : fishes) {				
		if (!f.is_live) { continue; } // 죽은 물고기 건너뜀

		bool can_move = false; // 이 물고기가 움직일 수 있는지
		int d = f.d;
		int nr = f.pos.first + delta[d].first;
		int nc = f.pos.second + delta[d].second;
		if (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) { // 범위안에 들어가고
			if (make_pair(nr, nc) != shark_pos) { // 상어가 없는 곳이라면
				can_move = true; // 움직일 수 있음을 표시
				pii cur_p = make_pair(f.pos.first, f.pos.second);
				Fish nf = board[nr][nc];				
				board[nr][nc] = f;
				board[cur_p.first][cur_p.second] = nf;				
				fishes[nf.n].pos = cur_p;				
				fishes[f.n].pos = make_pair(nr, nc);				
			}
		}
		if (!can_move) { // 현재 바라보는 방향으로 움직이지 못한다면
			for (int i = 0; i < 7; i++) { // 반시계방향으로 45도 회전
				d++;
				if (d > 8) {
					d = 1;
				}
				nr = f.pos.first + delta[d].first;
				nc = f.pos.second + delta[d].second;
				if (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) {
					if (make_pair(nr, nc) != shark_pos) {						
						can_move = true;
						pii cur_p = make_pair(f.pos.first, f.pos.second);						
						Fish nf = board[nr][nc];
						board[nr][nc] = f;
						board[nr][nc].d = d;
						board[cur_p.first][cur_p.second] = nf;							
						fishes[nf.n].pos = cur_p;
						fishes[f.n].pos = make_pair(nr, nc);
						fishes[f.n].d = d;
						break;
					}
				}
			}
		}				
	}			
	int nr = shark_pos.first + delta[shark_dir].first;
	int nc = shark_pos.second + delta[shark_dir].second;
	while (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) {		
		if (board[nr][nc].is_live) { // 해당 칸에 물고기가 있어 이동가능하면
			array<array<Fish, 5>, 5> cur_board = board;
			array<Fish,17> cur_fishes = fishes;
			solve(shark_num, make_pair(nr, nc), shark_dir);
			fishes = cur_fishes;
			board = cur_board;					
		}
		nr += delta[shark_dir].first;
		nc += delta[shark_dir].second;
	}	
	ans = max(ans, shark_num);
}
void print() {
	cout << ans;
}

int main() {
	input();	
	solve(0, make_pair(1,1), 0);
	print();
	cout << ans;
}