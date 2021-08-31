#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
using namespace std;

int K; // tc ����
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
	// child���� �湮�� �� ���� num[child]�� -num[parent]�� �־���
	// 1�� ����� num���� 1�̶�� ���� ��
	// ����� ��尡 2,3,4���̶��
	// num[2], [3], [4] = -1�̴�. �̷��� ���� �������� �Ѵٴ� ǥ�ø� ����
	// ���� ���� �湮�Ϸ��� �ϴ� ��尡 �̹� �湮�Ǿ��ٸ�, num���� �񱳸� ��
	// ���� ���� node�� num���� �̹� �湮�� node�� num���� ���ٸ�
	// �� �� ���� ���� ������ �� ����
	queue<int> q;
	q.push(start); // ���� node	
	visit[start] = 1; // �湮ó��	
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
				// �̹� �湮�� ���ε� ���� ��ġ�� node�� num���� ������ �� ���� ������ �� ����
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