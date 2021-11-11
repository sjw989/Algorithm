#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#include <iomanip>
#define pii pair<int,int>
using namespace std;


typedef struct Guest{
	int start_row, start_col;
	int dest_row, dest_col;
};

int N, M, G; // 지도크기 N x N, 승객 수 M, 초기 가스 G
int dist; // 한 승객을 목적지까지 태워주기 위해 사용한 연료
pii cur_taxi; // 현재 택시위치
array<array<int, 21>, 21> board; // board N x N
array<array<pii, 21>, 21> dest; // 승객의 도착지를 담을 array
array<int, 4> drow = { 0, 0, 1, -1 };
array<int, 4> dcol = { 1,-1, 0, 0 };

void input() {
	//ifstream in("test.txt");	
	cin >> N >> M >> G;	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {			
			cin >> board[i][j];
		}
	}
	int cur_r, cur_c;
	cin >> cur_r >> cur_c;	
	cur_taxi = make_pair(cur_r, cur_c);	
	for (int i = 0; i < M; i++) {
		Guest g;
		cin >> g.start_row >> g.start_col >> g.dest_row >> g.dest_col;
		board[g.start_row][g.start_col] = -1; // 승객 표시
		dest[g.start_row][g.start_col] = make_pair(g.dest_row, g.dest_col);
	}
}

pii find_guest() {	
	queue<pii> q;
	q.push(cur_taxi);	
	array <array<int, 21>, 21> visit = { 0 };
	array <array<int, 21>, 21> use_gas = { 0 };
	visit[cur_taxi.first][cur_taxi.second] = 1;	
	pii g = make_pair(25,25); // 태울 손님, 초기값으로 매우 큰값을 넣어줌	
	dist = 100; // 택시와 손님 거리, 초기값으로 매우 큰값을 넣어줌
	if (board[cur_taxi.first][cur_taxi.second] == -1) { // 택시위치 == 손님위치인 경우
		dist = 0;
		g = cur_taxi;
		board[g.first][g.second] = 0;// 손님 board에서 없애주기
		return g;
	}
	while (!q.empty()) { // 택시가 board를 완전탐색하면서 태울 손님을 결정함
		pii cur = q.front();			
		q.pop();		
		for (int i = 0; i < 4; i++) {			
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];													
			if (next_row >= 1  && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] == 0 && board[next_row][next_col] != 1) { // 다음 칸을 방문하지 않았고 벽이 아닌경우				
				visit[next_row][next_col] = 1; // 방문처리
				use_gas[next_row][next_col] = use_gas[cur.first][cur.second] +  1 ; // 시작지점으로 부터의 거리 저장
				if (board[next_row][next_col] == -1) { // 다음 칸에 손님이 있는 경우
					if (use_gas[next_row][next_col] < dist) { // 현재손님 보다 더 가까운 곳에 손님이 있는 경우
						dist = use_gas[next_row][next_col];
						g = make_pair(next_row, next_col);
					}
					else if (use_gas[next_row][next_col] == dist) { // 현재 손님과 같은 거리에 다른 손님이 있는경우
						if (next_row < g.first) { // row 가 더작은 손님을 선택
							dist = use_gas[next_row][next_col];
							g = make_pair(next_row, next_col);
						}
						else if (next_row == g.first) { // row 가 같다면
							if (next_col < g.second) { // col이 더 작은 값을 선택
								dist = use_gas[next_row][next_col];
								g = make_pair(next_row, next_col);
							}
						}
					}
				}				
				else { 
					q.push(make_pair(next_row, next_col));
				}
			}
		}		
	}
	if (g.first != 25) {		
		board[g.first][g.second] = 0;// 손님 board에서 없애주기
	}
	return g; // (25,25)가 리턴되면 손님이 없다는 의미
}

bool go_dest(pii pick_guest) {	
	queue<pii> q;
	q.push(pick_guest);
	array <array<int, 21>, 21> visit = { 0 };
	array <array<int, 21>, 21> use_gas = { 0 };
	visit[pick_guest.first][pick_guest.second] = 1;
	dist = 100;
	while (!q.empty()) { // 손님의 목적지 최단거리 탐색
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];
			if (next_row >= 1 && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] == 0 && board[next_row][next_col] != 1) { // 방문하지 않았고 벽이 아닌경우				
				visit[next_row][next_col] = 1;
				use_gas[next_row][next_col] = use_gas[cur.first][cur.second] + 1;

				if (next_row == dest[pick_guest.first][pick_guest.second].first
					&& next_col == dest[pick_guest.first][pick_guest.second].second) { // next가 손님의 목적지와 같으면					

					cur_taxi = make_pair(next_row, next_col); // 택시 위치 update
					dist = use_gas[next_row][next_col];
					return true;
				}
				else {					
					q.push(make_pair(next_row, next_col));
				}				
			}
		}
	}
	return false;
}

int solve() {	
	while (M != 0 && G > 0) { // 승객의 수가 0이거나, 연료가 다 떨어질 때 까지 반복
		pii pick_guest = find_guest();
		if (pick_guest.first == 25) { // 택시가 손님을 못 찾은 경우
			return -1;
		} 
		if (dist >= G) { // 만약 손님을 찾는데 내가 가진 연료보다 더 많이 사용한 경우 목적지에 갈 수 없으니
			return -1; // -1을 return
		}
		else { // 손님을 찾는데 가진 연료로 충분했던 경우
			G -= dist; // 현재 연로 업데이트						
			if (go_dest(pick_guest)) { // 손님의 목적지까지 가는 경로가 존재하는 경우
				if (dist <= G) { // 목적지 까지 가기위해 사용해야하는 연료가 충분한 경우
					M--; // 손님 수 -1
					G -= dist; // 현재 연로 업데이트
					G += dist * 2;
				}				
				else { // 연료가 충분하지 않은 경우
					return -1;
				}
			}
			else {
				return -1;
			}
		}						
	}
	if (M == 0) { // 모든 손님을 다 이동시킨 경우
		return G;
	}
	return -1; // 연료가 부족했던 경우
}

void print(int ans) {	
	cout << ans;
}
int main() {
	input();		
	int ans = solve();
	print(ans);
}






