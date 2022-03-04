#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>
#include <vector>
#define pii pair<int,int>
#define MAX_N 500
using namespace std;

int N; // N x N
int ans = 0;
array<pii, 4 > delta = { make_pair(0,-1),make_pair(+1,0), make_pair(0,+1), make_pair(-1,0) }; //좌 하 우 상
array<int, 10> ratio = { 2, 10, 7, 1, 5, 10, 7, 1 , 2, -1 }; 

array<pii, 10> lef = { make_pair(-2,0), make_pair(-1,-1), make_pair(-1,0), make_pair(-1,+1), make_pair(0,-2),
	 make_pair(+1,-1), make_pair(+1,0),make_pair(+1,+1), make_pair(+2,0), make_pair(0,-1) };

array<pii, 10> down = { make_pair(0,-2), make_pair(+1,-1), make_pair(0,-1), make_pair(-1,-1), make_pair(+2,0),
	 make_pair(+1,+1), make_pair(0,+1),make_pair(-1,+1), make_pair(0,+2), make_pair(+1,0) };

array<pii, 10> righ = { make_pair(-2,0), make_pair(-1,+1), make_pair(-1,0), make_pair(-1,-1), make_pair(0,+2),
		make_pair(+1,+1), make_pair(+1,0),make_pair(+1,-1), make_pair(+2,0), make_pair(0,+1) };		

array<pii, 10> up = { make_pair(0,+2), make_pair(-1,+1), make_pair(0,+1), make_pair(+1,+1), make_pair(-2,0),
	 make_pair(-1,-1), make_pair(0,-1),make_pair(+1,-1), make_pair(0,-2), make_pair(-1,0) };


array<array<int, MAX_N>, MAX_N> board;

void input() {
	ifstream in("test.txt");
	in >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			in >> board[i][j];
		}
	}
}
void tornado(pii cur_p, int cur_dir) {
	
	int dust = board[cur_p.first][cur_p.second];
	if (dust == 0) { return; }
	int gap = 0;
	board[cur_p.first][cur_p.second] = 0;
	for (int i = 0; i < 10; i++) {
		int nr = cur_p.first, nc = cur_p.second;
		switch (cur_dir) {
		case 0:
			nr += lef[i].first;
			nc += lef[i].second;
			break;
		case 1:
			nr += down[i].first;
			nc += down[i].second;
			break;
		case 2:
			nr += righ[i].first;
			nc += righ[i].second;
			break;
		case 3:
			nr += up[i].first;
			nc += up[i].second;
			break;
		}
		if (i < 9) {
			int minus_dust = (ratio[i] * dust) / 100;
			gap += minus_dust;
			//cout << dust << " " << ratio[i] << " " << minus_dust;
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
				board[nr][nc] += minus_dust;
				//cout << endl;
			}
			else {
				ans += minus_dust;
				//cout << "  ans" << endl;
			}
		}
		else {
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
				board[nr][nc] += dust - gap;
			}
			else {
				ans += dust - gap;
			}
			//cout << "alpha: " << dust - gap << endl;
				
		}
	}
	/*
	cout << ans << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << setw(5) << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;*/
}
void solve() {
	pii cur_p = make_pair(N / 2 + 1, N / 2 + 1); // 현재위치
	int cur_dir = 0;
	int len = 1;
	for (int i = 0; i < N / 2; i++) {
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < len; j++) {
				cur_p = make_pair(cur_p.first + delta[cur_dir].first, cur_p.second + delta[cur_dir].second);
				tornado(cur_p,cur_dir);
			}
			if (cur_dir % 2 == 1) { len++; } // 아래, 위로 이동한 후엔 len++
			cur_dir++; // 방향 전환
			if (cur_dir == 4) { cur_dir = 0; }
		}
	}
	for (int i = 0; i < len - 1; i++) {
		cur_p = make_pair(cur_p.first + delta[cur_dir].first, cur_p.second + delta[cur_dir].second);
		tornado(cur_p, cur_dir);
	}
}

void print() {
	cout << ans << endl;
}
int main() {
	input();
	solve();
	print();
}