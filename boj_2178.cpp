#include <iostream>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;

int N, M; //  N x M
array<array<char, 101>, 101> board;
array<array<int, 101>, 101> cnt;
array<array<int, 101>, 101> visit;

void input() {		
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		string k;
		cin >> k;
		for (int j = 1; j <= k.length(); j++) {
			board[i][j] = k[j - 1];
		}
	}
}

void bfs() {	
	queue<pii> q;		
	q.push(make_pair(1, 1)); // 시작지점 넣기
	visit[1][1] = 0; // 방문처리
	cnt[1][1] = 1; // 시작지점 cnt = 1
	while (!q.empty()) {
		pii s = q.front();
		q.pop();		
		if (s.first + 1 <= N && board[s.first + 1][s.second] == '1' && visit[s.first + 1][s.second] == 0) {
			q.push(make_pair(s.first + 1, s.second));
			visit[s.first + 1][s.second] = 1;
			cnt[s.first + 1][s.second] = cnt[s.first][s.second] + 1;
		}
		if (s.first - 1 >= 1 && board[s.first - 1][s.second] == '1' && visit[s.first - 1][s.second] == 0) {
			q.push(make_pair(s.first - 1, s.second));
			visit[s.first - 1][s.second] = 1;
			cnt[s.first - 1][s.second] = cnt[s.first][s.second] + 1;
		}
		if (s.second + 1 <= M && board[s.first][s.second + 1] == '1' && visit[s.first][s.second + 1] == 0) {
			q.push(make_pair(s.first , s.second + 1));
			visit[s.first][s.second + 1] = 1;
			cnt[s.first ][s.second + 1] = cnt[s.first][s.second] + 1;

		}
		if (s.second - 1 >= 1 && board[s.first][s.second - 1] == '1' && visit[s.first][s.second - 1] == 0) {
			q.push(make_pair(s.first , s.second - 1));
			visit[s.first][s.second - 1] = 1;
			cnt[s.first][s.second - 1] = cnt[s.first][s.second] + 1;
		}		
	}
	
}

int main() {
	input();
	bfs();
	cout << cnt[N][M] << "\n";
}

