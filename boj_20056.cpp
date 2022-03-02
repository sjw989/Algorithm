#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#define pii pair<int,int>
using namespace std;

typedef struct FireBall {	
	FireBall(int mass, int dir, int speed, int row, int col) {
		m = mass;
		d = dir;
		s = speed;
		pos = make_pair(row, col);
	}
	int m;// 질량
	int d; // 방향
	int s; // 속력
	pii pos; // 위치	
};

int N, M, K; // N x N , M : 파이어볼의 개수, K : 이동 횟수
vector<FireBall> fb;
array<array<vector<FireBall>, 51>, 51 > board;
array<int, 4> odd = { 1,3,5,7 };
array<int, 4> even = { 0,2,4,6 };
array<pii, 8> delta = { make_pair(-1,0),make_pair(-1,1),make_pair(0,1),make_pair(1,1)
					   ,make_pair(+1,0), make_pair(1,-1), make_pair(0,-1), make_pair(-1,-1) };


void input() {
	//ifstream in("test.txt");
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		FireBall f = FireBall(m, d, s, r, c);
		fb.push_back(f);
	}
}
void solve() {
	int t = 0;
	//cout << N << " " << M << " " << K << endl;
	while (t < K) {			
		
		/*
		* for (int i = 0; i < fb.size(); i++) {
			cout << fb[i].pos.first << "," << fb[i].pos.second << " " << fb[i].m << " " << fb[i].s << " " << fb[i].d << endl;
		}
		cout << endl;
		*/
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {				
					board[i][j].clear();
			 }
		}
		for (int i = 0; i < fb.size(); i++) {
			FireBall f = fb[i];			
			int nr = f.pos.first + (delta[f.d].first * f.s);
			int nc = f.pos.second + (delta[f.d].second * f.s);						
			//cout << f.pos.first << "," << f.pos.second << " " << nr << "," << nc << " ";
			if (nr > N) {
				nr = nr % N;				
			}
			if(nr < 1){
				nr = N - (abs(nr) % N);
			}
			if (nc > N) {
				nc = nc % N;

			}
			if (nc < 1) {
				nc = N - (abs(nc) % N);
			}
										
			//cout << " " << nr << "," << nc << endl;
			board[nr][nc].push_back(FireBall(f.m, f.d, f.s, nr, nc));
		}
		vector<FireBall> newFireBall;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (board[i][j].size() >= 2) {				
					int nm=0, ns=0, nd=0;					
					int cnt_even = 0;					
					for (int p = 0; p < board[i][j].size(); p++) {
						nm += board[i][j][p].m;
						ns += board[i][j][p].s;
						if (board[i][j][p].d % 2 == 0) {
							cnt_even++;
						}
					}					
					nm /= 5;					
					ns /= board[i][j].size();										
					if (cnt_even == 0 || cnt_even == board[i][j].size()) {
						nd = 1;
					}
					if (nm > 0) {
						for (int q = 0; q < 4; q++) {							
							if (nd == 1) {
								newFireBall.push_back(FireBall(nm, even[q], ns, i, j));
							}
							else {
								newFireBall.push_back(FireBall(nm, odd[q], ns, i, j));
							}
						}
					}					
				}
				else {
					for (int p = 0; p < board[i][j].size(); p++) {
						newFireBall.push_back(board[i][j][p]);
					}
				}
			}
		}
		/*
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << board[i][j].size() << " ";
			}
			cout << endl;
		}
		cout << endl;*/
		fb = newFireBall;
		t++;
	}
}
void print() {
	int ans = 0;
	for (int i = 0; i < fb.size(); i++) {
		ans += fb[i].m;
	}
	cout << ans;
}

int main() {
	input();
	solve();
	print();
}
