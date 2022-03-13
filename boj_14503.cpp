#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#define MAX 50+1
#define mp(a,b) make_pair(a,b)
#define pii pair<int,int>
using namespace std;


int N, M; //  N x M
int ans; // 정답
int dir; // 로봇청소기의 방향 : 상우하좌 0,1,2,3
pii pos; // 로봇청소기의 위치
array<pii, 4> delta = { mp(-1,0), mp(0,1), mp(1,0), mp(0,-1) }; // 상 우 하 좌
array<array<int, MAX>, MAX> board; // 행,열의 마지막 칸은 벽임 (1 , N , 1 , M )

void input() {
	//ifstream in("test.txt");
	int r, c;
	cin >> N >> M;	
	cin >> r >> c;		
	r++, c++;
	pos = mp(r, c);
	cin >> dir;	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
		}
	}	
}
void solve() {
	while (true) {	
		
		if (board[pos.first][pos.second] == 0) { // 현재위치 청소하기
			ans++;
			board[pos.first][pos.second] = -1; 			
		}				
		bool can_clean = false; // 4방향 중 청소가능한 칸이 있는지		
		// 바라보는 방향을 기준으로 반시계로 회전하며 청소가능한 칸 찾기
		for (int i = 0; i < 4; i++) { // 4번 반시계로 회전시킴			
			dir--; // 왼쪽으로 회전
			if (dir < 0) { dir = 3; } // 예외처리
			int nr = pos.first + delta[dir].first;
			int nc = pos.second + delta[dir].second; // 다음위치		

			if (nr > 1 && nr < N && nc > 1 && nc < M && board[nr][nc] == 0) { // 왼쪽으로 회전한 칸이 청소 가능하면															
				pos = mp(nr, nc); // 그 방향으로 전진
				can_clean = true; // 청소가능한 칸이 존재
				break;
			}
			
		}				
		if(!can_clean) { // 4방향중 청소가능한 칸이 존재하지 않으면					
			// 바라보는 방향을 유지한채 후진
			int back_dir = (dir + 2) % 4; // 후진 방향			
			int nr = pos.first + delta[back_dir].first;
			int nc = pos.second + delta[back_dir].second; // 1칸 후진한 위치
			if (nr > 1 && nr < N && nc > 1 && nc < M && board[nr][nc] != 1) { // 후진 가능한 경우
				pos = mp(nr, nc);
			}
			else { // 후진 못하는 경우
				return;
			}			
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

/*
1. 현재 바라보는 방향을 기준으로 왼쪽 방향부터 탐색
2. 왼쪽 방향에 청소하지 않은 공간이 존재한다면 그 방향으로 회전하고 한칸 전진
    -> 왼쪽으로 한 칸 땡기고 방향을 왼쪽으로 전환,
		delta 배열에서 인덱스 -1씩 줄여감
3. 왼쪽방향에 청소할 공간이 없다면 왼쪽으로 전환하고 2로 돌아감
   -> 반시계로 돌아가며 청소공간 탐색
4. 4방향 모두 청소가되어있거나 벽인 경우 -> 바라보는 방향을 유치한 채 한 칸 후진하고 2번으로	
   -> 후진이 안되는 경우 종료
*/