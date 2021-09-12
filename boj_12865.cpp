#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <array>
#define pii pair<int,int>
using namespace std;

int N; // 물품 수
int K; // 가방의 최대 무게
int ans; // 정답
vector<pii> thing; // 물건의 정보 array
array<array<int, 100001>,101> dp; // dp array
/*
    dp array
--> i번째 물건에 왔을 때 무게가 k인 경우가 이전에 연산된 적 있는지 기록

*/

void input() {
	ifstream in("test.txt");
	in >>N >> K;
	thing.push_back(make_pair(0, 0));
	for (int i = 1; i <= N; i++) {
		int w, v;
		in >>w >> v;
		thing.push_back(make_pair(w, v));
	}		
}

void dfs(int start,int cur_w, int cur_v) { // 시작 물건 index, 현재 무게, 현재 가치
	pii t = thing[start]; // 현재 물건	

	if (start == N) { // 마지막 물건
		if (cur_w + t.first <= K) { // 마지막 물건을 담을 수 있으면
			dp[start][cur_w] = cur_v + t.second;
		}
		else { // 담을 수 없을 때
			dp[start][cur_w] = cur_v;
		}
		return;
	}

	if (cur_w + t.first <= K) { // 가방에 현재 물건을 담을 수 있으면
		if (dp[start + 1][cur_w + t.first] == 0) { // 이 물건을 담는 경우의 dp값이 없으면
			dfs(start + 1, cur_w + t.first, cur_v + t.second); // dfs
		}
		else {
			dp[start + 1][cur_w + t.first] = max(dp[start + 1][cur_w + t.first], cur_v + t.second);
		}
	}
	if (dp[start + 1][cur_w] == 0) {
		dfs(start + 1, cur_w, cur_v); // 현재 물건을 담지않는 경우
	}
	else {
		dp[start + 1][cur_w] = max(dp[start + 1][cur_w], cur_v);
	}
	dp[start][cur_w] = max(dp[start + 1][cur_w + t.first], dp[start + 1][cur_w]);
	ans = max(ans, dp[start][cur_w]);
	
}


int main() {
	input();
	//sort(thing.begin(), thing.end());
	dfs(1, 0, 0);		
	
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j <= 5; j++) {
			cout << setw(5) << dp[i][j] << " ";
		}
		cout << endl;
	}
	cout << ans;	
	
}