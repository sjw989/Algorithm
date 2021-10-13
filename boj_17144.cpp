#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;

int R, C, T; // 방 크기 R x C, T 초후
array<array<int, 51>, 51> room;
array<array<int, 51>, 51> new_room;
array<array<int, 51>, 51> visit;
array<array<pii, 51>, 51> spread_data;
array<int, 4> drow = {1,-1,0,0};
array<int, 4> dcol = {0,0,-1,1};
array<int, 2> cleaner;
queue<pii> dust; // 미세먼지 좌표들

void input() {
	//ifstream in("test.txt");
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> room[i][j];
			if (room[i][j] != 0  && room[i][j] != -1 ) {
				dust.push(make_pair(i, j)); // 초기 미세먼지들
			}
			else if(room[i][j] == -1){
				for (int k = 0; k < 2; k++) {
					if (cleaner[k] == 0) {
						cleaner[k] = i; // 공기청정기 row 넣어주기
						break;
					}
				}
			}
		}
	}	
}

void spread_dust() {
	
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= 50; j++) {
			visit[i][j] = 0;
			spread_data[i][j] = make_pair(0, 0);
		}
	}	
	
	queue<pii> next_dust; // 확산된 후 미세먼지 좌표들
	while (!dust.empty()) {
		pii cur_dust = dust.front();
		dust.pop();
		
		int value = room[cur_dust.first][cur_dust.second];
		for (int i = 0; i < 4; i++) {
			int next_row = cur_dust.first + drow[i];
			int next_col = cur_dust.second + dcol[i];
			if (next_row >= 1 && next_row <= R && next_col >= 1 && next_col <= C
				&& room[next_row][next_col] != -1) {				
				// 확산 조건 : 공기청정기가 없다, room 안이다
				spread_data[cur_dust.first][cur_dust.second].first++; // cur에서 몇 번 퍼져나갔는지
				spread_data[next_row][next_col].second += value / 5; // 다른 칸에서 몇 번 확산되어왔는지								
			}
		}
		
	}
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (room[i][j] != -1) {
				room[i][j] = room[i][j] - (room[i][j] /5 * spread_data[i][j].first) + spread_data[i][j].second;
				if (room[i][j] != 0) {
					next_dust.push(make_pair(i, j));
				}
			}
		}
	}	
	dust = next_dust; // 미세먼지 좌표 업데이트	
}


void on_cleaner() {	
	
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= 50; j++) {
			new_room[i][j] = 0;
		}
	}	
	new_room[cleaner[0]][1] = -1;
	new_room[cleaner[1]][1] = -1;
	queue<pii> new_dust;
	while (!dust.empty()) {
		pii cur_dust = dust.front();
		dust.pop();				

		int row = cur_dust.first, col = cur_dust.second;

		if (row != cleaner[0] && row != cleaner[1] && row != 1 && row != R
			&& col != 1 && col != C) { // 공기청정기에 영향받지 않는 먼지						
			new_room[row][col] = room[row][col]; // 값 그대로 넣어줌			
			new_dust.push(make_pair(row, col));
		}
		else { // 공기청정기에 영향을 받는 먼지들
			if (row == cleaner[0] && col > 1 && col < C) { // 위 순환 오른쪽
				new_room[row][col + 1] = room[row][col];
				new_dust.push(make_pair(row, col + 1));
			}
			if (row > 1 && row <= cleaner[0] && col == C) { // 위 순환 위쪽
				new_room[row-1][col] = room[row][col];
				new_dust.push(make_pair(row-1, col));
			}
			if (row == 1 && col > 1 && col <= C) { // 위 순환 왼쪽
				new_room[row][col - 1] = room[row][col];
				new_dust.push(make_pair(row, col - 1));
			}
			if (row >= 1 && row < cleaner[0] - 1 && col == 1) { // 위 순환 아래쪽
				new_room[row + 1][col] = room[row][col];
				new_dust.push(make_pair(row+1, col));
			}

			if (row == cleaner[1] && col > 1 && col < C) { // 아래 순환 오른쪽
				new_room[row][col + 1] = room[row][col];
				new_dust.push(make_pair(row, col + 1));
			}
			if (row < R && row >= cleaner[1] && col == C) { // 아래 순환 아래쪽
				new_room[row + 1][col] = room[row][col];
				new_dust.push(make_pair(row + 1, col));
			}
			if (row == R && col > 1 && col <= C) { // 아래 순환 왼쪽
				new_room[row][col - 1] = room[row][col];
				new_dust.push(make_pair(row, col - 1));
			}
			if (row <= R && row > cleaner[1] + 1  && col == 1) { // 아래 순환 위쪽
				new_room[row - 1][col] = room[row][col];
				new_dust.push(make_pair(row - 1, col));
			}
		}
	}
	room = new_room;
	dust = new_dust;
}

void solve() {	
	while (T > 0) {		
		spread_dust(); // 먼지 확산시키기			
		on_cleaner(); // 공기청정기 작동시키기
		T--; // 시간 줄이기
	}
}

void print() {
	int ans = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (room[i][j] != -1 && room[i][j] != 0) {
				ans += room[i][j];
			}
		}
	}
	cout << ans;
}


int main() {
	input();
	solve();
	print();
}