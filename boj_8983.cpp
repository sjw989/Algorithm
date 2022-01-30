#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

int N; // 동물의 마리 수
int M; // 사대의 수, 사대 : 사냥꾼이 위치할 수 있는 곳
int L; // 사냥꾼의 사정거리
int ans; // 정답
vector<int> set_M; // 사대의 위치
vector<pii> vec_animal; // 동물들의 위치

void input() {
	//ifstream in("test.txt");
	cin >> M >> N >> L;	
	for (int i = 0; i < M; i++) {
		int k;
		cin >> k;
		set_M.push_back(k);
	} 
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		vec_animal.push_back(make_pair(x, y));
	}
}


bool can_hunt(int x, int y) {
	/*
	|a - x| + y <= L
	|a - x| <= L - y
	-(L - y) <= a - x <= L - y
	-L + y + x <= a <= L - y + x
	*/

	int max_distance = L - y + x; // 사대의 최대 좌표
	int min_distance = y - L + x; // 사대의 최소좌표
	
	auto max_it = upper_bound(set_M.begin(), set_M.end(), max_distance); // max를 초과하는 iterator
	int under_max = max_it - set_M.begin(); // max 이하의 원소의 개수

	auto min_it = lower_bound(set_M.begin(), set_M.end(), min_distance); // min 이상의 iterator
	int under_min = min_it - set_M.begin(); // min 미만의 원소의 개수


	int cnt = under_max - under_min; // min ~ max 사이에 있는 수의 개수
	
	if (cnt > 0) { // 부등식 범위에 속하는 사대가 존재할 때 true를 리턴
		return true;
	}

	return false;
}

void solve() {	
	//완전탐색은 O(NM) = 10^10 -> 안됨
	sort(set_M.begin(), set_M.end()); // 사대의 위치 정렬
	
	for (pii animal : vec_animal) {
		int x = animal.first;
		int y = animal.second;		
		if (can_hunt(x, y)) {
			ans++;
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