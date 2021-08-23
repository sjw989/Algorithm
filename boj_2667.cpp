#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#define pii pair<int,int>
using namespace std;


int N; // 지도 크기
int ans; // 단지 수
int cnt; // 단지 내 집의 수
vector<int> result;
array<array<char, 26>, 26> board;
array<array<int, 26>, 26> visit;

void input() {
	//ifstream in("test.txt");
	cin >> N;
	string k ;
	for (int i = 1; i <= N; i++) {
		cin >> k;	
		for (int j = 1; j <= N; j++) {
			board[i][j] = k[j-1];			
		}		
	}
}


void bfs(int row, int col) {
	cnt = 0; // 단지 내 집의 수 초기화
	queue<pii> q;
	q.push(make_pair(row, col)); // 시작지점 q에 추가 	
	visit[row][col] = 1; // 시작지점 방문처리

	while (!q.empty()) {		
		pii start = q.front();		
		q.pop();		
		cnt++; // 단지 내 집 수 ++		
		
		if (start.first - 1 >= 1) { // 위쪽 검사
			if (visit[start.first - 1][start.second] == 0 && board[start.first - 1][start.second] == '1') {
				// 방문한 적 없고 && 해당 칸에 건물이 있으면
				q.push(make_pair(start.first - 1, start.second)); // q에 추가
				visit[start.first - 1][start.second] = 1;
			}
		}
		
		if(start.first + 1 <= N) { // 아래쪽 검사
			if (visit[start.first + 1][start.second] == 0 && board[start.first + 1][start.second] == '1'){
				// 방문한 적 없고 && 해당 칸에 건물이 있으면
				q.push(make_pair(start.first + 1, start.second)); // q에 추가
				visit[start.first + 1][start.second] = 1;
			}
		}

		if (start.second -1  >= 1) { // 왼쪽 검사
			if (visit[start.first][start.second - 1] == 0 && board[start.first][start.second - 1] == '1') {
				// 방문한 적 없고 && 해당 칸에 건물이 있으면
				q.push(make_pair(start.first, start.second - 1)); // q에 추가
				visit[start.first ][start.second - 1] = 1;
			}
		}

		if (start.second + 1 <= N) { // 오른쪽 검사
			if (visit[start.first][start.second + 1] == 0 && board[start.first][start.second + 1] == '1') {
				// 방문한 적 없고 && 해당 칸에 건물이 있으면
				q.push(make_pair(start.first, start.second + 1)); // q에 추가
				visit[start.first][start.second + 1] = 1;
			}
		}
	}
}

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) { 
			if (board[i][j] == '1' && visit[i][j] == 0) { // 방문하지 않은 집 찾기								
				ans++; // 단지 수 ++
				bfs(i, j); // bfs로 단지 탐색
				result.push_back(cnt);				
			}
		}
	}
}

void print() {
	cout << ans << "\n";
	sort(result.begin(), result.end());
	for (auto k : result) {
		cout << k << "\n";
	}
}


int main() {
	input();
	solve();
	print();
}
