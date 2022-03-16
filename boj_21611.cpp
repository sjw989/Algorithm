#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)

using namespace std;

int N, M; // ���� ũ��, ���� ����

array<array<int, 50>, 50> board;
vector<pii> query;
array<int, 5> result = { 0,0,0,0,0 };
array<pii, 5> delta = { mp(0,0), mp(-1,0), mp(1,0), mp(0,-1), mp(0,+1) }; // �� �� �� ��
array<pii, 5> delta2 = { mp(1,0), mp(0,+1), mp(-1,0),  mp(0,-1), }; // �� �� �� ��

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
	pii cur = mp(N / 2 + 1, N / 2); // 1�� ��ġ���� ����		
	int len = 1;
	vector<int> numbers;
	for (int i = 0; i < N / 2; i++) { // N / 2 �� 			
		for (int j = 0; j < 4; j++) { // �Ͽ���� �ݺ�
			for (int k = 0; k < len; k++) { // ���� len ��ŭ �ݺ�					
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				if (board[cur.first][cur.second] != 0) { // ���� ĭ�� ��ĭ�� �ƴϸ�
					numbers.push_back(board[cur.first][cur.second]);
				}
				cur = mp(nr, nc); // ���� ĭ���� �̵�
			}
			if (j == 0 || j == 2) { // ������ �� or �� �̸� ���� +1
				len++;
			}
		}
	}
	cur = mp(N / 2 + 1, N / 2); // 1�� ��ġ���� ����		
	len = 1;
	int idx = 0;
	numbers.resize(N * N, 0);
	for (int i = 0; i < N / 2; i++) { // N / 2 �� 			
		for (int j = 0; j < 4; j++) { // �Ͽ���� �ݺ�
			for (int k = 0; k < len; k++) { // ���� len ��ŭ �ݺ�					
				board[cur.first][cur.second] = numbers[idx];
				idx++;
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				cur = mp(nr, nc); // ���� ĭ���� �̵�
			}
			if (j == 0 || j == 2) { // ������ �� or �� �̸� ���� +1
				len++;
			}
		}
	}
}
void transform() {
	pii cur = mp(N / 2 + 1, N / 2); // 1�� ��ġ���� ����		
	int len = 1;
	int n = board[N / 2 + 1][N / 2];
	vector<int> info;
	int cnt = 0;
	for (int i = 0; i < N / 2; i++) { // N / 2 �� 			
		for (int j = 0; j < 4; j++) { // �Ͽ���� �ݺ�
			for (int k = 0; k < len; k++) { // ���� len ��ŭ �ݺ�					
				if (board[cur.first][cur.second] == n) { // ��ȣ�� ���� �ֵ���					
					cnt++;
				}
				else { // ��ȣ�� ���� ��ȣ�� �ٸ���					
					if (n > 0) {						
						info.push_back(cnt);
						info.push_back(n);
					}					
					cnt = 1;
					n = board[cur.first][cur.second];
				}
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				cur = mp(nr, nc); // ���� ĭ���� �̵�
			}
			if (j == 0 || j == 2) { // ������ �� or �� �̸� ���� +1
				len++;
			}
		}		
	}	
	if (n > 0) {// ������ ���� �ȵ��⶧���� ���� �־���
		info.push_back(cnt);
		info.push_back(n);
	}

	cur = mp(N / 2 + 1, N / 2); // 1�� ��ġ���� ����		
	len = 1;
	int idx = 0;
	for (int i = 0; i < N / 2; i++) { // N / 2 �� 			
		for (int j = 0; j < 4; j++) { // �Ͽ���� �ݺ�
			for (int k = 0; k < len; k++) { // ���� len ��ŭ �ݺ�									
				if (idx < info.size()) {
					board[cur.first][cur.second] = info[idx];
				}				
				int nr = cur.first + delta2[j].first;
				int nc = cur.second + delta2[j].second;
				cur = mp(nr, nc); // ���� ĭ���� �̵�
				idx++;
			}
			if (j == 0 || j == 2) { // ������ �� or �� �̸� ���� +1
				len++;
			}
		}
	}
}
void explosion() {				
	int n = board[N / 2 + 1][N / 2];		
	while (true) {
		vector<pii> pos; // ���ӵ� �������� ��ǥ
		bool is_explosion = false; // �̹� �ݺ����� ������ �Ͼ����
		pii cur = mp(N / 2 + 1, N / 2); // 1�� ��ġ���� ����				
		int len = 1;		
		for (int i = 0; i < N / 2; i++) { // N / 2 �� 			
			for (int j = 0; j < 4; j++) { // �Ͽ���� �ݺ�
				for (int k = 0; k < len; k++) { // ���� len ��ŭ �ݺ�					
					if (board[cur.first][cur.second] == n) { // ��ȣ�� ���� �ֵ���					
						pos.push_back(cur); // ������						
					}
					else { // ��ȣ�� ���� ��ȣ�� �ٸ���						
						if (pos.size() >= 4) { // 4�� �̻� ���ִ��� Ȯ��							
							is_explosion = true;
							for (pii p : pos) {																
								result[board[p.first][p.second]]++;								
								board[p.first][p.second] = 0; // ���� �����																										
							}
						}
						pos.clear();
						pos.push_back(cur); // ������
						n = board[cur.first][cur.second];						
					}
					int nr = cur.first + delta2[j].first;
					int nc = cur.second + delta2[j].second;
					cur = mp(nr, nc); // ���� ĭ���� �̵�
				}
				if (j == 0 || j == 2) { // ������ �� or �� �̸� ���� +1
					len++;
				}
			}
		}
		move(); // ���� �̵�				
		if (!is_explosion) {
			break;
		}
	}		
}


void solve() {
	for (pii q : query) { // M���� ���ڵ� �ߵ�		
		int d = q.first; // ����
		int s = q.second; // �ӵ�		
		for (int i = 1; i <= s; i++) {					
			int nr = (N / 2) + 1 + (i * delta[d].first);
			int nc = (N / 2) + 1 + (i * delta[d].second);			
			board[nr][nc] = 0; // ���� �ı�						
		}
		move(); // �����̵�				
		explosion(); // ���� ����								
		transform(); // ���� ��ȯ		
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