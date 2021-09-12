#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <array>
#define pii pair<int,int>
using namespace std;

int N; // ��ǰ ��
int K; // ������ �ִ� ����
int ans; // ����
vector<pii> thing; // ������ ���� array
array<array<int, 100001>,101> dp; // dp array
/*
    dp array
--> i��° ���ǿ� ���� �� ���԰� k�� ��찡 ������ ����� �� �ִ��� ���

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

void dfs(int start,int cur_w, int cur_v) { // ���� ���� index, ���� ����, ���� ��ġ
	pii t = thing[start]; // ���� ����	

	if (start == N) { // ������ ����
		if (cur_w + t.first <= K) { // ������ ������ ���� �� ������
			dp[start][cur_w] = cur_v + t.second;
		}
		else { // ���� �� ���� ��
			dp[start][cur_w] = cur_v;
		}
		return;
	}

	if (cur_w + t.first <= K) { // ���濡 ���� ������ ���� �� ������
		if (dp[start + 1][cur_w + t.first] == 0) { // �� ������ ��� ����� dp���� ������
			dfs(start + 1, cur_w + t.first, cur_v + t.second); // dfs
		}
		else {
			dp[start + 1][cur_w + t.first] = max(dp[start + 1][cur_w + t.first], cur_v + t.second);
		}
	}
	if (dp[start + 1][cur_w] == 0) {
		dfs(start + 1, cur_w, cur_v); // ���� ������ �����ʴ� ���
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