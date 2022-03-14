#include <iostream>
#include <fstream>
#include <array>
#include <math.h>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;


int N; // �л��� ��
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
			if (board[i][j] == 0) { // ���ڸ��� ���
				int pri = 0; // ���� ��ȣ�ϴ� ģ�� ��
				int empty = 0; // ���� ���ڸ� ��
				for (int d = 0; d < 4; d++) { // ������ 4���� Ž��
					int nr = i + delta[d].first;
					int nc = j + delta[d].second;
					if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {						
						if (board[nr][nc] == 0) { // ����ִ� ĭ�̸� 
							empty++;
						}
						else { // ����ִ� ĭ�� �ƴϸ�											
							auto it = find(cur_priority.begin(), cur_priority.end(), board[nr][nc]);							
							if (it != cur_priority.end()) { // ģ��ģ���� �����ϸ�																								
								pri++;
							}							
						}												
					}					
				}				
				// 4���� Ž���� ��ġ�� ���� ��ȣ�ڸ� ������Ʈ
				if (bs.pri < pri) { // ������ ��ȣ�ڸ� ���� ģ��ģ���� ���� ĭ�̶��
					bs.empty = empty;
					bs.pri = pri;
					bs.pos = mp(i, j);
				}
				else if (bs.pri == pri && bs.empty < empty) { // ������ ��ȣ�ڸ��� ģ��ģ�� ���� ���ٸ�
					// ������ �ڸ��� ����ִ� �ڸ��� ���� ������ ������Ʈ
					bs.empty = empty;
					bs.pos = mp(i, j);
				}
				else if (bs.pri == pri && bs.empty == empty) { // ģ��ģ��, ���ڸ� ���� ��� ������
					if (bs.pos.first > i) { // ���ȣ�� ���������� �̵�
						bs.pos = mp(i, j);
					}
					else if (bs.pos.first == i && bs.pos.second > j) { // ���� ������, ����ȣ�� ������
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
		board[bs.pos.first][bs.pos.second] = std_id[i]; // �ڸ��� ����			
		num_pri[std_id[i]] = bs.pri;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int n = board[i][j];
			int pri = 0; // ���� ��ȣ�ϴ� ģ�� ��			
			for (int d = 0; d < 4; d++) { // ������ 4���� Ž��
				int nr = i + delta[d].first;
				int nc = j + delta[d].second;
				if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {					
					// ����ִ� ĭ�� �ƴϸ�											
					auto it = find(priority[n].begin(), priority[n].end(), board[nr][nc]);
					if (it != priority[n].end()) { // ģ��ģ���� �����ϸ�																								
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
