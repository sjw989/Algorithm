#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

int N, M; // ���� ����, �ٸ��� ����
int fac1, fac2; // ������ �������ִ� ���� ��ȣ
int ans;
int max_weight;
array<int, 100001> visit; // �湮����	           
array<vector<pii>, 100001> island; // i��° ���� �������ִ� �ٸ����� ����


void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		island[a].push_back(make_pair(b, c)); // ����� �� ��ȣ + �߷�
		island[b].push_back(make_pair(a, c)); // ����� ����
		max_weight = max(max_weight, c);
	}
	cin >> fac1 >> fac2;
}

bool bfs(int high_weight) {	
	for (int i = 1; i < 100001; i++) {
		visit[i] = 0;
	}

	queue<int> q;
	q.push(fac1);	// ����1���� ���� 
	visit[fac1] = 1;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		vector<pii> cur_island = island[cur]; // ���� ���� ����Ǿ��ִ� �ٸ� ����
		for (int i = 0; i < cur_island.size(); i++) {
			pii next_island = cur_island[i]; // ���� ���� ���� ����
			if (next_island.second >= high_weight && visit[next_island.first] == 0) { 
				// ���������� ����ϸ�
				
				if (next_island.first == fac2) { // ���� ���� 2�������̸�
					return true;
				}
				q.push(next_island.first);
				visit[next_island.first] = 1;
			}
		}
	}
	return false; // bfs�� 2�� ������ �������ϸ� false ����
}

void solve() {
	int lower = 1; // ������ �߷� �ּҰ�
	int upper = max_weight; // ������ �߷� �ִ밪

	while (lower <= upper) {
		int mid = (lower + upper) / 2; // ���� ã�� ����
		//cout << mid << " " << lower << " " << upper << endl;
		if (bfs(mid)) { // 2�� ������ ã�� �� ������						
			lower = mid + 1; // ���� ���Է� 2�������� ã�� �� ������ lower�� �������� �ִ밪 ã��
		}
		else { // 2�� ������ ã�� �� ������
			upper = mid - 1 ; // ���� ���Է� 2�� ���� ã�� �� ������ upper�� ���ҽ�Ű��
		}
	}

	ans = upper;
}

void print() {
	cout << ans;
}

int main() {
	input();
	solve();
	print();
}