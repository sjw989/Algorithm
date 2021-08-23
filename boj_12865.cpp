#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int N, K;
vector<pair<int, int>> moolgun;
array<array<int, 100001>, 101> result;

void find_sol() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {			
			if (j >= moolgun[i].first) {
				result[i][j] = max(result[i - 1][j], result[i-1][j-moolgun[i].first] + moolgun[i].second);
			}
			else{
				result[i][j] = result[i - 1][j];
			}
		}
	}
	cout << result[N][K] << endl;
}
int main() {
	cin >> N >> K;
	pair<int, int> p;
	p.first = 0; p.second = 0;
	moolgun.push_back(p);
	for (int i = 0; i < N; i++) {		
		cin >> p.first >> p.second;
		moolgun.push_back(p);
	}	
	sort(moolgun.begin(), moolgun.end());	
	find_sol();
	return 0;
}
