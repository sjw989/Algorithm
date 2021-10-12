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

int N, K, L; // �迭 ũ�� N x N, ��� ���� K��, ������ȯ Ƚ�� L
int ans; // �ð�
Snake head; // �Ӹ�
Snake tail; // ����
array<pii, 4> drc = { make_pair(0,1), make_pair(0,-1),
					  make_pair(-1,0), make_pair(1,0) 
					}; // R, L, U, D					

array<array <int, 101>, 101> board; // ���� ����
array<array <int, 101>, 101> apple; // ��� ����
queue<pic> change; // ������ȯ����
queue<Snake> snake_position; // ���� ��ġ�� board ��ǥ

void input() {
	//ifstream in("test.txt");
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int r, c;
		cin >> r >> c;
		apple[r][c] = 1; // ��� ǥ��
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
	// head�� ���డ������ ���� check
	pii cur_drc = drc[head.direction]; // ���� ������ drow, dcol ��
	if (head.row + cur_drc.first < 1 || head.row + cur_drc.first > N // head rowüũ
		|| head.col + cur_drc.second < 1 || head.col + cur_drc.second > N // head colüũ
		|| board[head.row + cur_drc.first][head.col + cur_drc.second] == 1) {// head�� ������ �ϴ� ���� ������ ������		
		return false; // ���� ����
	}
	return true;
}

bool apple_check() {
	pii cur_drc = drc[head.direction];
	if (apple[head.row + cur_drc.first][head.col + cur_drc.second] == 1) {
		apple[head.row + cur_drc.first][head.col + cur_drc.second] = 0;// ��� �԰�
		return true; // ���� ĭ�� ������� üũ
	}
	return false;
}

void move_snake_position() {		
	// head�� ���� ������ ���
	queue<Snake> new_snake_position;
	Snake before_snake; // ���̴°Ÿ� ����ؼ� ���� ���� ����	
	// �ʱ�ȭ
	before_snake.row = 0;
	before_snake.col = 0;
	before_snake.direction = 0;	

	while (!snake_position.empty()) { // ���� ��ġ �ϳ��ϳ��� �Ű���				
		Snake cur_snake = snake_position.front(); // ���� ����?
		snake_position.pop();

		if (snake_position.size() == 0) {
			tail = cur_snake; // ���� ����
		}
		Snake new_snake; // �Ű��� ��ġ
		// �ʱ�ȭ
		new_snake.row = 0;
		new_snake.col = 0;
		new_snake.direction = 0;		

		if (cur_snake.row == head.row && cur_snake.col == head.col) {			
			// head�� ��� �״�� ����
			new_snake.row = head.row + drc[head.direction].first;
			new_snake.col = head.col + drc[head.direction].second;
			new_snake.direction = head.direction;
			head = new_snake; // head ������Ʈ			
		}
		else { // �� �� ������ ���
			new_snake = before_snake;
		}		
		before_snake = cur_snake; // before_snake �־���
		new_snake_position.push(new_snake);
		board[cur_snake.row][cur_snake.col] = 0;
		board[new_snake.row][new_snake.col] = 1;
	}	
	snake_position = new_snake_position; // snake ��ġ ������Ʈ
}

void change_head_direction(pic direct_change) {
	// drc -> right, left, up, down 
	//          0      1   2     3
		
	switch (head.direction) {
		case 0: // ���� head�� ������			
			if (direct_change.second == 'D') { // ���������� 90��
				head.direction = 3; // down ���� �ٲ���				
			}
			else {
				head.direction = 2; // up���� �ٲ���
			}
			break;
		case 1: // ���� head�� ����
			if (direct_change.second == 'D') { // ���������� 90��
				head.direction = 2; // up ���� �ٲ���
			}
			else {
				head.direction = 3; // down���� �ٲ���
			}
			break;
		case 2: // ���� head�� ����
			if (direct_change.second == 'D') { // ���������� 90��
				head.direction = 0; // right ���� �ٲ���
			}
			else {
				head.direction = 1; // left�� �ٲ���
			}
			break;
		case 3: // ���� head�� �Ʒ���
			if (direct_change.second == 'D') { // ���������� 90��
				head.direction = 1; // left�� �ٲ���
			}
			else {
				head.direction = 0; // right���� �ٲ���
			}
			break;
	}
}

void solve() {		
	head.row = 1, head.col = 1, head.direction = 0; // �ʱ� head ����
	board[1][1] = 1; // �ʱ� ���� ��ġ
	snake_position.push(head); // �ʱ� �� ��ǥ
	pic direct_change = change.front(); // �ʱ� ������ȯ ����
	change.pop();

	while (1) { // ���� ������ ������� �𸣴� ���ѷ���
		if (can_go()) { // �� ĭ �� �� �� ������ --> head�� üũ�ϸ��
			ans++;
			if (apple_check()) { // ���� ĭ�� ����� ������				
				move_snake_position(); // �� �ű��		
				snake_position.push(tail); // ���� �߰�
				board[tail.row][tail.col] = 1; // ���� board�� ǥ��
			}			
			else { // ��� ������

				move_snake_position(); // �� �ű�⸸
			}
			if (ans == direct_change.first) { // head ���� �ٲ�� �Ǵ� �ð��̸�				
				change_head_direction(direct_change);
				if (change.size() != 0) {
					direct_change = change.front();
					change.pop();
				}				
			}
		}
		else { // head ������ �Ұ����ϸ� ��������
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
