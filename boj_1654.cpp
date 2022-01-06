#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int K, N; // 이미 가지고있는 랜선 K개, 필요한 랜선 N개
int ans; // 가능한 랜선의 최대길이
vector<long long> lan; // 가지고있는 랜선의 길이

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
	sort(lan.begin(), lan.end()); // 최소길이, 최대길이를 얻기위해 정렬

	int lower = 1; // 가진 랜선의 최소길이
	long long upper = lan[K-1]; // 가진 랜선의 최대길이		

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