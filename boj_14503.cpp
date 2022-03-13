#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#define MAX 50+1
#define mp(a,b) make_pair(a,b)
#define pii pair<int,int>
using namespace std;


int N, M; //  N x M
int ans; // ����
int dir; // �κ�û�ұ��� ���� : ������� 0,1,2,3
pii pos; // �κ�û�ұ��� ��ġ
array<pii, 4> delta = { mp(-1,0), mp(0,1), mp(1,0), mp(0,-1) }; // �� �� �� ��
array<array<int, MAX>, MAX> board; // ��,���� ������ ĭ�� ���� (1 , N , 1 , M )

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
		
		if (board[pos.first][pos.second] == 0) { // ������ġ û���ϱ�
			ans++;
			board[pos.first][pos.second] = -1; 			
		}				
		bool can_clean = false; // 4���� �� û�Ұ����� ĭ�� �ִ���		
		// �ٶ󺸴� ������ �������� �ݽð�� ȸ���ϸ� û�Ұ����� ĭ ã��
		for (int i = 0; i < 4; i++) { // 4�� �ݽð�� ȸ����Ŵ			
			dir--; // �������� ȸ��
			if (dir < 0) { dir = 3; } // ����ó��
			int nr = pos.first + delta[dir].first;
			int nc = pos.second + delta[dir].second; // ������ġ		

			if (nr > 1 && nr < N && nc > 1 && nc < M && board[nr][nc] == 0) { // �������� ȸ���� ĭ�� û�� �����ϸ�															
				pos = mp(nr, nc); // �� �������� ����
				can_clean = true; // û�Ұ����� ĭ�� ����
				break;
			}
			
		}				
		if(!can_clean) { // 4������ û�Ұ����� ĭ�� �������� ������					
			// �ٶ󺸴� ������ ������ä ����
			int back_dir = (dir + 2) % 4; // ���� ����			
			int nr = pos.first + delta[back_dir].first;
			int nc = pos.second + delta[back_dir].second; // 1ĭ ������ ��ġ
			if (nr > 1 && nr < N && nc > 1 && nc < M && board[nr][nc] != 1) { // ���� ������ ���
				pos = mp(nr, nc);
			}
			else { // ���� ���ϴ� ���
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
1. ���� �ٶ󺸴� ������ �������� ���� ������� Ž��
2. ���� ���⿡ û������ ���� ������ �����Ѵٸ� �� �������� ȸ���ϰ� ��ĭ ����
    -> �������� �� ĭ ����� ������ �������� ��ȯ,
		delta �迭���� �ε��� -1�� �ٿ���
3. ���ʹ��⿡ û���� ������ ���ٸ� �������� ��ȯ�ϰ� 2�� ���ư�
   -> �ݽð�� ���ư��� û�Ұ��� Ž��
4. 4���� ��� û�Ұ��Ǿ��ְų� ���� ��� -> �ٶ󺸴� ������ ��ġ�� ä �� ĭ �����ϰ� 2������	
   -> ������ �ȵǴ� ��� ����
*/