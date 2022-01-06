#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int K, N; // �̹� �������ִ� ���� K��, �ʿ��� ���� N��
int ans; // ������ ������ �ִ����
vector<long long> lan; // �������ִ� ������ ����

void input() {
	ifstream in("test.txt");
	in >>K >> N;
	for (long long i = 0; i < K; i++) {
		long long l;
		in >>l;
		lan.push_back(l);
	}
}

int divide(int mid) {
	int cnt = 0;
	for (int l : lan) {
		cnt += l / mid;
	}
	return cnt;
}

void solve() {
	sort(lan.begin(), lan.end()); // �ּұ���, �ִ���̸� ������� ����

	int lower = 1; // ���� ������ �ּұ���
	long long upper = lan[K-1]; // ���� ������ �ִ����		

	while (lower < upper) { 
		int mid = (lower + upper) / 2;
		int cnt = divide(mid);			
		cout << lower << " " << upper << endl;
		//cout << mid << " " << cnt << endl;
		if (cnt < N) {
			upper = mid;
		}
		else {
			ans = mid;
			lower = mid + 1;
		}
	}			
	if (divide(lower) >= N) {
		ans = max(ans, lower);
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