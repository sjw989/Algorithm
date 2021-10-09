#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#define pii pair<int,int>

using namespace std;

int N, M; // 사이즈 N x M
int ans; // 최대 안전지대 수
int clean_cnt; // 클린존 개수
int wall_cnt;
array<array<int, 9>, 9> board; // 연구소
array<int, 4> drow = { 1,-1,0,0 };
array<int, 4> dcol = { 0,0,1,-1 };
vector<pii> clean; // 클린존
vector<array<pii, 3>> wall_case; // 벽이 세워질 수 있는 경우
queue<pii> clean_zone; // bfs 돌릴 queue

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 0) {
				clean.push_back(make_pair(i, j));
				clean_cnt++;
			}
			if (board[i][j] == 2) {
				clean_zone.push(make_pair(i, j));
			}
			if (board[i][j] == 1) {
				wall_cnt++;
			}
		}
	}
}

void get_wall() {
	for (int i = 0; i < clean.size()-2; i++) {
		for (int j = i + 1; j < clean.size() - 1; j++) {
			for (int k = j + 1; k < clean.size(); k++) {
				array<pii, 3> arr = { clean[i],clean[j],clean[k] };
				wall_case.push_back(arr);
			}		
		}
	} 
}

void push_wall(array<pii,3> arr) {
	for (int i = 0; i < 3; i++) {
		board[arr[i].first][arr[i].second] = 1; 
	}
}

void pop_wall(array<pii, 3> arr) {
	for (int i = 0; i < 3; i++) {
		board[arr[i].first][arr[i].second] = 0;
	}
}

void bfs() {
	queue<pii> q = clean_zone;
	int cnt = 0;
	array<array<int, 9>, 9> visit;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			visit[i][j] = 0;
		}
	}
	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		cnt++;		
		visit[cur.first][cur.second] = 1; // 방문처리
		for (int i = 0; i < 4; i++) {						
			if (cur.first + drow[i] >= 1 && cur.first + drow[i] <= N
				&& cur.second + dcol[i] >= 1 && cur.second + dcol[i] <= M
				&& board[cur.first+drow[i]][cur.second+dcol[i]] == 0
				&& visit[cur.first+drow[i]][cur.second+dcol[i]] == 0) {
				
				visit[cur.first + drow[i]][cur.second + dcol[i]] = 1; // 방문처리
				q.push(make_pair(cur.first + drow[i], cur.second + dcol[i]));
			}
		}
	}				
	ans = max(ans, N * M - cnt); 	
}

void solve() {
	for (array<pii, 3> arr : wall_case) {
		push_wall(arr); // 벽 3개 설치		
		bfs(); // 안전지대 개수 세기
		pop_wall(arr); // 벽 3개 제거
	}
}

void print() {
	cout << ans - (wall_cnt+3);
}

int main() {
	input();
	get_wall();		
	solve();
	print();
}
