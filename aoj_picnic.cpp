#include <iostream>
#include <fstream>
#include <array>
#include <vector>
using namespace std;

int C; // tc 개수
int n, m; // 학생 수, 친구 쌍 수
int result; // 결과
vector<int> res;
array<vector<int>, 10> friends; // 친구 관계
array<bool, 10> can_pair; // 짝이 있는지 없는지

void input() {
	cin >> n >> m;	
	for (int i = 0; i < m; i++) {
		int s1 = 0, s2 = 0;
		cin >> s1 >> s2;
		friends[s1].push_back(s2);
		friends[s2].push_back(s1);
	}
}

bool all_pair() {
	for (int i = 0; i < n; i++) {
		if (can_pair[i]) { // 하나라도 짝 지을 수 있는게 있으면
			return false;
		}
	}
	return true; // 모두 짝 지을 수 없으면
}

void solve(int cur) {			
	can_pair[cur] = false; // cur 짝짓기 처리
	
	vector<int> can_friend = friends[cur];
	for (auto num : can_friend) {
		
		if(can_pair[num]) { // cur과 친구인 num들 중 아직 짝이 없는 경우
			can_pair[num] = false; // cur과 짝을 지어줌

			if (all_pair()) { // 모두 짝지어졌으면			
				result++;
				can_pair[num] = true; // cur과 짝 해제
				continue;
			}			
			for (int next = cur + 1; next < n; next++) {			
				if (can_pair[next]) {					
					solve(next);
					break;
				}
			}			
			can_pair[num] = true; // cur과 짝 해제
		}	
	}
	can_pair[cur] = true;
}

void print() {
	for (auto ans : res) {
		cout << ans << endl;
	}
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {				
		input();
		for (int j = 0; j < n; j++) {
			can_pair[j] = true;
		}
		
		solve(0);		
		for (int j = 0; j < n; j++) {
			friends[j].clear();
			can_pair[j] = true;
		}
		res.push_back(result);
		result = 0;		
	}
	print();	
}