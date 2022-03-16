#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)

using namespace std;

int N, M; // 격자 크기, 쿼리 개수

array<array<int, 50>, 50> board;
vector<pii> query;
array<int, 5> result = { 0,0,0,0,0 };
array<pii, 5> delta = { mp(0,0), mp(-1,0), mp(1,0), mp(0,-1), mp(0,+1) }; // 상 하 좌 우
array<pii, 5> delta2 = { mp(1,0), mp(0,+1), mp(-1,0),  mp(0,-1), }; // 하 우 상 좌

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int d, s;		
		cin >> d >> s;
		query.push_back(mp(d,s));		
	}
}
void print_b() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void move() {
	pii cur = mp(N / 2 + 1, N / 2); // 1번 위치부터 시작		
	int len = 1;
	vector<int> numbers;
	for (int i = 0; i < N / 2; i++) { // N / 2 번 			
		for (int j = 0; j < 4; j++) { // 하우상좌 반복
			for (int k = 0; k < len; k++) { // 길이 len 만큼 반복					
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				if (board[cur.first][cur.second] != 0) { // 현재 칸이 빈칸이 아니면
					numbers.push_back(board[cur.first][cur.second]);
				}
				cur = mp(nr, nc); // 다음 칸으로 이동
			}
			if (j == 0 || j == 2) { // 다음이 하 or 좌 이면 길이 +1
				len++;
			}
		}
	}
	cur = mp(N / 2 + 1, N / 2); // 1번 위치부터 시작		
	len = 1;
	int idx = 0;
	numbers.resize(N * N, 0);
	for (int i = 0; i < N / 2; i++) { // N / 2 번 			
		for (int j = 0; j < 4; j++) { // 하우상좌 반복
			for (int k = 0; k < len; k++) { // 길이 len 만큼 반복					
				board[cur.first][cur.second] = numbers[idx];
				idx++;
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				cur = mp(nr, nc); // 다음 칸으로 이동
			}
			if (j == 0 || j == 2) { // 다음이 하 or 좌 이면 길이 +1
				len++;
			}
		}
	}
}
void transform() {
	pii cur = mp(N / 2 + 1, N / 2); // 1번 위치부터 시작		
	int len = 1;
	int n = board[N / 2 + 1][N / 2];
	vector<int> info;
	int cnt = 0;
	for (int i = 0; i < N / 2; i++) { // N / 2 번 			
		for (int j = 0; j < 4; j++) { // 하우상좌 반복
			for (int k = 0; k < len; k++) { // 길이 len 만큼 반복					
				if (board[cur.first][cur.second] == n) { // 번호가 같은 애들은					
					cnt++;
				}
				else { // 번호가 이전 번호와 다르면					
					if (n > 0) {						
						info.push_back(cnt);
						info.push_back(n);
					}					
					cnt = 1;
					n = board[cur.first][cur.second];
				}
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				cur = mp(nr, nc); // 다음 칸으로 이동
			}
			if (j == 0 || j == 2) { // 다음이 하 or 좌 이면 길이 +1
				len++;
			}
		}		
	}	
	if (n > 0) {// 마지막 구슬 안들어갔기때문에 따로 넣어줌
		info.push_back(cnt);
		info.push_back(n);
	}

	cur = mp(N / 2 + 1, N / 2); // 1번 위치부터 시작		
	len = 1;
	int idx = 0;
	for (int i = 0; i < N / 2; i++) { // N / 2 번 			
		for (int j = 0; j < 4; j++) { // 하우상좌 반복
			for (int k = 0; k < len; k++) { // 길이 len 만큼 반복									
				if (idx < info.size()) {
					board[cur.first][cur.second] = info[idx];
				}				
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				cur = mp(nr, nc); // 다음 칸으로 이동
				idx++;
			}
			if (j == 0 || j == 2) { // 다음이 하 or 좌 이면 길이 +1
				len++;
			}
		}
	}
}
void explosion() {				
	int n = board[N / 2 + 1][N / 2];		
	while (true) {
		vector<pii> pos; // 연속된 구슬들의 좌표
		bool is_explosion = false; // 이번 반복에서 폭발이 일어났는지
		pii cur = mp(N / 2 + 1, N / 2); // 1번 위치부터 시작				
		int len = 1;		
		for (int i = 0; i < N / 2; i++) { // N / 2 번 			
			for (int j = 0; j < 4; j++) { // 하우상좌 반복
				for (int k = 0; k < len; k++) { // 길이 len 만큼 반복					
					if (board[cur.first][cur.second] == n) { // 번호가 같은 애들은					
						pos.push_back(cur); // 모으기						
					}
					else { // 번호가 이전 번호와 다르면						
						if (pos.size() >= 4) { // 4개 이상 모여있는지 확인							
							is_explosion = true;
							for (pii p : pos) {																
								result[board[p.first][p.second]]++;								
								board[p.first][p.second] = 0; // 구슬 지우기																										
							}
						}
						pos.clear();
						pos.push_back(cur); // 모으기
						n = board[cur.first][cur.second];						
					}
					int nr = cur.first + delta2[j].first;
					int nc = cur.second + delta2[j].second;
					cur = mp(nr, nc); // 다음 칸으로 이동
				}
				if (j == 0 || j == 2) { // 다음이 하 or 좌 이면 길이 +1
					len++;
				}
			}
		}
		move(); // 구슬 이동				
		if (!is_explosion) {
			break;
		}
	}		
}


void solve() {
	for (pii q : query) { // M개의 블리자드 발동		
		int d = q.first; // 방향
		int s = q.second; // 속도		
		for (int i = 1; i <= s; i++) {					
			int nr = (N / 2) + 1 + (i * delta[d].first);
			int nc = (N / 2) + 1 + (i * delta[d].second);			
			board[nr][nc] = 0; // 구슬 파괴						
		}
		move(); // 구슬이동				
		explosion(); // 구슬 폭발								
		transform(); // 구슬 변환		
	}

}
void print() {
	cout << result[1] + 2*result[2] + 3*result[3];
}

int main() {
	input();
	solve();
	print();
}