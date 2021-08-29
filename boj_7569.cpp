#include <iostream>
#include <vector>
#include <queue>
#include <array>
#define piii pair<int,pair<int,int>>
using namespace std;


int M, N, H; // 가로 세로 높이
int cnt;
int box[101][101][101];
int visit[101][101][101];

// 상하좌우 위 아래
array<int, 6> drow = { -1, 1, 0, 0,0,0 };
array<int, 6> dcol = { 0, 0, -1, +1,0,0 };
array<int, 6> dheight = { 0, 0, 0, 0,1,-1 };
queue<piii> q; // 토마토 담을 queue

void input() {	
	cin >> M >> N >> H;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= M; k++) {
				int p;
				cin >> p;
				box[i][j][k] = p;
			}
		}
	}
}



bool input_check() {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= M; k++) {
				if (box[i][j][k] == 0) {
					return false;
				}
			}
		}
	}
	return true;
}

void get_tomato() {	
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= M; k++) {
				if (box[i][j][k] == 1) {
					visit[i][j][k] = 1;
					q.push(make_pair(i, make_pair(j, k)));
				}
			}
		}
	}	
}

void bfs() {
	int child = 0;
	child = q.size();
	while (!q.empty()) {
		int new_child = 0;
		for (int i = 0; i < child; i++) {
			piii s = q.front();
			q.pop();
			for (int j = 0; j < 6; j++) {
				if (s.first + dheight[j] >= 1 && s.first + dheight[j] <= H
					&& s.second.first + drow[j] >= 1 && s.second.first + drow[j] <= N
					&& s.second.second + dcol[j] >= 1 && s.second.second + dcol[j] <= M) {

					if (box[s.first + dheight[j]][s.second.first + drow[j]][s.second.second + dcol[j]] == 0
						&& visit[s.first + dheight[j]][s.second.first + drow[j]][s.second.second + dcol[j]] == 0) {

						box[s.first + dheight[j]][s.second.first + drow[j]][s.second.second + dcol[j]] = 1;
						visit[s.first + dheight[j]][s.second.first + drow[j]][s.second.second + dcol[j]] = 1;
						q.push(make_pair(s.first + dheight[j], make_pair(s.second.first + drow[j], s.second.second + dcol[j])));
						new_child++;
					}					
				}
			}
		}
		child = new_child;
		cnt++;
	}
}


void print() {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= M; k++) {				
				if (box[i][j][k] == 0) {
					cout << -1 << "\n";					
					return;
				}
			}			
		}		
	}	
	cout << cnt - 1 << "\n";
}

int main() {

	input();
	if (input_check()) {
		cout << 0 << "\n";				
	}
	else {
		get_tomato();
		bfs();		
		print();
	}
	
}