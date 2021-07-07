#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#define INF 987654321
using namespace std;
bool is_result = true;
int C; // tc 개수
int res;
int push = INF;
array<int, 16> input_clock; // 시계 입력
array<int, 16> cnt; // 시계들이 몇 번 돌아갔는지
vector<int> result; // 정답 저장
vector<vector<int>> clock_switch = {
	{0,1,2},{3,7,9,11}, {4,10,14,15}, {0,4,5,6,7}, {6,7,8,10,12},
	{0,2,14,15}, {3,14,15}, {4,5,7,14,15}, {1,2,3,4,5}, {3,4,5,9,13}
};

void input() {	
	for (int i = 0; i < 16; i++) {
		cin >> input_clock[i];
	}
}
/*
for (int i = 0; i < 16; i++) {
	cout << cnt[i] << " ";
}
cout << endl;*/
bool check_twelve() {	

	for (int i = 0; i < 16; i++) {
		switch (input_clock[i]) {
			case 3:
				if (cnt[i] % 4 != 3) {
					return false;
				}
				break;
			case 6:
				if (cnt[i] % 4 != 2) {
					return false;
				}
				break;
			case 9:
				if (cnt[i] % 4 != 1) {
					return false;
				}
				break;
			case 12:
				if (cnt[i] % 4 != 0) {
					return false;
				}
				break;
		}
	}	
	return true;
}

void solve(int switch_num) {					
	for (int i = 0; i < 4; i++) { // 각 스위치를 0번 ~ 3번까지 누를 수 있음				
		if (i != 0) {
			push++;
			for (auto num : clock_switch[switch_num]) {				
					cnt[num]++;				
			} // 각 시계의 cnt 회수 증가 
		}						
	
		if(!check_twelve()) { // 12시인지 체크
			if (switch_num + 1 < 10){
				solve(switch_num+1);				
			} // 다음 스위치가 있으면 재귀호출
		}
		else {
			res = min(res, push);							
		}
	}	
	push -= 3;
	for (auto num : clock_switch[switch_num]) {
		cnt[num] -= 3;
	}

}
void print() {
	for (auto ans : result) {
		if (ans == INF) {
			cout << -1 << "\n";
		}
		else {
			cout << ans << "\n";
		}
	}

}
int main() {
	cin >> C;
	for (int i = 0; i < C; i++) {
		input();		
		int swtich_num = 0;
		res = INF;
		push = 0;
		solve(swtich_num);
		result.push_back(res);
	}
	print();
	
}