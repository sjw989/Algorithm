#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, V;
array<bool, 1001> visit;
array<vector<int>, 1001> node;

void input() {
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		node[x].push_back(y);
		node[y].push_back(x);
	}
}

void dfs(int idx) {
	cout << idx << " ";
	visit[idx] = true;
	vector<int> next = node[idx];
	sort(next.begin(), next.end());
	for (auto n : next) {
		if (!visit[n]) {
			dfs(n);
		}
	}
}

void bfs(int start) {
	queue<int> q;
	q.push(V); // 시작점 q에 넣어주기
	visit[V] = true;
	while (!q.empty()) {
		int idx = q.front();
		cout << idx << " ";
		q.pop();		
		vector<int> next = node[idx];
		sort(next.begin(), next.end());
		for (auto n : next) {
			if (!visit[n]) {
				q.push(n);			
				visit[n] = true;
			}
		}
	}
}

int main() {
	cin >> N >> M >> V;
	input();
	dfs(V);
	cout << endl;
	visit = { false };
	bfs(V);
	cout << endl;
}