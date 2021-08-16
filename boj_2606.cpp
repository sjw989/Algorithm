#include <iostream>
#include <vector>
#include <array>
using namespace std;

int N, M; // 전체 컴퓨터 수, 연결되어있는 쌍의 수
int ans;
array<vector<int>, 101> computer;
array<bool, 101> visit;

void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		computer[x].push_back(y);
		computer[y].push_back(x);
	}
}

void solve(int start) {
	ans++;	
	visit[start] = true; // 방문 표시
	vector<int> next = computer[start]; // next 컴퓨터들
	for (int n : next) {
		if (!visit[n]) {
			solve(n);			
		}
	}
}

void print() {
	cout << ans - 1; // 1번 컴퓨터 제외
}



int main() {	
	input();
	solve(1);
	print();

}