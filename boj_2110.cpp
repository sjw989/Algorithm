#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int N, C; // 집의 수, 설치하려는 공유기의 수
int ans;
vector<int> home;

void input() {
	//ifstream in("test.txt");
	cin >> N >> C;
	for (int i = 0; i < N; i++) {
		int k;
		cin >> k;
		home.push_back(k);
	}
}

void binary_search() {
	int start = 1, end = home[N - 1] - home[0];
	// N >= 2이므로, 공유기 사이의 최소간격 : 1, 최대간격 : 마지막 - 처음

	int cnt = 0;
	while (start <= end) {
		int before = home[0]; // 첫번째 집에는 무조건 설치해야함
		cnt = 1;
		int mid = (start + end) / 2; 
		/* start와 end의 중간값 기준으로 모든 공유기가 설치가능한지		   
		    판단해보면 간격 조절이 가능*/		
		for (int i = 1; i < N; i++) {
			if (home[i] - before >= mid) { // mid 이상의 간격으로 놓을 수 있는 공유기				
				cnt++;
				before = home[i];
			}
		}		
		if (cnt >= C) { // 모든 공유기를 놓을 수 있다면			
			ans = max(ans, mid);
			start = mid + 1; // 거리를 더 넓혀서 찾아봄
		}
		else {
			end = mid - 1; // 거리를 좁힘
		}
	}
}

void print() {
	cout << ans;
}

int main() {
	input();
	sort(home.begin(), home.end());
	binary_search();
	print();
}