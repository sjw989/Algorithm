#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;


int N, M; // N x M
int days;
array<int, 4> drow = {1, -1, 0, 0 };
array<int, 4> dcol = {0, 0, 1, -1 }; // 위 아래 오른쪽 왼쪽
array<array<int, 1001>, 1001> box;
array<array<int, 1001>, 1001> visit;

void input() {
	//ifstream in("test.txt");
	cin >> M >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int k;
			cin >> k;
			box[i][j] = k;			
		}
	}
}

queue<pii> get_tomato() {
	queue<pii> q; // 토마토 위치를 담을 Queue
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (box[i][j] == 1) {
				q.push(make_pair(i, j)); // 토마토가 들어있는 칸 체크
				visit[i][j] = 1; // 익은 토마토 방문체크
			}
		}
	}
	return q;
}

bool all_tomato(queue<pii> q) { 
	// 익은 토마토 주위에 1 or -1만 있으면 됨
	if (q.size() == 0) { // 익은 토마토가 하나도 없는 경우
		return false;
	}
	while (!q.empty()) {
		pii tomato = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) { // 위 아래 오른쪽 왼쪽 체크
			if (tomato.first + drow[i] <= N && tomato.first + drow[i] >= 1
				&& tomato.second + dcol[i] <= M && tomato.second + dcol[i] >= 1
				&& box[tomato.first + drow[i]][tomato.second + dcol[i]] == 0) {
				return false;
			}
		}
	}
	return true;
}

void bfs(queue<pii> q) {
	int child_num = q.size();		
	while (!q.empty()) {
		int child_cnt = 0;
		for (int i = 0; i < child_num; i++) {
			pii tomato = q.front();
			q.pop();
			for (int j = 0; j < 4; j++) { // 위 아래 오른쪽 왼쪽 체크
				if (tomato.first + drow[j] <= N && tomato.first + drow[j] >= 1
					&& tomato.second + dcol[j] <= M && tomato.second + dcol[j] >= 1
					&& box[tomato.first + drow[j]][tomato.second + dcol[j]] == 0
					&& visit[tomato.first + drow[j]][tomato.second + dcol[j]] == 0) {
					// box범위 안에있고, 현재 값이 0이며, visit또한 0이면 
					q.push(make_pair(tomato.first + drow[j], tomato.second + dcol[j])); // q에 추가
					box[tomato.first + drow[j]][tomato.second + dcol[j]] = 1; // 토마토 익음처리
					visit[tomato.first + drow[j]][tomato.second + dcol[j]] = 1; // 추가되는 토마토 위치 방문처리
					child_cnt++;
				}
			}
		}		
		child_num = child_cnt;
		days++;
	}
}

void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (box[i][j] == 0) {
				cout << -1 << "\n"; // 모두 익지 못하는 상황
				return;
			}
		}
	}
	cout << days-1 << "\n";
}

int main() {
	input();	
	queue<pii> q = get_tomato(); // input에서 익은 토마토 Queue에 넣기
	if (all_tomato(q)) {// input에서 모든 토마토가 익었는지 체크 
		cout << 0 << "\n";
	}
	else {
		bfs(q);
		print();
	}		
}