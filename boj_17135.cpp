#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#define pii pair<int,int>
using namespace std;

int N, M, D; // N x M , 궁수의 공격거리 D
int maximum;
array<array<int, 16>, 16> board;
queue<pii> enemy;
vector<array<pii,4>> archer; // 1,2,3번 궁수 위치

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
	// 문제 조건에 따라 적들의 가장 가까이있는 적부터 탐색
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
	int kill = 0; // 죽은 적의 수
	
	while (!q.empty()) {		
		array<array<int, 16>, 16> visit;
		for (int i = 0; i <= 15; i++) {
			for (int j = 0; j <= 15; j++) {
				visit[i][j] = 0;
			}
		}
		for (int i = 1; i <= 3; i++) { // 모든 궁수를 탐색
			queue<pii> sub = q;			
			pii dead = make_pair(100,100); // 죽게될 적
			
			while (!sub.empty()) {
				pii e = sub.front();
				sub.pop();
				int dis = calc(pos[i],e); //적과 궁수와의 거리
				if (dis <= D) { // 궁수 사정범위 내이면					
					if (calc(e, pos[i]) < calc(dead, pos[i])) { // 거리가 더 짧은 적 발견시			
						dead = e; // 죽게될 적 갱신
					}
					else if (calc(e, pos[i]) == calc(dead, pos[i])) { // 거리가 같다면
						if (dead.second > e.second) { // 가장 왼쪽에 있는 애를 dead에 넣어줌
							dead = e;
						}
					}					
				} 
			}			
			if (dead.first != 100 && dead.second != 100) {
				if (visit[dead.first][dead.second] == 0) { // 해당 적이 아직 죽은 적 없으면				
					kill++; // kill 수 ++				
					visit[dead.first][dead.second] = 1; // 적 죽음 처리				
				}
			}
								
		}		
		queue<pii> next_q;
		while (!q.empty()) {
			pii e = q.front();
			q.pop();			
			if (visit[e.first][e.second] == 0) { // 모든 적들을 탐색하면서 죽은애들은 빼주고 남아있는 애들은 전진시켜줌
				if (e.first + 1 <= N) { // 전진 가능하면
					next_q.push(make_pair(e.first + 1, e.second)); // 전진시켜줌
				}
			}
		}		
		q = next_q;
	}	
	return kill;
}

int main() {
	input(); // input
	get_archer(); // 궁수 위치 경우의 수			
	for (array<pii, 4> pos : archer) {				
		maximum = max(maximum, bfs(pos));					
	}
	cout << maximum;
}