#include <iostream>
#include <fstream>
#include <array>
#include <math.h>
#include <queue>
#include <vector>
#define pii pair<int,int>
using namespace std;

int N, Q; // 격자크기, 파이어스톰 총 횟수
int M; // 2^N
int cnt_block;
array<int, 4> drow = { 1,-1,0,0 };
array<int, 4> dcol = { 0,0,1,-1 };
array<array<int, 65>, 65> board;
array<array<int, 65>, 65> new_board;
array<array<int, 65>, 65> visit;
array<array<int, 65>, 65> temp;
array<array<int, 65>, 65> temp2;
vector<int> fs;
void input() {
	//sifstream in("test.txt");
	cin >> N >> Q;
	M = pow(2, N);
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		int k;
		cin >> k;
		fs.push_back(k);
	}
}
void rotate(int r, int c, int len) {		
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			temp[i][j] = board[r + i - 1][c + j - 1];
		}
	}
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			temp2[r + i - 1][c + j -1] = temp[len - j + 1][i];
		}
	}
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			board[r + i - 1][c + j - 1] = temp2[r + i - 1][c + j - 1];
		}		
	}		
}

void solve() {
	for (int l : fs) {			
		int sub_cnt = pow(M, 2) / pow(pow(2, l), 2); // 부분격자의 개수 : M^2 / (2^L)^2		
		int r = 1, c = 1;
		int len = pow(2, l);
		for (int i = 0; i < sub_cnt; i++) { // 부분격자의 개수만큼 반복						
			rotate(r, c, len);			
			c += len;
			if (c > M) {
				r += len;
				c = 1;
			}					
		}						
		new_board = board;
		for (int i = 1; i <= M; i++) {
			for (int j = 1; j <= M; j++) {				
				if (board[i][j] != 0) { // 얼음이 있는 칸					
					int cnt = 0;
					for (int k = 0; k < 4; k++) {
						int nr = i + drow[k];
						int nc = j + dcol[k];
						if (nr >= 1 && nr <= M && nc >= 1 && nc <= M && board[nr][nc] > 0) {// 다음 칸에 얼음이 있으면							
							cnt++;						
						}						
					}
					if (cnt < 3) {
						new_board[i][j]--;
					}
				}				
			}
		}
		board = new_board;
	}	
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			if (board[i][j] > 0 && visit[i][j] == 0) { // 얼음이 있고 아직 방문하지 않은 칸				
				queue<pii> q;
				q.push(make_pair(i, j));
				visit[i][j] = 1;
				int cnt = 1;
				while (!q.empty()) {
					pii cur = q.front();					
					q.pop();
					for (int k = 0; k < 4; k++) {
						int nr = cur.first + drow[k];
						int nc = cur.second + dcol[k];
						if (nr >= 1 && nr <= M && nc >= 1 && nc <= M && visit[nr][nc] == 0 && board[nr][nc]>0) {							
							cnt++;
							q.push(make_pair(nr, nc));
							visit[nr][nc] = 1;
						}
					}
				}				
				cnt_block = max(cnt_block, cnt);				
			}
		}
	}	
}

void print() {
	int ans = 0;
	for (int i = 1;  i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			ans += board[i][j];
		}
	}
	cout << ans << "\n";
	cout << cnt_block;
}

int main() {	
	input();
	solve();
	print();
}
