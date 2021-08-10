#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int C; // tc 개수
int N; // 문자열 개수

priority_queue<int, vector<int>, greater<int> > pq;
vector<int> result;

void input() {
	cin >> N;	
	for (int i = 0; i < N; i++) {
		int k;
		cin >> k;
		pq.push(k);
	}
}

int solve() {
	int ans = 0;
	while (pq.size() > 2) {
		int first = pq.top();
		pq.pop();
		int second = pq.top();
		pq.pop();
		pq.push(first + second);
		ans += first + second;
	}
	ans += pq.top();
	pq.pop();
	ans += pq.top();
	pq.pop();
	return ans;
}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {
		input();		
		int ans = solve();
		result.push_back(ans);
	}
	print();
}