#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int n, k;
int dp[10001];
vector<int> coin;


void input() {
	//ifstream in("test.txt");
	cin >> n >> k;
	coin.push_back(0);
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		coin.push_back(p);
	}
	sort(coin.begin(), coin.end());
}
void solve() {
	for (int i = 1; i <= n; i++) {
		int p = coin[i]; // 현재 동전 값
		for (int j = 1; j <= k; j++) {
			if (j < p) {
				dp[j] = dp[j]; // 이전 동전으로만 처리
			}
			else if (j == p) {
				dp[j] = dp[j] + 1;
			}
			else if (j > p) {
				dp[j] = dp[j] + dp[j - p];
			}
			//cout << dp[i][j] << endl;
		}
		/*
		for (int i = 1; i <= k; i++) {
			cout << dp[i] << " ";

		}
		cout << endl;*/
	}
}
void print() {
	cout << dp[k];

}

int main() {
	input();
	solve();
	print();
}