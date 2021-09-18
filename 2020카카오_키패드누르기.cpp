#include <iostream>
#include <array>
#include <vector>
#define pii pair<int,int>
using namespace std;

array <pii,11> position;

void get_position() {
		position[1] = make_pair(1, 1);			
		position[2] = make_pair(1, 2);
		position[3] = make_pair(1, 3);			
		position[4] = make_pair(2, 1);				
		position[5] = make_pair(2, 2);				
		position[6] = make_pair(2, 3);				
		position[7] = make_pair(3, 1);			
		position[8] = make_pair(3, 2);			
		position[9] = make_pair(3, 3);
		position[0] =  make_pair(4, 2);			
}

string get_hand(string hand, pii pos, pii cur_left, pii cur_right) {
	int l = abs(pos.first - cur_left.first) + abs(pos.second - cur_left.second);
	int r = abs(pos.first - cur_right.first) + abs(pos.second - cur_right.second);	
	if (l < r) {
		return "left";
	}
	if (r < l) {
		return "right";
	}
	if (r == l) {
		return hand;
	}
}

int main() {
	vector<int> numbers = { 7, 0, 8, 2, 8, 3, 1, 5, 7, 6, 2 };
	string hand = "left"; // input

	get_position(); // 좌표반환

	string answer = ""; // 정답 string
	pii cur_left = make_pair(4,1), cur_right = make_pair(4, 3);
	for (int cur_n : numbers) {
		if (cur_n == 1 || cur_n == 4 || cur_n == 7) { // 왼손 이동
			answer += "L";			
			cur_left = position[cur_n];			
		}
		else if (cur_n == 3 || cur_n == 6 || cur_n == 9) { // 오른손 이동
			answer += "R";
			cur_right = position[cur_n];
		}
		else if (cur_n == 2 || cur_n == 5 || cur_n == 8 || cur_n == 0) { // 가운데 번호인 경우
			string s = get_hand(hand, position[cur_n], cur_left, cur_right); // 어느 손 사용할지 고르기
			if (s == "right") {	
				answer += "R";		
				cur_right = position[cur_n];
			}
			else if (s == "left") {				
				answer += "L";				
				cur_left = position[cur_n];
			}
		}
	}
	cout << answer;
}