#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <deque>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;

int N, K; // 격자크기, 말의 개수
int ans;
int drow[5] = { 0, 0, 0,-1,1 }; // 우좌상하
int dcol[5] = { 0, 1, -1,0,0 };
array<pii, 11> pos;
array<int, 11> dir;
array<array<int, 13>, 13> board;
array<array<deque<int>, 13>, 13> horse;


void input() {
	//ifstream in("test.txt");
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 1; i <= K; i++) {
		int r, c, d;
		cin >> r >> c >> d;
		pos[i] = mp(r, c);
		dir[i] = d;
		horse[r][c].push_back(i);
	}
}
void white(pii p, pii n, int idx) {
	int s = horse[p.first][p.second].size();  // 현재 덱 크기
	while (s > 0) { // 덱 크기만큼 반복
		int c = horse[p.first][p.second].front(); // 밑에서부터 꺼냄
		if (c == idx) { // i번째 말을 찾으면
			break; // 탈출
		}
		horse[p.first][p.second].pop_front();
		horse[p.first][p.second].push_back(c); // 못 찾으면 제자리에 다시 쌓음
		s--;
	}
	while (s > 0) { // i번 말부터 다음 칸에 쌓음
		int c = horse[p.first][p.second].front(); // 밑에서 꺼내고
		horse[p.first][p.second].pop_front();
		horse[n.first][n.second].push_back(c); // 다음 칸 위에 쌓음
		pos[c] = mp(n.first, n.second); // i번 말 위치 업데이트
		s--;
	}
}
void red(pii p, pii n, int idx) {
	int s = horse[p.first][p.second].size();  // 현재 덱 크기
	while (s > 0) { // 덱 크기만큼 반복
		int c = horse[p.first][p.second].back(); // 위에서부터 꺼냄
		horse[p.first][p.second].pop_back();
		horse[n.first][n.second].push_back(c);
		pos[c] = n;
		if (c == idx) {
			return;
		}
	}

}
void blue(pii p, int idx, int d) {
	if (d == 1 || d == 3) { d++; }
	else if (d == 2 || d == 4) { d--; } // 방향 뒤집기
	dir[idx] = d; // 방향 업데이트
	int nr = p.first + drow[d];
	int nc = p.second + dcol[d];
	if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) { // 뒤집은 방향이 격자 안이고,
		if (board[nr][nc] != 2) { // 파랑색이 아닐 때
			switch (board[nr][nc]) { // 다음 칸 색깔에 따라 이동
			case 0:
				white(p, mp(nr, nc), idx);
				break;
			case 1:
				red(p, mp(nr, nc), idx);
				break;
			}
		}
		// 파랑색이면 이동안함
	}
	else {
		blue(p, idx, d);
	}
	// 뒤집은 방향이 격자 밖이어도 이동안함
}
void solve() {
	int t = 0;
	while (t < 1000) {
		t++;
		for (int i = 1; i <= K; i++) { // 1번말부터 이동
			pii p = pos[i]; // i번 말의 위치
			int d = dir[i]; // i번 말의 방향
			int nr = p.first + drow[d];
			int nc = p.second + dcol[d];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) { // 다음 칸이 격자 안인경우
				switch (board[nr][nc]) {
				case 0:
					white(p, mp(nr, nc), i);
					break;
				case 1:
					red(p, mp(nr, nc), i);
					break;
				case 2:
					blue(p, i, d);
					break;
				}
			}
			else { // 격자 밖인 경우
				blue(p, i, d);
			}
			// 이동 후 다음 칸에 말이 4개 이상 쌓였는지 확인
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (horse[i][j].size() >= 4) {
						ans = t;
						return;
					}
				}
			}
		}
	}
	ans = -1; // t > 1000 인 상황이므로 정답을 찾을 수 없음
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
1. 하나의 말 위에 다른 말을 올릴 수 있다.
2. 체스판은 흰색 빨간색 파란색으로 색칠
3. 말 K개를 놓고 시작, 번호는 1~ K, 이동방향은 4방향
4. 각 턴은 1 ~ K 말이 순서대로 이동한다.
   4-1. 한 말이 이동할때 위에 쌓여있는 말까지 같이 이동
   4-2 턴이 진행되는 중 말이 4개 이상 쌓이면 게임 종료

5. 흰색 -> 비어있는 경우 -> 그 칸으로 이동
   말이 이미 있는 경우는 가장 위에 A번 말을 올려놓는다
6. 빨간색 -> 비어있는 경우 -> 순서뒤집음
7. 파랑색인 경우 A번 말의 이동 방향을 반대로하고 한 칸 이동
   바꾼 후에 이동하려는 칸이 파랑색인 경우는 이동 x









*/