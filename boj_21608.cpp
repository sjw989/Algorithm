#include <iostream>
#include <fstream>
#include <array>
#include <math.h>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;


int N; // 학생의 수
array<pii, 4> delta = { mp(1,0),mp(-1,0),mp(0,1),mp(0,-1) };
array<array<int, 21>, 21> board;
array<vector<int>, 401> priority;
array<int, 401> std_id;
array<int, 401> num_pri;

struct BestSeat {	
	pii pos = mp(21,21);
	int pri = 0;
	int empty = 0;
};

void input(){
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 1; i <= N * N; i++) {
		int n;		
		cin >> n;
		for (int j = 0; j < 4; j++) {
			int k;
			cin >> k;
			priority[n].push_back(k);
			std_id[i] = n;
		}
	}

}

BestSeat find_seat(vector<int> cur_priority) {
	BestSeat bs;	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j] == 0) { // 빈자리인 경우
				int pri = 0; // 인접 선호하는 친구 수
				int empty = 0; // 인접 빈자리 수
				for (int d = 0; d < 4; d++) { // 인접한 4방향 탐색
					int nr = i + delta[d].first;
					int nc = j + delta[d].second;
					if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {						
						if (board[nr][nc] == 0) { // 비어있는 칸이면 
							empty++;
						}
						else { // 비어있는 칸이 아니면											
							auto it = find(cur_priority.begin(), cur_priority.end(), board[nr][nc]);							
							if (it != cur_priority.end()) { // 친한친구와 인접하면																								
								pri++;
							}							
						}												
					}					
				}				
				// 4방향 탐색을 마치고 나면 선호자리 업데이트
				if (bs.pri < pri) { // 기존의 선호자리 보다 친한친구가 많은 칸이라면
					bs.empty = empty;
					bs.pri = pri;
					bs.pos = mp(i, j);
				}
				else if (bs.pri == pri && bs.empty < empty) { // 기존의 선호자리와 친한친구 수가 같다면
					// 인접한 자리중 비어있는 자리가 많은 곳으로 업데이트
					bs.empty = empty;
					bs.pos = mp(i, j);
				}
				else if (bs.pri == pri && bs.empty == empty) { // 친한친구, 빈자리 수가 모두 같으면
					if (bs.pos.first > i) { // 행번호가 작은곳으로 이동
						bs.pos = mp(i, j);
					}
					else if (bs.pos.first == i && bs.pos.second > j) { // 행이 같으면, 열번호가 작은곳
						bs.pos = mp(i, j);
					}
				}
			}
						
		}
	}
	return bs;
}

void solve() {
	for (int i = 1; i <= N*N; i++) {
		vector<int> cur_priority = priority[std_id[i]];
		BestSeat bs = find_seat(cur_priority);
		board[bs.pos.first][bs.pos.second] = std_id[i]; // 자리에 앉힘			
		num_pri[std_id[i]] = bs.pri;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int n = board[i][j];
			int pri = 0; // 인접 선호하는 친구 수			
			for (int d = 0; d < 4; d++) { // 인접한 4방향 탐색
				int nr = i + delta[d].first;
				int nc = j + delta[d].second;
				if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {					
					// 비어있는 칸이 아니면											
					auto it = find(priority[n].begin(), priority[n].end(), board[nr][nc]);
					if (it != priority[n].end()) { // 친한친구와 인접하면																								
						pri++;					
					}
				}
			}
			num_pri[n] = pri;
		}		
	}	

}
void print() {
	int ans = 0;
	for (int i = 1; i <= N*N; i++) {
		int n = num_pri[i];
		ans += pow(10, n - 1);
	}
	cout << ans;
}
int main() {
	input();
	solve();
	print();
}
