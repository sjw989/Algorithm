#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;

int N; // N x N
int fish_cnt; // 현재 남아있는 물고기 마리 수
int cur_size = 2; // 아기상어의 사이즈
int ate; // 현재 먹은 물고기의 수
int ans; // 엄마 상어의 도움없이 물고기 잡아먹는 시간
pii cur_position; // 초기상어위치
queue<pii> fish_q;
array<array<int, 21>, 21> space;
array<array<int, 21>, 21> visit;
array<int, 4> drow = {0,0,1,-1};
array<int, 4> dcol = {1,-1,0,0};

void input() {
	ifstream in("test.txt");
	in >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			in >> space[i][j];
			if (space[i][j] != 0) {				
				if (space[i][j] == 9) {
					cur_position = make_pair(i, j);						
				} // 초기 아기상어 위치 저장
				else {
					fish_q.push(make_pair(i, j));
					fish_cnt++;
				} // 물고기의 위치를 담고있는 queue
			}			
		}
	}	
}

void set_visit() {
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 20; j++) {
			visit[i][j] = 0;
		}
	}
}

void get_distance() {
	queue<pii> bfs_q; // 거리 구하는데 사용할 queue
	bfs_q.push(cur_position); // 현재 상어의 위치 넣어주기	
	while (!bfs_q.empty()) { // 현재 위치로부터 각 물고기 까지의 거리 구하기
		pii cur = bfs_q.front();				
		bfs_q.pop();
		for (int i = 0; i < 4; i++) {			
			if (cur.first + drow[i] >= 1 && cur.first+drow[i] <= N
				&& cur.second + dcol[i] >= 1 && cur.second + dcol[i] <= N
				&& space[cur.first + drow[i]][cur.second + dcol[i]] <= cur_size
				&& visit[cur.first + drow[i]][cur.second + dcol[i]] == 0) {
				// 아직 방문된 적 없고 상어가 지나갈 수 있으면
				bfs_q.push(make_pair(cur.first + drow[i], cur.second + dcol[i]));
				visit[cur.first + drow[i]][cur.second + dcol[i]] = visit[cur.first][cur.second] + 1;
			}
		}
	}		
}

void bfs() {
	queue<pii> q = fish_q;	
	while (!q.empty()) {				
		set_visit(); // visit 0으로 초기화			
		get_distance(); // 모든 물고기까지의 위치 구하기		
		queue<pii> next_q;
		pii eat_fish; // 먹을 물고기
		int eat_fish_to_shark = 987654321; // 먹을 물고기와 상어 사이의 거리
		while (!fish_q.empty()) { // 먹을 물고기 찾기			
			pii cur = fish_q.front();						
			fish_q.pop();
			if (space[cur.first][cur.second] < cur_size) { // 물고기 사이즈가 현재 상어 사이즈보다 작으면					
				if (visit[cur.first][cur.second] != 0
					&&visit[cur.first][cur.second] < eat_fish_to_shark) { // 현재 eat_fish보다 더 가까이 있으면
					if (eat_fish != make_pair(0, 0) ){
						next_q.push(eat_fish);
					}
					eat_fish = cur; // eat_fish 업데이트
					eat_fish_to_shark = visit[cur.first][cur.second];
					continue;
				}
				else if (visit[cur.first][cur.second] == eat_fish_to_shark) { // 거리가 같으면
					if (eat_fish.first > cur.first) { // cur이 더 위에 있는 경우
						if (eat_fish != make_pair(0, 0)) {
							next_q.push(eat_fish);
						}
						eat_fish = cur; // 업데이트
						continue;
					}
					else if (eat_fish.first == cur.first) { // 만약 row가 같다면
						if (eat_fish.second > cur.second) { // 더 왼쪽에 있는 경우 
							if (eat_fish != make_pair(0, 0)) {
								next_q.push(eat_fish);
							}
							eat_fish = cur; //업데이트
							continue;
						}
					}
				}				
			}
			next_q.push(cur);
		}		
		if (eat_fish_to_shark != 987654321) { // 먹을 물고기를 찾았으면			
			space[cur_position.first][cur_position.second] = 0; // 상어 위치 update			
			space[eat_fish.first][eat_fish.second] = 9; // 상어 위치 -> 물고기 위치			
			cur_position = eat_fish; // 상어 위치를 옮겨주고
			ate++;		
			ans += visit[eat_fish.first][eat_fish.second]; // 그 물고기까지 가는 시간 + 해줌
			fish_q = next_q;
			q = next_q; // 다음 q 탐색
			if (ate == cur_size) { // 먹은 수랑 사이즈가 같으면
				ate = 0; 
				cur_size++;
			}			
		}
		else { // 먹을 물고기를 못찾았으면 			
			return;
		}			
	}
}

void print() {
	cout << ans;
}

int main() {
	input();
	get_distance();	
	bfs();
	print();
}