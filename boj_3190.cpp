#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#define pic pair<int,char>
#define pii pair<int,int>
using namespace std;


typedef struct Snake {
	int row;
	int col;
	int direction;
};

int N, K, L; // 배열 크기 N x N, 사과 개수 K개, 방향전환 횟수 L
int ans; // 시간
Snake head; // 머리
Snake tail; // 꼬리
array<pii, 4> drc = { make_pair(0,1), make_pair(0,-1),
					  make_pair(-1,0), make_pair(1,0) 
					}; // R, L, U, D					

array<array <int, 101>, 101> board; // 게임 보드
array<array <int, 101>, 101> apple; // 사과 정보
queue<pic> change; // 방향전환정보
queue<Snake> snake_position; // 뱀이 위치한 board 좌표

void input() {
	//ifstream in("test.txt");
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int r, c;
		cin >> r >> c;
		apple[r][c] = 1; // 사과 표시
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int x;
		char c;
		cin >> x >> c;		
		change.push(make_pair(x, c));
	}
}

bool can_go() { 
	// head가 진행가능한지 부터 check
	pii cur_drc = drc[head.direction]; // 진행 방향의 drow, dcol 값
	if (head.row + cur_drc.first < 1 || head.row + cur_drc.first > N // head row체크
		|| head.col + cur_drc.second < 1 || head.col + cur_drc.second > N // head col체크
		|| board[head.row + cur_drc.first][head.col + cur_drc.second] == 1) {// head가 가려고 하는 곳에 몸통이 있으면		
		return false; // 게임 종료
	}
	return true;
}

bool apple_check() {
	pii cur_drc = drc[head.direction];
	if (apple[head.row + cur_drc.first][head.col + cur_drc.second] == 1) {
		apple[head.row + cur_drc.first][head.col + cur_drc.second] = 0;// 사과 먹고
		return true; // 다음 칸이 사과인지 체크
	}
	return false;
}

void move_snake_position() {		
	// head가 진행 가능한 경우
	queue<Snake> new_snake_position;
	Snake before_snake; // 꺾이는거를 대비해서 이전 상태 저장	
	// 초기화
	before_snake.row = 0;
	before_snake.col = 0;
	before_snake.direction = 0;	

	while (!snake_position.empty()) { // 뱀의 위치 하나하나를 옮겨줌				
		Snake cur_snake = snake_position.front(); // 현재 부위?
		snake_position.pop();

		if (snake_position.size() == 0) {
			tail = cur_snake; // 꼬리 저장
		}
		Snake new_snake; // 옮겨진 위치
		// 초기화
		new_snake.row = 0;
		new_snake.col = 0;
		new_snake.direction = 0;		

		if (cur_snake.row == head.row && cur_snake.col == head.col) {			
			// head인 경우 그대로 진행
			new_snake.row = head.row + drc[head.direction].first;
			new_snake.col = head.col + drc[head.direction].second;
			new_snake.direction = head.direction;
			head = new_snake; // head 업데이트			
		}
		else { // 그 외 몸통의 경우
			new_snake = before_snake;
		}		
		before_snake = cur_snake; // before_snake 넣어줌
		new_snake_position.push(new_snake);
		board[cur_snake.row][cur_snake.col] = 0;
		board[new_snake.row][new_snake.col] = 1;
	}	
	snake_position = new_snake_position; // snake 위치 업데이트
}

void change_head_direction(pic direct_change) {
	// drc -> right, left, up, down 
	//          0      1   2     3
		
	switch (head.direction) {
		case 0: // 현재 head가 오른쪽			
			if (direct_change.second == 'D') { // 오른쪽으로 90도
				head.direction = 3; // down 으로 바꿔줌				
			}
			else {
				head.direction = 2; // up으로 바꿔줌
			}
			break;
		case 1: // 현재 head가 왼쪽
			if (direct_change.second == 'D') { // 오른쪽으로 90도
				head.direction = 2; // up 으로 바꿔줌
			}
			else {
				head.direction = 3; // down으로 바꿔줌
			}
			break;
		case 2: // 현재 head가 위쪽
			if (direct_change.second == 'D') { // 오른쪽으로 90도
				head.direction = 0; // right 으로 바꿔줌
			}
			else {
				head.direction = 1; // left로 바꿔줌
			}
			break;
		case 3: // 현재 head가 아래쪽
			if (direct_change.second == 'D') { // 오른쪽으로 90도
				head.direction = 1; // left로 바꿔줌
			}
			else {
				head.direction = 0; // right으로 바꿔줌
			}
			break;
	}
}

void solve() {		
	head.row = 1, head.col = 1, head.direction = 0; // 초기 head 정보
	board[1][1] = 1; // 초기 뱀의 위치
	snake_position.push(head); // 초기 뱀 좌표
	pic direct_change = change.front(); // 초기 방향전환 정보
	change.pop();

	while (1) { // 언제 게임이 종료될지 모르니 무한루프
		if (can_go()) { // 한 칸 더 갈 수 있으면 --> head만 체크하면됨
			ans++;
			if (apple_check()) { // 다음 칸에 사과가 있으면				
				move_snake_position(); // 뱀 옮기고		
				snake_position.push(tail); // 꼬리 추가
				board[tail.row][tail.col] = 1; // 꼬리 board에 표시
			}			
			else { // 사과 없으면

				move_snake_position(); // 뱀 옮기기만
			}
			if (ans == direct_change.first) { // head 방향 바꿔야 되는 시간이면				
				change_head_direction(direct_change);
				if (change.size() != 0) {
					direct_change = change.front();
					change.pop();
				}				
			}
		}
		else { // head 전진이 불가능하면 게임종료
			break;
		}
	}
}

void print() {
	cout << ans+1;
}

int main() {
	input();
	solve();
	print();
}
