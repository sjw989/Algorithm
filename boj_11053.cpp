#include <iostream>
#include <fstream>
#include <vector>
#include <array>
using namespace std;

int N; // 수열의 크기
int ans; // 정답
array<int, 1001> number;
array<int, 1001> dp;

void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int k;
		cin >> k;
		number[i] = k;
	}
}

void solve(int k) {
	if (k == N) {
		dp[k] = 1;
		return;
	}
	int pivot = number[k];
	for (int i = k + 1; i <= N; i++) {
		
		if (pivot < number[i]) {
			if (dp[i] == 0) {
				solve(i);			
			}
			dp[k] = max(dp[i] + 1, dp[k]);
		}
	}
	if (dp[k] == 0) {
		dp[k] = 1;
	}

}

void print() {
	for (int i = 1; i <= N; i++) {
		//cout << dp[i] << " ";
		ans = max(ans, dp[i]);
	}
	//cout << endl;
	cout << ans;
}


int main() {
	input();
	for (int i = 1; i <= N; i++) {
		solve(i);
	}
	print();
}