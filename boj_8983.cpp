#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

int N; // ������ ���� ��
int M; // ����� ��, ��� : ��ɲ��� ��ġ�� �� �ִ� ��
int L; // ��ɲ��� �����Ÿ�
int ans; // ����
vector<int> set_M; // ����� ��ġ
vector<pii> vec_animal; // �������� ��ġ

void input() {
	//ifstream in("test.txt");
	cin >> M >> N >> L;	
	for (int i = 0; i < M; i++) {
		int k;
		cin >> k;
		set_M.push_back(k);
	} 
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		vec_animal.push_back(make_pair(x, y));
	}
}


bool can_hunt(int x, int y) {
	/*
	|a - x| + y <= L
	|a - x| <= L - y
	-(L - y) <= a - x <= L - y
	-L + y + x <= a <= L - y + x
	*/

	int max_distance = L - y + x; // ����� �ִ� ��ǥ
	int min_distance = y - L + x; // ����� �ּ���ǥ
	
	auto max_it = upper_bound(set_M.begin(), set_M.end(), max_distance); // max�� �ʰ��ϴ� iterator
	int under_max = max_it - set_M.begin(); // max ������ ������ ����

	auto min_it = lower_bound(set_M.begin(), set_M.end(), min_distance); // min �̻��� iterator
	int under_min = min_it - set_M.begin(); // min �̸��� ������ ����


	int cnt = under_max - under_min; // min ~ max ���̿� �ִ� ���� ����
	
	if (cnt > 0) { // �ε�� ������ ���ϴ� ��밡 ������ �� true�� ����
		return true;
	}

	return false;
}

void solve() {	
	//����Ž���� O(NM) = 10^10 -> �ȵ�
	sort(set_M.begin(), set_M.end()); // ����� ��ġ ����
	
	for (pii animal : vec_animal) {
		int x = animal.first;
		int y = animal.second;		
		if (can_hunt(x, y)) {
			ans++;
		}
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