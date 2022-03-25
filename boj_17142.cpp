#include <iostream>
#include <fstream>
#include <queue>
#include <array>
#include <vector>
#include <cstring>
#include <iomanip>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;

int N, M; // N x N, ���̷��� ����
int ans= 987654321 ;
int cnt_zero = 0;
array<array<int, 51>, 51> board;
array<array<int, 51>, 51> new_board;
vector<pii> virus;
vector<vector<pii>> virus_pos;

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				virus.push_back(mp(i, j)); // ���̷��� ���� ��ġ�� �����ϰ�
				board[i][j] = -1; // -1�� �ٲ���
			}	
			if (board[i][j] == 0) {
				cnt_zero++;
			}
		}
	}
}
void get_virus_pos(int idx, vector<pii> set_virus) {		
	if (set_virus.size() == M) {
		virus_pos.push_back(set_virus);	
		return;
	}
	for (int i = idx; i < virus.size(); i++) {
		set_virus.push_back(virus[i]);
		get_virus_pos(i + 1, set_virus);
		set_virus.pop_back();
	}
}

void fill_virus(vector<pii> virus) {
	for (auto v : virus) {
		new_board[v.first][v.second] = 2; // 2�̸� Ȱ�����̷���
	}
}

int bfs(vector<pii> virus) {

	int drow[4] = { 0,0,1,-1 };
	int dcol[4] = { 1,-1,0,0 };
	int visit[51][51];
	int t = 0;
	queue<pii> q;
	for (int i = 0; i <= 50; i++) {
		memset(visit[i], 0, sizeof(visit[i]));
	}
	for (auto v : virus) {
		visit[v.first][v.second] = 1;
		q.push(v);
	}	
	int cnt = 0; // ��ĭ ���� ī����
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (new_board[i][j] == 0) {
				cnt++;
			}
		}
	}
	if (cnt == 0) { // ��ĭ�� ������ Ż��						
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				t = max(t, visit[i][j]);
			}
		}
		return t;
	}
	cnt = 0; // ��ĭ�� ����
	while (true) {
		queue<pii> next_q;		
		while (!q.empty()) {
			pii cur = q.front();
			q.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.first + drow[i];
				int nc = cur.second + dcol[i];

				if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && visit[nr][nc] == 0) {					
					if (new_board[nr][nc] != 2 && new_board[nr][nc] != 1) { // Ȱ�� ���̷����� �ִ°� & ���� �ƴϸ�
						if (new_board[nr][nc] == 0) {
							cnt++;
						}
						new_board[nr][nc] = 2; // Ȱ�����̷����� ����
						visit[nr][nc] = visit[cur.first][cur.second] + 1;						
						next_q.push(mp(nr, nc));
					}										
				}
			}			
		}		
		if (cnt == cnt_zero) { // ���̻� ä�� ĭ�� ���ٴ� �ǹ�
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					t = max(t, visit[i][j]);
				}
			}
			break;
		}
		if (next_q.size() == 0) {
			break;
		}
		q = next_q;					
	}	

	return t;
}

void solve() {	
	vector<pii> set_virus;
	get_virus_pos(0,set_virus);
	
	for (vector<pii> virus : virus_pos) {		
		new_board = board;
		fill_virus(virus);
		int t = bfs(virus);
		if (t > 0) {
			ans = min(ans, t);
		}				
	}

}
void print() {
	if (ans == 987654321) {
		cout << -1;
	}
	else {
		cout << ans-1;
	}
}

int main() {
	input();
	solve();
	print();
}