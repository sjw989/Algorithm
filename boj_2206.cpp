#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#define piii pair<pair<int,int>,int>
using namespace std;

int N, M; // N x M
array<int, 4 > drow = { 1,-1,0,0 };
array<int, 4 > dcol = { 0,0,1,-1 };
array<array<int, 1001>, 1001> board;
array<array<int, 1001>, 1001> cnt;
array<array<array<int, 1001>, 1001>, 2> visit; // 벽을 부수고 방문한 경우와 안 부수고 방문한 경우

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		string inp;
		cin >> inp;
		for (int j = 1; j <= M; j++) {
			board[i][j] = inp[j - 1] - '0';
		}
	}
}

void bfs() {
	queue<piii> q;
	q.push(make_pair(make_pair(1, 1), 0)); // row, col, 벽 부순 횟수
	cnt[1][1] = 1;
	visit[1][1][0] = 1;

	while (!q.empty()) {
		piii cur = q.front();
		q.pop();
				
		for (int i = 0; i < 4; i++) { // 상하좌우 4가지 경우 탐색
			int nextRow = cur.first.first + drow[i];
			int nextCol = cur.first.second + dcol[i];			
			if (nextRow >= 1 && nextRow <= N && nextCol >= 1 && nextCol <= M) { // 범위 안
				if (board[nextRow][nextCol] == 0 && visit[cur.second][nextRow][nextCol] == 0) { // 다음 칸이 벽이 아니고 현재 상태로 방문한 적 없으면
					q.push(make_pair(make_pair(nextRow, nextCol), cur.second)); // queue에 추가
					cnt[nextRow][nextCol] = cnt[cur.first.first][cur.first.second] + 1; // 방문횟수 카운트
					visit[cur.second][nextRow][nextCol] = 1; // visit처리
				}

				if (board[nextRow][nextCol] == 1 && cur.second == 0) { // 다음 칸이 벽이고, 이때까지 벽을 부순 횟수가 0이라면
					q.push(make_pair(make_pair(nextRow, nextCol), cur.second + 1)); // queue에 추가 (벽 부순 횟수 +1)
					cnt[nextRow][nextCol] = cnt[cur.first.first][cur.first.second] + 1; // 방문횟수 카운트
					visit[cur.second + 1][nextRow][nextCol] = 1; // 방문처리
				}				

				if (nextRow == N && nextCol == M) {
					return;
				}
			}
		}
	}	
}

void print() {

	if (cnt[N][M] == 0) {
		cout << -1;
	}
	else {
		cout << cnt[N][M];
	}	

}

int main() {
	input();
	bfs();
	print();
}