#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>
#define pii pair<int,int>
using namespace std;

int C; // tc 개수
int N;
vector<pii> inp;
vector<int> result;


void input(){	
	cin >> N;
	inp.clear(); // 초기화
	for (int i = 0; i < N; i++) {
		int k;
		cin >> k;
		inp.push_back(make_pair(k, 0));
	}
	for (int i = 0; i < N; i++) {
		int k;
		cin >> k;
		inp[i].second = k;
	}

}

int solve() {
	int lunch_time = 0;
	int over_time = inp[0].second;
	for (int i = 0; i < N; i++) {
		lunch_time += inp[i].first;
		if (i != N - 1) {
			if (over_time < inp[i + 1].first + inp[i + 1].second) {
				over_time = inp[i + 1].second;
			}
			else {
				over_time -= inp[i + 1].first ;
			}
		}
	}	
	return lunch_time + over_time;
}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

bool compare(pii a, pii b) {
	return a.second > b.second;
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {
		input();
		sort(inp.begin(), inp.end(), compare); // 식사시간 내림차순 정렬		
		int ans = solve();		
		result.push_back(ans);
	}
	print();
	
	

}