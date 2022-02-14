#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

int N; // 전깃줄의 개수
vector<int> line;
vector<int> dp;

void input() {
	//ifstream in("test.txt");	
	cin >> N;
	vector<pii> edge;
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		edge.push_back(make_pair(x, y));
	}
	sort(edge.begin(), edge.end());
	for (int i = 0; i < N; i++) {
		line.push_back(edge[i].second);
		dp.push_back(0);
	}
}
void solve(int idx) {
	if (idx == line.size() - 1) {
		dp[idx] = 1;
		return;
	}
	int pivot = line[idx];
	for (int i = idx + 1; i < N; i++) {
		if (pivot < line[i]) { // 증가할 때
			if (dp[i] == 0) {				
				solve(i);
			}			
			dp[idx] = max(dp[idx], dp[i] + 1);
		}
	}
	if (dp[idx] == 0) {
		dp[idx] = 1;
	}
}
void print() {
	int a = 0;
	for (int i = 0; i < N; i++) {
		a = max(a, dp[i]);
	}
	cout << N - a;
}

int main() {
	input();
	for (int i = 0; i < N; i++) {
		solve(i);
	}	
	print();
}