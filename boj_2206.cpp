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
array<array<array<int, 1001>, 1001>, 2> visit; // ���� �μ��� �湮�� ���� �� �μ��� �湮�� ���

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
	q.push(make_pair(make_pair(1, 1), 0)); // row, col, �� �μ� Ƚ��
	cnt[1][1] = 1;
	visit[1][1][0] = 1;

	while (!q.empty()) {
		piii cur = q.front();
		q.pop();
				
		for (int i = 0; i < 4; i++) { // �����¿� 4���� ��� Ž��
			int nextRow = cur.first.first + drow[i];
			int nextCol = cur.first.second + dcol[i];			
			if (nextRow >= 1 && nextRow <= N && nextCol >= 1 && nextCol <= M) { // ���� ��
				if (board[nextRow][nextCol] == 0 && visit[cur.second][nextRow][nextCol] == 0) { // ���� ĭ�� ���� �ƴϰ� ���� ���·� �湮�� �� ������
					q.push(make_pair(make_pair(nextRow, nextCol), cur.second)); // queue�� �߰�
					cnt[nextRow][nextCol] = cnt[cur.first.first][cur.first.second] + 1; // �湮Ƚ�� ī��Ʈ
					visit[cur.second][nextRow][nextCol] = 1; // visitó��
				}

				if (board[nextRow][nextCol] == 1 && cur.second == 0) { // ���� ĭ�� ���̰�, �̶����� ���� �μ� Ƚ���� 0�̶��
					q.push(make_pair(make_pair(nextRow, nextCol), cur.second + 1)); // queue�� �߰� (�� �μ� Ƚ�� +1)
					cnt[nextRow][nextCol] = cnt[cur.first.first][cur.first.second] + 1; // �湮Ƚ�� ī��Ʈ
					visit[cur.second + 1][nextRow][nextCol] = 1; // �湮ó��
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