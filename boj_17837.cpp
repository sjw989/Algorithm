#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <deque>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;

int N, K; // ����ũ��, ���� ����
int ans;
int drow[5] = { 0, 0, 0,-1,1 }; // ���»���
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
	int s = horse[p.first][p.second].size();  // ���� �� ũ��
	while (s > 0) { // �� ũ�⸸ŭ �ݺ�
		int c = horse[p.first][p.second].front(); // �ؿ������� ����
		if (c == idx) { // i��° ���� ã����
			break; // Ż��
		}
		horse[p.first][p.second].pop_front();
		horse[p.first][p.second].push_back(c); // �� ã���� ���ڸ��� �ٽ� ����
		s--;
	}
	while (s > 0) { // i�� ������ ���� ĭ�� ����
		int c = horse[p.first][p.second].front(); // �ؿ��� ������
		horse[p.first][p.second].pop_front();
		horse[n.first][n.second].push_back(c); // ���� ĭ ���� ����
		pos[c] = mp(n.first, n.second); // i�� �� ��ġ ������Ʈ
		s--;
	}
}
void red(pii p, pii n, int idx) {
	int s = horse[p.first][p.second].size();  // ���� �� ũ��
	while (s > 0) { // �� ũ�⸸ŭ �ݺ�
		int c = horse[p.first][p.second].back(); // ���������� ����
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
	else if (d == 2 || d == 4) { d--; } // ���� ������
	dir[idx] = d; // ���� ������Ʈ
	int nr = p.first + drow[d];
	int nc = p.second + dcol[d];
	if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) { // ������ ������ ���� ���̰�,
		if (board[nr][nc] != 2) { // �Ķ����� �ƴ� ��
			switch (board[nr][nc]) { // ���� ĭ ���� ���� �̵�
			case 0:
				white(p, mp(nr, nc), idx);
				break;
			case 1:
				red(p, mp(nr, nc), idx);
				break;
			}
		}
		// �Ķ����̸� �̵�����
	}
	else {
		blue(p, idx, d);
	}
	// ������ ������ ���� ���̾ �̵�����
}
void solve() {
	int t = 0;
	while (t < 1000) {
		t++;
		for (int i = 1; i <= K; i++) { // 1�������� �̵�
			pii p = pos[i]; // i�� ���� ��ġ
			int d = dir[i]; // i�� ���� ����
			int nr = p.first + drow[d];
			int nc = p.second + dcol[d];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) { // ���� ĭ�� ���� ���ΰ��
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
			else { // ���� ���� ���
				blue(p, i, d);
			}
			// �̵� �� ���� ĭ�� ���� 4�� �̻� �׿����� Ȯ��
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
	ans = -1; // t > 1000 �� ��Ȳ�̹Ƿ� ������ ã�� �� ����
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
1. �ϳ��� �� ���� �ٸ� ���� �ø� �� �ִ�.
2. ü������ ��� ������ �Ķ������� ��ĥ
3. �� K���� ���� ����, ��ȣ�� 1~ K, �̵������� 4����
4. �� ���� 1 ~ K ���� ������� �̵��Ѵ�.
   4-1. �� ���� �̵��Ҷ� ���� �׿��ִ� ������ ���� �̵�
   4-2 ���� ����Ǵ� �� ���� 4�� �̻� ���̸� ���� ����

5. ��� -> ����ִ� ��� -> �� ĭ���� �̵�
   ���� �̹� �ִ� ���� ���� ���� A�� ���� �÷����´�
6. ������ -> ����ִ� ��� -> ����������
7. �Ķ����� ��� A�� ���� �̵� ������ �ݴ���ϰ� �� ĭ �̵�
   �ٲ� �Ŀ� �̵��Ϸ��� ĭ�� �Ķ����� ���� �̵� x









*/