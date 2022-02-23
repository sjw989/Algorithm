#include <iostream>
#include <fstream>
#include <array>
#define pii pair<int,int>
using namespace std;

int N; // 컨베이어의 길이
int K; // 내구도 0인 칸의 개수
int ans = 1; // 정답
array<pii, 201> belt; // (로봇의 유무, 내구도)

void input() {
	//ifstream in("test.txt");
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++) {
		int k;
		cin >> k;
		belt[i] = make_pair(0, k);
	}
}
void rotate() {
	array<pii, 201> new_belt;
	for (int i = 1; i <= 2 * N; i++) {
		if (i == 2 * N) {
			new_belt[1] = belt[2 * N];
		}
		else {
			new_belt[i + 1] = belt[i];
		}				
	}  	
	belt = new_belt;	
}
void solve() {	
	while (1) { // 내구도가 0인 칸이 K개가 될 떄 까지 반복		
		rotate(); // 벨트 회전
		if (belt[N].first == 1) { // 내리는 위치에 로봇이 있으면 즉시 내림
			belt[N].first = 0;
		}
		for (int i = N - 1; i >= 1; i--) { // 가장 먼저 올라간 로봇부터 전진
			if (belt[i].first == 1) { // 로봇이 있을 때
				if (belt[i + 1].first == 0 && belt[i + 1].second > 0) { // 다음칸이 비어있고 내구도가 1이상이면
					// 로봇 전진
					belt[i].first = 0;
					belt[i + 1].first = 1;
					belt[i + 1].second--; 					
				}			
			}
		}
		if (belt[N].first == 1) { // 내리는 위치에 로봇이 있으면 즉시 내림
			belt[N].first = 0;
		}

		if (belt[1].second > 0) { // 올리는 위치에 내구도가 0이 아니면
			belt[1].first = 1; // 로봇 올리고
			belt[1].second--; // 내구도 감소
		}
		int destroyed = 0;// 내구도가 0인 칸의 개수
		for (int i = 1; i <= 2*N; i++) { // 내구도가 0인 칸 카운팅			
			if (belt[i].second == 0) { 				
				destroyed++;
			}
		}		
		if (destroyed >= K) {
			return;
		}

		ans++;
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