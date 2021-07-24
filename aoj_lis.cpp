#include <iostream>
#include <vector>
#include <array>
using namespace std;

int C; // tc 개수
int N; // tc 원소 개수
int maximum; // 최대값
vector<int> num;
vector<int> result;
array<int, 500> dp;

void input() {	
	cin >> N;
	for (int j = 0; j < N; j++) {
		int n;
		cin >> n;
		num.push_back(n);
	}
}

void init() {
	for (int i = 0; i < 500; i++) {
		dp[i] = 0;
	}
	maximum = 0;
	num.clear();
}

void solve(int idx) {
	if (idx == N - 1) {
		dp[idx] = 1;
		return;
	}
	for (int i = idx + 1; i < N; i++) {
		if (num[idx] < num[i]) {
			if (dp[i] == 0) {
				solve(i);				
			}
			dp[idx] = max(dp[idx],dp[i] + 1);
			maximum = max(maximum, dp[idx]);			
		}
	}
	if (dp[idx] == 0) {
		dp[idx] = 1;
	}	

}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {
		init();
		input();
		for (int j = 0; j < N; j++) {
			solve(j);			
		}	
		result.push_back(maximum);		
	}
	print();	
	
}
