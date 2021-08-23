#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;


int N, M; // N x M
int days;
array<int, 4> drow = {1, -1, 0, 0 };
array<int, 4> dcol = {0, 0, 1, -1 }; // �� �Ʒ� ������ ����
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
	queue<pii> q; // �丶�� ��ġ�� ���� Queue
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (box[i][j] == 1) {
				q.push(make_pair(i, j)); // �丶�䰡 ����ִ� ĭ üũ
				visit[i][j] = 1; // ���� �丶�� �湮üũ
			}
		}
	}
	return q;
}

bool all_tomato(queue<pii> q) { 
	// ���� �丶�� ������ 1 or -1�� ������ ��
	if (q.size() == 0) { // ���� �丶�䰡 �ϳ��� ���� ���
		return false;
	}
	while (!q.empty()) {
		pii tomato = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) { // �� �Ʒ� ������ ���� üũ
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
			for (int j = 0; j < 4; j++) { // �� �Ʒ� ������ ���� üũ
				if (tomato.first + drow[j] <= N && tomato.first + drow[j] >= 1
					&& tomato.second + dcol[j] <= M && tomato.second + dcol[j] >= 1
					&& box[tomato.first + drow[j]][tomato.second + dcol[j]] == 0
					&& visit[tomato.first + drow[j]][tomato.second + dcol[j]] == 0) {
					// box���� �ȿ��ְ�, ���� ���� 0�̸�, visit���� 0�̸� 
					q.push(make_pair(tomato.first + drow[j], tomato.second + dcol[j])); // q�� �߰�
					box[tomato.first + drow[j]][tomato.second + dcol[j]] = 1; // �丶�� ����ó��
					visit[tomato.first + drow[j]][tomato.second + dcol[j]] = 1; // �߰��Ǵ� �丶�� ��ġ �湮ó��
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
				cout << -1 << "\n"; // ��� ���� ���ϴ� ��Ȳ
				return;
			}
		}
	}
	cout << days-1 << "\n";
}

int main() {
	input();	
	queue<pii> q = get_tomato(); // input���� ���� �丶�� Queue�� �ֱ�
	if (all_tomato(q)) {// input���� ��� �丶�䰡 �;����� üũ 
		cout << 0 << "\n";
	}
	else {
		bfs(q);
		print();
	}		
}