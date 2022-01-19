#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <array>
#define MIN -12345678
using namespace std;

string N; // �̵��Ϸ��� ä��
int M; // ���峭 ��ư�� ����
int ans; // ����
bool remote[10]; // ������ 0 ~ 9

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	memset(remote, true, sizeof(remote));	
	if (M > 0) { // ���峭 ��ư�� �ִ� ���
		for (int i = 0; i < M; i++) {
			int k;
			cin >> k;
			remote[k] = false; // ��ư ���� ó��
		}
	}
}

bool can_go(int cur) {
	string s = to_string(cur); // ���� ä��		
	for (int i = 0; i < s.size(); i++) {				
		if (!remote[s[i] - '0']) { // ���� �� ���� ��ư�� �����ϸ�
			return false;
		}
	}		
	return true; // ��� ��ư���� �̵��� �� �ִ� ���

}

int find_up() {
	int n = stoi(N);	
	// ��� ��ư�� ���峪�� �̵��Ұ����� ��� ����ó���ؼ� ���ѷ��� �ȵ�	
	while (true) { // ��ư���� �̵������� ä�� ã���� ���� Ž��		
		if (can_go(n)) {						
			return n;
		}
		n++;
	}		
}

int find_down() {
	int n = stoi(N) - 1;
	for (int i = n; i >= 0; i--) {
		if (can_go(i)) {
			return i;
		}
	}
	return -1;
}

int get_nearest(int upper, int lower, int single) {
	int n = stoi(N);
	int up = abs(upper - n) + to_string(upper).size();
	int down = abs(lower - n) + to_string(lower).size();		
	return min(single, min(up, down));
}

void solve() {		
	// 0�� �̵������Ѱ��� ������ lower case
	// 0�� �ƴ� �ٸ� ��ư���� �̵������Ѱ��� upper case ����
	bool only_zero = true;
	for (int i = 1; i < 10; i++) {
		if (remote[i]) {
			only_zero = false;
			break;
		}
	}

	// ���ؾ��� ��
	// (N ~ ���Ѵ�) vs (0 ~ N -1) vs  + or - �� ������ ���

	int upper = 0;
	if (!only_zero) {
		upper = find_up(); // N ~ ���Ѵ� -> N�̻��� �� �� ���� ����� ��
	}	
	int lower = find_down(); // 0 ~ N-1 -> N ������ �� �� ���� ����� ��
	if (lower == -1) { // �Ʒ��������� ã�� �� ���� ���
		lower = MIN;
	}
	int single = abs(100 - stoi(N)); // + or - �θ� �̵��ϴ� ���
		

	int nearest = get_nearest(upper,lower,single);

	if (nearest == single) {
		cout << nearest;
	}
	else {
		cout << nearest ;
	}	

}

bool all_false() {	
	int n = 0;
	for (int i = 0; i <= 9; i++) {
		if (remote[i]) {
			n = 1;
		}
	}
	if (n == 0) {
		return true;
	}
	return false;
}

int main() {
	/*
		���Ʈ������ ������ ����?
		N�� �ִ밪�� 50�� -> 6�ڸ�
		������ ��� ���� 10^6

		��ư ���忩�� Ž�� = 10

		�ִ� 10^7
	*/
	input();		
	if (stoi(N) == 100) { // �̵��� �ʿ� ���� ���
		cout << 0;
	}
	else if (all_false()) { // ��� ��ư�� ���峭���			
		cout << abs(100 - stoi(N));
	}
	else { // �̿��� ���		
		solve();
	}		
	// 100���� + - �θ� �ö󰡴°� ����ó��
}