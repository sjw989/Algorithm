#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int N; // 나무의 수
int M; // 상근이가 가져가려고 하는 나무의 길이
int ans; // 절단기의 최대 높이
vector<int> tree;

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		tree.push_back(t);
	}
}

long long get_tree(int h) {
	long long l = 0;
	for (long long t : tree) {
		long long gap = t - h;
		if (gap >= 0) {
			l += gap;
		}
	}
	return l;
}

void solve() {
	sort(tree.begin(), tree.end()); // 나무의 최고높이를 얻기 위해
	int lower = 0;
	int upper = tree[N - 1];
	while (lower < upper) {
		int mid = (lower + upper) / 2;
		if (get_tree(mid) >= M) {
			ans = max(ans, mid);
			lower = mid + 1;
		}
		else {
			upper = mid;
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
