#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#include <math.h>
#include <iomanip>
#define pii pair<int,int>
using namespace std;

struct BlockGroup {
	int rainbow = 0;
	pii std_block = make_pair(22,22);	
	vector<pii> block = {};
};

int N, M; // ����ũ��, ������ ����
int ans;
array<array<int, 21>, 21> board;
array<int, 4> drow = { -1,1,0,0 };
array<int, 4> dcol = { 0,0,-1,1 };
BlockGroup bestBG;

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

void find_group() {
	bestBG.rainbow = 0;
	bestBG.std_block = make_pair(22, 22);
	bestBG.block.clear();
	array<array<int, 21>, 21> visit;	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visit[i][j] = 0;
		}
	}	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visit[i][j] == 0 && board[i][j] > 0) { // ���� �湮�����ʾҰ�, �Ϲ� ����� ã����
				BlockGroup bg; // ���ο� ��� �׷�
				bg.block.push_back(make_pair(i, j));
				bg.std_block = make_pair(i, j);
				queue<pii> q; // bfs�� ���� ť
				q.push(make_pair(i, j));
				visit[i][j] = 1;
				array<array<int, 21>, 21> bfs_visit;
				for (int i = 1; i <= N; i++) {
					for (int j = 1; j <= N; j++) {
						bfs_visit[i][j] = 0;
					}
				}
				bfs_visit[i][j] = 1;
				while (!q.empty()) {					
					pii cur = q.front();					
					q.pop();
					for (int k = 0; k < 4; k++) {
						int nr = cur.first + drow[k];
						int nc = cur.second + dcol[k];
						if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && bfs_visit[nr][nc] == 0) { // ������ ���ϰ� ���� Ž�� x �� ��
							if (board[nr][nc] == 0) { // �������� ���
								bg.block.push_back(make_pair(nr, nc));
								bg.rainbow++;
								q.push(make_pair(nr, nc));
								bfs_visit[nr][nc] = 1;
							}
							else if (board[i][j] == board[nr][nc]) { // �������� �ƴ� ���
								bg.block.push_back(make_pair(nr, nc));
								if (bg.std_block.first > nr) { // ���� ��� ������Ʈ
									bg.std_block = make_pair(nr, nc);
								}
								else if (bg.std_block.first == nr && bg.std_block.second > nc) {
									bg.std_block = make_pair(nr, nc);
								}
								visit[nr][nc] = 1;
								bfs_visit[nr][nc] = 1;
								q.push(make_pair(nr, nc));
							}							
							
							
						}
					}
				}				
				if (bg.block.size() >= 2) { // ��ϱ׷��� ������ �� ��
					if (bg.block.size() > bestBG.block.size()) { // ��� �׷��� ũ�Ⱑ �� ũ�ٸ�
						bestBG = bg; // ����Ʈ ��ϱ׷� ������Ʈ
					}
					else if (bg.block.size() == bestBG.block.size()) { // ����� �����ϴٸ�
						if (bg.rainbow > bestBG.rainbow) { // ������ ��� ��
							bestBG = bg;
						}
						else if (bg.rainbow == bestBG.rainbow) { // �������� ���ٸ�
							if (bg.std_block.first > bestBG.std_block.first) {
								bestBG = bg;
							}
							else if (bg.std_block.first == bestBG.std_block.first) {
								if (bg.std_block.second > bestBG.std_block.second) {
									bestBG = bg;
								}
							}
						}
					}
				}
			}
		}
	}
}

void gravity() {
	for (int c = 1; c <= N; c++) {
		for (int r = N; r >= 1; r--) {
			if (board[r][c] >= 0) { // ���� ��� ���� ��� ���				
				int nr = r + 1;							
				while (true) {					
					if (nr <= N && board[nr][c] == -2) {						
						board[nr][c] = board[nr-1][c];
						board[nr-1][c] = -2;						
						nr++;
					}
					else {						
						break;
					}
				}
				
			}			
		}
	}
}

void rotate() {
	array<array<int, 21>, 21> sub ;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sub[i][j] = board[j][N - i+ 1];
		}
	}
	board = sub;
}
void solve() {	
	while (true) {
		find_group();
		if (bestBG.block.size() < 2) {
			return;
		}
		for (int i = 0; i < bestBG.block.size(); i++) {
			pii bk = bestBG.block[i];
			board[bk.first][bk.second] = -2; // ����� ǥ��
		}
		ans += pow(bestBG.block.size(), 2); // ����ȹ��	
		gravity();
		rotate();
		gravity();
	}	
	


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
��� ���� : �Ϲ� ����� �� ��� ����, ������ ���x (0), ������ x (-1)
���غҷ� : �������� �ƴ� �Ϲ� ����� ���� ��ȣ�� ���� �۰� ���� ���� ������
			-> ���� ���� ���



*/