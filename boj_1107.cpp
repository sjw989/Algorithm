#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <array>
#define MIN -12345678
using namespace std;

string N; // 이동하려는 채널
int M; // 고장난 버튼의 개수
int ans; // 정답
bool remote[10]; // 리모컨 0 ~ 9

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	memset(remote, true, sizeof(remote));	
	if (M > 0) { // 고장난 버튼이 있는 경우
		for (int i = 0; i < M; i++) {
			int k;
			cin >> k;
			remote[k] = false; // 버튼 고장 처리
		}
	}
}

bool can_go(int cur) {
	string s = to_string(cur); // 현재 채널		
	for (int i = 0; i < s.size(); i++) {				
		if (!remote[s[i] - '0']) { // 누를 수 없는 버튼이 존재하면
			return false;
		}
	}		
	return true; // 모두 버튼으로 이동할 수 있는 경우

}

int find_up() {
	int n = stoi(N);	
	// 모든 버튼이 고장나서 이동불가능한 경우 예외처리해서 무한루프 안됨	
	while (true) { // 버튼으로 이동가능한 채널 찾을때 까지 탐색		
		if (can_go(n)) {						
			return n;
		}
		n++;
	}		
}

int find_down() {
	int n = stoi(N) - 1;
	for (int i = n; i >= 0; i--) {
		if (can_go(i)) {
			return i;
		}
	}
	return -1;
}

int get_nearest(int upper, int lower, int single) {
	int n = stoi(N);
	int up = abs(upper - n) + to_string(upper).size();
	int down = abs(lower - n) + to_string(lower).size();		
	return min(single, min(up, down));
}

void solve() {		
	// 0만 이동가능한경우는 무조건 lower case
	// 0이 아닌 다른 버튼으로 이동가능한경우는 upper case 존재
	bool only_zero = true;
	for (int i = 1; i < 10; i++) {
		if (remote[i]) {
			only_zero = false;
			break;
		}
	}

	// 비교해야할 것
	// (N ~ 무한대) vs (0 ~ N -1) vs  + or - 만 누르는 경우

	int upper = 0;
	if (!only_zero) {
		upper = find_up(); // N ~ 무한대 -> N이상의 수 중 가장 가까운 수
	}	
	int lower = find_down(); // 0 ~ N-1 -> N 이하의 수 중 가장 가까운 수
	if (lower == -1) { // 아래범위에서 찾을 수 없는 경우
		lower = MIN;
	}
	int single = abs(100 - stoi(N)); // + or - 로만 이동하는 경우
		

	int nearest = get_nearest(upper,lower,single);

	if (nearest == single) {
		cout << nearest;
	}
	else {
		cout << nearest ;
	}	

}

bool all_false() {	
	int n = 0;
	for (int i = 0; i <= 9; i++) {
		if (remote[i]) {
			n = 1;
		}
	}
	if (n == 0) {
		return true;
	}
	return false;
}

int main() {
	/*
		브루트포스가 가능한 이유?
		N의 최대값은 50만 -> 6자리
		가능한 모든 수는 10^6

		버튼 고장여부 탐색 = 10

		최대 10^7
	*/
	input();		
	if (stoi(N) == 100) { // 이동할 필요 없는 경우
		cout << 0;
	}
	else if (all_false()) { // 모든 버튼이 고장난경우			
		cout << abs(100 - stoi(N));
	}
	else { // 이외의 경우		
		solve();
	}		
	// 100에서 + - 로만 올라가는거 예외처리
}