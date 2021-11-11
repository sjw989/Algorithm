#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#include <iomanip>
#define pii pair<int,int>
using namespace std;


typedef struct Guest{
	int start_row, start_col;
	int dest_row, dest_col;
};

int N, M, G; // ����ũ�� N x N, �°� �� M, �ʱ� ���� G
int dist; // �� �°��� ���������� �¿��ֱ� ���� ����� ����
pii cur_taxi; // ���� �ý���ġ
array<array<int, 21>, 21> board; // board N x N
array<array<pii, 21>, 21> dest; // �°��� �������� ���� array
array<int, 4> drow = { 0, 0, 1, -1 };
array<int, 4> dcol = { 1,-1, 0, 0 };

void input() {
	//ifstream in("test.txt");	
	cin >> N >> M >> G;	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {			
			cin >> board[i][j];
		}
	}
	int cur_r, cur_c;
	cin >> cur_r >> cur_c;	
	cur_taxi = make_pair(cur_r, cur_c);	
	for (int i = 0; i < M; i++) {
		Guest g;
		cin >> g.start_row >> g.start_col >> g.dest_row >> g.dest_col;
		board[g.start_row][g.start_col] = -1; // �°� ǥ��
		dest[g.start_row][g.start_col] = make_pair(g.dest_row, g.dest_col);
	}
}

pii find_guest() {	
	queue<pii> q;
	q.push(cur_taxi);	
	array <array<int, 21>, 21> visit = { 0 };
	array <array<int, 21>, 21> use_gas = { 0 };
	visit[cur_taxi.first][cur_taxi.second] = 1;	
	pii g = make_pair(25,25); // �¿� �մ�, �ʱⰪ���� �ſ� ū���� �־���	
	dist = 100; // �ýÿ� �մ� �Ÿ�, �ʱⰪ���� �ſ� ū���� �־���
	if (board[cur_taxi.first][cur_taxi.second] == -1) { // �ý���ġ == �մ���ġ�� ���
		dist = 0;
		g = cur_taxi;
		board[g.first][g.second] = 0;// �մ� board���� �����ֱ�
		return g;
	}
	while (!q.empty()) { // �ýð� board�� ����Ž���ϸ鼭 �¿� �մ��� ������
		pii cur = q.front();			
		q.pop();		
		for (int i = 0; i < 4; i++) {			
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];													
			if (next_row >= 1  && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] == 0 && board[next_row][next_col] != 1) { // ���� ĭ�� �湮���� �ʾҰ� ���� �ƴѰ��				
				visit[next_row][next_col] = 1; // �湮ó��
				use_gas[next_row][next_col] = use_gas[cur.first][cur.second] +  1 ; // ������������ ������ �Ÿ� ����
				if (board[next_row][next_col] == -1) { // ���� ĭ�� �մ��� �ִ� ���
					if (use_gas[next_row][next_col] < dist) { // ����մ� ���� �� ����� ���� �մ��� �ִ� ���
						dist = use_gas[next_row][next_col];
						g = make_pair(next_row, next_col);
					}
					else if (use_gas[next_row][next_col] == dist) { // ���� �մ԰� ���� �Ÿ��� �ٸ� �մ��� �ִ°��
						if (next_row < g.first) { // row �� ������ �մ��� ����
							dist = use_gas[next_row][next_col];
							g = make_pair(next_row, next_col);
						}
						else if (next_row == g.first) { // row �� ���ٸ�
							if (next_col < g.second) { // col�� �� ���� ���� ����
								dist = use_gas[next_row][next_col];
								g = make_pair(next_row, next_col);
							}
						}
					}
				}				
				else { 
					q.push(make_pair(next_row, next_col));
				}
			}
		}		
	}
	if (g.first != 25) {		
		board[g.first][g.second] = 0;// �մ� board���� �����ֱ�
	}
	return g; // (25,25)�� ���ϵǸ� �մ��� ���ٴ� �ǹ�
}

bool go_dest(pii pick_guest) {	
	queue<pii> q;
	q.push(pick_guest);
	array <array<int, 21>, 21> visit = { 0 };
	array <array<int, 21>, 21> use_gas = { 0 };
	visit[pick_guest.first][pick_guest.second] = 1;
	dist = 100;
	while (!q.empty()) { // �մ��� ������ �ִܰŸ� Ž��
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = cur.first + drow[i];
			int next_col = cur.second + dcol[i];
			if (next_row >= 1 && next_row <= N && next_col >= 1 && next_col <= N
				&& visit[next_row][next_col] == 0 && board[next_row][next_col] != 1) { // �湮���� �ʾҰ� ���� �ƴѰ��				
				visit[next_row][next_col] = 1;
				use_gas[next_row][next_col] = use_gas[cur.first][cur.second] + 1;

				if (next_row == dest[pick_guest.first][pick_guest.second].first
					&& next_col == dest[pick_guest.first][pick_guest.second].second) { // next�� �մ��� �������� ������					

					cur_taxi = make_pair(next_row, next_col); // �ý� ��ġ update
					dist = use_gas[next_row][next_col];
					return true;
				}
				else {					
					q.push(make_pair(next_row, next_col));
				}				
			}
		}
	}
	return false;
}

int solve() {	
	while (M != 0 && G > 0) { // �°��� ���� 0�̰ų�, ���ᰡ �� ������ �� ���� �ݺ�
		pii pick_guest = find_guest();
		if (pick_guest.first == 25) { // �ýð� �մ��� �� ã�� ���
			return -1;
		} 
		if (dist >= G) { // ���� �մ��� ã�µ� ���� ���� ���Ẹ�� �� ���� ����� ��� �������� �� �� ������
			return -1; // -1�� return
		}
		else { // �մ��� ã�µ� ���� ����� ����ߴ� ���
			G -= dist; // ���� ���� ������Ʈ						
			if (go_dest(pick_guest)) { // �մ��� ���������� ���� ��ΰ� �����ϴ� ���
				if (dist <= G) { // ������ ���� �������� ����ؾ��ϴ� ���ᰡ ����� ���
					M--; // �մ� �� -1
					G -= dist; // ���� ���� ������Ʈ
					G += dist * 2;
				}				
				else { // ���ᰡ ������� ���� ���
					return -1;
				}
			}
			else {
				return -1;
			}
		}						
	}
	if (M == 0) { // ��� �մ��� �� �̵���Ų ���
		return G;
	}
	return -1; // ���ᰡ �����ߴ� ���
}

void print(int ans) {	
	cout << ans;
}
int main() {
	input();		
	int ans = solve();
	print(ans);
}






