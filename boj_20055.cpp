#include <iostream>
#include <fstream>
#include <array>
#define pii pair<int,int>
using namespace std;

int N; // �����̾��� ����
int K; // ������ 0�� ĭ�� ����
int ans = 1; // ����
array<pii, 201> belt; // (�κ��� ����, ������)

void input() {
	//ifstream in("test.txt");
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++) {
		int k;
		cin >> k;
		belt[i] = make_pair(0, k);
	}
}
void rotate() {
	array<pii, 201> new_belt;
	for (int i = 1; i <= 2 * N; i++) {
		if (i == 2 * N) {
			new_belt[1] = belt[2 * N];
		}
		else {
			new_belt[i + 1] = belt[i];
		}				
	}  	
	belt = new_belt;	
}
void solve() {	
	while (1) { // �������� 0�� ĭ�� K���� �� �� ���� �ݺ�		
		rotate(); // ��Ʈ ȸ��
		if (belt[N].first == 1) { // ������ ��ġ�� �κ��� ������ ��� ����
			belt[N].first = 0;
		}
		for (int i = N - 1; i >= 1; i--) { // ���� ���� �ö� �κ����� ����
			if (belt[i].first == 1) { // �κ��� ���� ��
				if (belt[i + 1].first == 0 && belt[i + 1].second > 0) { // ����ĭ�� ����ְ� �������� 1�̻��̸�
					// �κ� ����
					belt[i].first = 0;
					belt[i + 1].first = 1;
					belt[i + 1].second--; 					
				}			
			}
		}
		if (belt[N].first == 1) { // ������ ��ġ�� �κ��� ������ ��� ����
			belt[N].first = 0;
		}

		if (belt[1].second > 0) { // �ø��� ��ġ�� �������� 0�� �ƴϸ�
			belt[1].first = 1; // �κ� �ø���
			belt[1].second--; // ������ ����
		}
		int destroyed = 0;// �������� 0�� ĭ�� ����
		for (int i = 1; i <= 2*N; i++) { // �������� 0�� ĭ ī����			
			if (belt[i].second == 0) { 				
				destroyed++;
			}
		}		
		if (destroyed >= K) {
			return;
		}

		ans++;
	}
}
void print() {
	cout << ans;
}

int main() {
	input();
	solve();
	print();
}