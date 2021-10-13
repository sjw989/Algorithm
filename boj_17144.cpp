#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;

int R, C, T; // �� ũ�� R x C, T ����
array<array<int, 51>, 51> room;
array<array<int, 51>, 51> new_room;
array<array<int, 51>, 51> visit;
array<array<pii, 51>, 51> spread_data;
array<int, 4> drow = {1,-1,0,0};
array<int, 4> dcol = {0,0,-1,1};
array<int, 2> cleaner;
queue<pii> dust; // �̼����� ��ǥ��

void input() {
	//ifstream in("test.txt");
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> room[i][j];
			if (room[i][j] != 0  && room[i][j] != -1 ) {
				dust.push(make_pair(i, j)); // �ʱ� �̼�������
			}
			else if(room[i][j] == -1){
				for (int k = 0; k < 2; k++) {
					if (cleaner[k] == 0) {
						cleaner[k] = i; // ����û���� row �־��ֱ�
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
	
	queue<pii> next_dust; // Ȯ��� �� �̼����� ��ǥ��
	while (!dust.empty()) {
		pii cur_dust = dust.front();
		dust.pop();
		
		int value = room[cur_dust.first][cur_dust.second];
		for (int i = 0; i < 4; i++) {
			int next_row = cur_dust.first + drow[i];
			int next_col = cur_dust.second + dcol[i];
			if (next_row >= 1 && next_row <= R && next_col >= 1 && next_col <= C
				&& room[next_row][next_col] != -1) {				
				// Ȯ�� ���� : ����û���Ⱑ ����, room ���̴�
				spread_data[cur_dust.first][cur_dust.second].first++; // cur���� �� �� ������������
				spread_data[next_row][next_col].second += value / 5; // �ٸ� ĭ���� �� �� Ȯ��Ǿ�Դ���								
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
	dust = next_dust; // �̼����� ��ǥ ������Ʈ	
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
			&& col != 1 && col != C) { // ����û���⿡ ������� �ʴ� ����						
			new_room[row][col] = room[row][col]; // �� �״�� �־���			
			new_dust.push(make_pair(row, col));
		}
		else { // ����û���⿡ ������ �޴� ������
			if (row == cleaner[0] && col > 1 && col < C) { // �� ��ȯ ������
				new_room[row][col + 1] = room[row][col];
				new_dust.push(make_pair(row, col + 1));
			}
			if (row > 1 && row <= cleaner[0] && col == C) { // �� ��ȯ ����
				new_room[row-1][col] = room[row][col];
				new_dust.push(make_pair(row-1, col));
			}
			if (row == 1 && col > 1 && col <= C) { // �� ��ȯ ����
				new_room[row][col - 1] = room[row][col];
				new_dust.push(make_pair(row, col - 1));
			}
			if (row >= 1 && row < cleaner[0] - 1 && col == 1) { // �� ��ȯ �Ʒ���
				new_room[row + 1][col] = room[row][col];
				new_dust.push(make_pair(row+1, col));
			}

			if (row == cleaner[1] && col > 1 && col < C) { // �Ʒ� ��ȯ ������
				new_room[row][col + 1] = room[row][col];
				new_dust.push(make_pair(row, col + 1));
			}
			if (row < R && row >= cleaner[1] && col == C) { // �Ʒ� ��ȯ �Ʒ���
				new_room[row + 1][col] = room[row][col];
				new_dust.push(make_pair(row + 1, col));
			}
			if (row == R && col > 1 && col <= C) { // �Ʒ� ��ȯ ����
				new_room[row][col - 1] = room[row][col];
				new_dust.push(make_pair(row, col - 1));
			}
			if (row <= R && row > cleaner[1] + 1  && col == 1) { // �Ʒ� ��ȯ ����
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
		spread_dust(); // ���� Ȯ���Ű��			
		on_cleaner(); // ����û���� �۵���Ű��
		T--; // �ð� ���̱�
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