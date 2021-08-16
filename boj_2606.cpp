#include <iostream>
#include <vector>
#include <array>
using namespace std;

int N, M; // ��ü ��ǻ�� ��, ����Ǿ��ִ� ���� ��
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
	visit[start] = true; // �湮 ǥ��
	vector<int> next = computer[start]; // next ��ǻ�͵�
	for (int n : next) {
		if (!visit[n]) {
			solve(n);			
		}
	}
}

void print() {
	cout << ans - 1; // 1�� ��ǻ�� ����
}



int main() {	
	input();
	solve(1);
	print();

}