#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#define pii pair<int,int>
using namespace std;

int N, M, D; // N x M , �ü��� ���ݰŸ� D
int maximum;
array<array<int, 16>, 16> board;
queue<pii> enemy;
vector<array<pii,4>> archer; // 1,2,3�� �ü� ��ġ

void input() {
	//ifstream in("test.txt");
	cin >> N >> M >> D;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int k;
			cin >> k;
			board[i][j] = k;			
		}
	}	
	// ���� ���ǿ� ���� ������ ���� �������ִ� ������ Ž��
	for (int i = N; i >= 1; i--) {
		for (int j = 1; j <= M; j++) {
			if (board[i][j] == 1) {
				enemy.push(make_pair(i, j));				
			}
		}
	}
}

void get_archer() {
	array<pii, 4> position;
	for (int i = 1; i <= M-2; i++) {
		for (int j = i + 1; j <= M-1; j++) {
			for (int k = j+1; k <= M; k++) {
				position[1] = make_pair(N + 1, i);
				position[2] = make_pair(N + 1, j);
				position[3] = make_pair(N + 1, k);
				archer.push_back(position);				
			}
		}
	}	
}

int calc(pii a, pii e) {
	return abs(a.first - e.first) + abs(a.second - e.second);
}

int bfs(array<pii,4> pos) {		
	queue<pii > q = enemy;	
	int kill = 0; // ���� ���� ��
	
	while (!q.empty()) {		
		array<array<int, 16>, 16> visit;
		for (int i = 0; i <= 15; i++) {
			for (int j = 0; j <= 15; j++) {
				visit[i][j] = 0;
			}
		}
		for (int i = 1; i <= 3; i++) { // ��� �ü��� Ž��
			queue<pii> sub = q;			
			pii dead = make_pair(100,100); // �װԵ� ��
			
			while (!sub.empty()) {
				pii e = sub.front();
				sub.pop();
				int dis = calc(pos[i],e); //���� �ü����� �Ÿ�
				if (dis <= D) { // �ü� �������� ���̸�					
					if (calc(e, pos[i]) < calc(dead, pos[i])) { // �Ÿ��� �� ª�� �� �߽߰�			
						dead = e; // �װԵ� �� ����
					}
					else if (calc(e, pos[i]) == calc(dead, pos[i])) { // �Ÿ��� ���ٸ�
						if (dead.second > e.second) { // ���� ���ʿ� �ִ� �ָ� dead�� �־���
							dead = e;
						}
					}					
				} 
			}			
			if (dead.first != 100 && dead.second != 100) {
				if (visit[dead.first][dead.second] == 0) { // �ش� ���� ���� ���� �� ������				
					kill++; // kill �� ++				
					visit[dead.first][dead.second] = 1; // �� ���� ó��				
				}
			}
								
		}		
		queue<pii> next_q;
		while (!q.empty()) {
			pii e = q.front();
			q.pop();			
			if (visit[e.first][e.second] == 0) { // ��� ������ Ž���ϸ鼭 �����ֵ��� ���ְ� �����ִ� �ֵ��� ����������
				if (e.first + 1 <= N) { // ���� �����ϸ�
					next_q.push(make_pair(e.first + 1, e.second)); // ����������
				}
			}
		}		
		q = next_q;
	}	
	return kill;
}

int main() {
	input(); // input
	get_archer(); // �ü� ��ġ ����� ��			
	for (array<pii, 4> pos : archer) {				
		maximum = max(maximum, bfs(pos));					
	}
	cout << maximum;
}