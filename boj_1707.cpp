#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
using namespace std;

int K; // tc 개수
int V, E;
array<vector<int>, 20001> tree;
array<int, 20001> num;
array<int, 20001> visit;

void init() {
	for (int i = 1; i <= 20000; i++) {
		tree[i].clear();
		visit[i] = 0;
		num[i] = 0;
	}
}

void input() {	
	cin >> V >> E;
	init();
	for (int i = 0; i < E; i++) {
		int n1, n2;
		cin >> n1 >> n2;
		tree[n1].push_back(n2);
		tree[n2].push_back(n1);
	}
}

bool bfs(int start) {
	// child들을 방문할 때 마다 num[child]에 -num[parent]를 넣어줌
	// 1번 노드의 num값이 1이라고 헀을 때
	// 연결된 노드가 2,3,4번이라면
	// num[2], [3], [4] = -1이다. 이렇게 서로 떨어져야 한다는 표시를 해줌
	// 만약 내가 방문하려고 하는 노드가 이미 방문되었다면, num값을 비교를 함
	// 만약 현재 node의 num값과 이미 방문된 node의 num값이 같다면
	// 이 두 노드는 서로 떨어질 수 없음
	queue<int> q;
	q.push(start); // 시작 node	
	visit[start] = 1; // 방문처리	
	num[start] = 1;

	while (!q.empty()) {
	
		int n = q.front();		
		q.pop();
		vector<int> child = tree[n];
		for (int i : child) {
			if (visit[i] == 0) {
				visit[i] = 1;
				num[i] = -num[n];
				q.push(i);
			}
			else {
				// 이미 방문한 곳인데 현재 위치한 node와 num값이 같으면 이 둘은 떨어질 수 없음
				if (num[i] == num[n]) {
					return 0;
				}								
			}
		}
		
	}
	return 1;
}

int main() {
	//ifstream in("test.txt");
	cin >> K;
	for (int i = 0; i < K; i++) {
		input();
		int ans = 1;
		for (int j = 1; j <= V; j++) {
			if (visit[j] == 0) {
				ans *= bfs(j);
			}
		}
		if (ans == 1) {
			cout << "YES" << "\n";
		}
		else {
			cout << "NO" << "\n";
		}
	}
}