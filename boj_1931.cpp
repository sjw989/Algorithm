#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define pii pair<int,int>
using namespace std;

int N; // 회의 개수
int ans;
vector<pii> meeting;

void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 0; i < N; i++) {
		int start, end;
		cin >> start >> end;
		meeting.push_back(make_pair(start, end));
	}
}

bool compare(pii a, pii b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

void solve() {
	int end = 0;
	for (int i = 0; i < N; i++) {
		pii cur_meet = meeting[i];
		if (cur_meet.first >= end) {
			end = cur_meet.second;
			ans++;
		}
	}
}

int main() {
	input();
	sort(meeting.begin(), meeting.end(), compare);
	solve();
	cout << ans;
}