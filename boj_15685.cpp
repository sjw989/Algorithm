#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#define pii pair<int,int>
#define MAX 100+1
using namespace std;

typedef struct Dragon {	
	int r, c; // ������
	int d; // ���۹���
	int g; // ����
	vector<pii> point; // ���� �巡��Ŀ�갡 �������ִ� ��ǥ��	
	Dragon(int x, int y, int dir, int gene) {
		r = x;
		c = y;
		d = dir;
		g = gene;
	}
};

array<array<int, MAX>, MAX> board;
array<int, 4 > drow = {0,-1,0,1};
array<int, 4 > dcol = {1,0,-1,0};
vector<Dragon> dragons; 
int N; // N x N 

void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		Dragon dragon = Dragon(x, y, d, g);
		dragon.point.push_back(make_pair(x, y));
		dragon.point.push_back(make_pair(x+dcol[d], y+drow[d]));
		dragons.push_back(dragon);
	}
}

pii rotate(pii point, pii end) {
	int x = point.first-end.first;
	int y = point.second-end.second;
	return make_pair((-1)*y + end.first, x + end.second);
}

void solve() {					
	for (Dragon& cur_dragon : dragons) {		
		for (int i = 0; i < cur_dragon.g; i++) { // �巡���� ����� ��ŭ �ݺ�						
			pii end_point = cur_dragon.point.back(); // ����
			int size = cur_dragon.point.size();
			for (int j = size-1; j >=0; j--) { // ��ü ��ǥ�� ���ؼ� ȸ��				
				pii new_point = rotate(cur_dragon.point[j], end_point);					
				cur_dragon.point.push_back(new_point);
			}						
		}			
	}	
	for (Dragon dragon : dragons) {
		vector<pii> cur_point = dragon.point;
		for (pii p : cur_point) {			
			if (p.first >= 0 && p.first <= MAX &&
				p.second >= 0 && p.second <= MAX) {
				board[p.second][p.first] = 1;
			}
		}				
	}			
	int ans = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i][j + 1] == 1
				&& board[i + 1][j + 1] == 1) {
				ans++;
			}
		}
	}
	cout << ans;
}

void print() {

}

int main() {	
	

	input();
	solve();
	print();
}
