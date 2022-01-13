#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int N, H; // N x H 동굴
int ans_break = 200001; // 파괴해야하는 최소 장애물 수
int ans_cnt = 0; // 파괴해야하는 최소 장애물 수가 같은 구간의 개수
vector<int> stalagmite; // 석순 높이
vector<int> stalactite; // 종유석 높이

void input() {
	//ifstream in("test.txt");
	cin >> N >> H;
	for (int i = 1; i <= N; i++) {
		int k;
		cin >> k;
		if (i % 2 == 0) { // 짝수번째는 종유석			
			stalactite.push_back(k);
		}
		else { // 홀수번째는 석순
			stalagmite.push_back(k);
		}		
	}	
}

void solve() {
	for (int h = 1; h <= H; h++) { // HlogN 
		int bottom = lower_bound(stalagmite.begin(),stalagmite.end(), h) - stalagmite.begin(); // 현재 높이에서 파괴하는 석순의 개수
		int top = upper_bound(stalactite.begin(), stalactite.end(), H - h) - stalactite.begin(); // 현재 높이에서 파괴하는 종유석의 개수

		int cur_bottom = N / 2 - bottom;
		int cur_top = N / 2 - top; // 종유석 처리에 필요한 연산		
		if (cur_bottom + cur_top < ans_break) { // 새로운 최소값을 발견
			ans_cnt = 1; // cnt 초기화
			ans_break = cur_bottom + cur_top; // 최소값 업데이트
		}
		else if (cur_bottom + cur_top == ans_break) {
			ans_cnt++;
		}
	}
}

void print() {	
	cout << ans_break << " " << ans_cnt;
}

int main() {
	input();
	sort(stalagmite.begin(), stalagmite.end());		
	sort(stalactite.begin(), stalactite.end());	
	solve();	
	print();
}