#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#define NOCALC 987654321
using namespace std;


int C; // tc 개수
array<array<int, 50>, 50> dp;
vector<int> number; // 게임판
vector<int> result; // 정답 모음

void input() {
	int n;
	cin >> n;
	number.clear(); // 게임판 초기화
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++){
			dp[i][j] = NOCALC;
		}
	}
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		number.push_back(k);
	}
}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

int solve(int start, int end) {
	if (start == end) {
		return number[start];
	} // 길이 1인 경우 바로 retrun
	
	int case1=0, case2=0, case3=0 ,case4=0;
	if (dp[start][end] != NOCALC) {
		return dp[start][end];
	}

	case1 = number[start] - solve(start + 1, end);
	case2 = number[end] - solve(start, end - 1);
	if (end - start + 1 > 2) {
		case3 = -solve(start + 2, end);
		case4 = -solve(start, end - 2);
	}

	return dp[start][end] = max(case1, max(case2, max(case3, case4)));
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {
		input();
		int ans =  solve(0, number.size() - 1);
		result.push_back(ans);
	}
	print();
}