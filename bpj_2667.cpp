#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#define pii pair<int,int>
using namespace std;


int N; // ���� ũ��
int ans; // ���� ��
int cnt; // ���� �� ���� ��
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
	cnt = 0; // ���� �� ���� �� �ʱ�ȭ
	queue<pii> q;
	q.push(make_pair(row, col)); // �������� q�� �߰� 	
	visit[row][col] = 1; // �������� �湮ó��

	while (!q.empty()) {		
		pii start = q.front();		
		q.pop();		
		cnt++; // ���� �� �� �� ++		
		
		if (start.first - 1 >= 1) { // ���� �˻�
			if (visit[start.first - 1][start.second] == 0 && board[start.first - 1][start.second] == '1') {
				// �湮�� �� ���� && �ش� ĭ�� �ǹ��� ������
				q.push(make_pair(start.first - 1, start.second)); // q�� �߰�
				visit[start.first - 1][start.second] = 1;
			}
		}
		
		if(start.first + 1 <= N) { // �Ʒ��� �˻�
			if (visit[start.first + 1][start.second] == 0 && board[start.first + 1][start.second] == '1'){
				// �湮�� �� ���� && �ش� ĭ�� �ǹ��� ������
				q.push(make_pair(start.first + 1, start.second)); // q�� �߰�
				visit[start.first + 1][start.second] = 1;
			}
		}

		if (start.second -1  >= 1) { // ���� �˻�
			if (visit[start.first][start.second - 1] == 0 && board[start.first][start.second - 1] == '1') {
				// �湮�� �� ���� && �ش� ĭ�� �ǹ��� ������
				q.push(make_pair(start.first, start.second - 1)); // q�� �߰�
				visit[start.first ][start.second - 1] = 1;
			}
		}

		if (start.second + 1 <= N) { // ������ �˻�
			if (visit[start.first][start.second + 1] == 0 && board[start.first][start.second + 1] == '1') {
				// �湮�� �� ���� && �ش� ĭ�� �ǹ��� ������
				q.push(make_pair(start.first, start.second + 1)); // q�� �߰�
				visit[start.first][start.second + 1] = 1;
			}
		}
	}
}

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) { 
			if (board[i][j] == '1' && visit[i][j] == 0) { // �湮���� ���� �� ã��								
				ans++; // ���� �� ++
				bfs(i, j); // bfs�� ���� Ž��
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