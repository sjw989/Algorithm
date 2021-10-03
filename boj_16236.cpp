#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#define pii pair<int,int>
using namespace std;

int N; // N x N
int fish_cnt; // ���� �����ִ� ����� ���� ��
int cur_size = 2; // �Ʊ����� ������
int ate; // ���� ���� ������� ��
int ans; // ���� ����� ������� ����� ��ƸԴ� �ð�
pii cur_position; // �ʱ�����ġ
queue<pii> fish_q;
array<array<int, 21>, 21> space;
array<array<int, 21>, 21> visit;
array<int, 4> drow = {0,0,1,-1};
array<int, 4> dcol = {1,-1,0,0};

void input() {
	ifstream in("test.txt");
	in >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			in >> space[i][j];
			if (space[i][j] != 0) {				
				if (space[i][j] == 9) {
					cur_position = make_pair(i, j);						
				} // �ʱ� �Ʊ��� ��ġ ����
				else {
					fish_q.push(make_pair(i, j));
					fish_cnt++;
				} // ������� ��ġ�� ����ִ� queue
			}			
		}
	}	
}

void set_visit() {
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 20; j++) {
			visit[i][j] = 0;
		}
	}
}

void get_distance() {
	queue<pii> bfs_q; // �Ÿ� ���ϴµ� ����� queue
	bfs_q.push(cur_position); // ���� ����� ��ġ �־��ֱ�	
	while (!bfs_q.empty()) { // ���� ��ġ�κ��� �� ����� ������ �Ÿ� ���ϱ�
		pii cur = bfs_q.front();				
		bfs_q.pop();
		for (int i = 0; i < 4; i++) {			
			if (cur.first + drow[i] >= 1 && cur.first+drow[i] <= N
				&& cur.second + dcol[i] >= 1 && cur.second + dcol[i] <= N
				&& space[cur.first + drow[i]][cur.second + dcol[i]] <= cur_size
				&& visit[cur.first + drow[i]][cur.second + dcol[i]] == 0) {
				// ���� �湮�� �� ���� �� ������ �� ������
				bfs_q.push(make_pair(cur.first + drow[i], cur.second + dcol[i]));
				visit[cur.first + drow[i]][cur.second + dcol[i]] = visit[cur.first][cur.second] + 1;
			}
		}
	}		
}

void bfs() {
	queue<pii> q = fish_q;	
	while (!q.empty()) {				
		set_visit(); // visit 0���� �ʱ�ȭ			
		get_distance(); // ��� ���������� ��ġ ���ϱ�		
		queue<pii> next_q;
		pii eat_fish; // ���� �����
		int eat_fish_to_shark = 987654321; // ���� ������ ��� ������ �Ÿ�
		while (!fish_q.empty()) { // ���� ����� ã��			
			pii cur = fish_q.front();						
			fish_q.pop();
			if (space[cur.first][cur.second] < cur_size) { // ����� ����� ���� ��� ������� ������					
				if (visit[cur.first][cur.second] != 0
					&&visit[cur.first][cur.second] < eat_fish_to_shark) { // ���� eat_fish���� �� ������ ������
					if (eat_fish != make_pair(0, 0) ){
						next_q.push(eat_fish);
					}
					eat_fish = cur; // eat_fish ������Ʈ
					eat_fish_to_shark = visit[cur.first][cur.second];
					continue;
				}
				else if (visit[cur.first][cur.second] == eat_fish_to_shark) { // �Ÿ��� ������
					if (eat_fish.first > cur.first) { // cur�� �� ���� �ִ� ���
						if (eat_fish != make_pair(0, 0)) {
							next_q.push(eat_fish);
						}
						eat_fish = cur; // ������Ʈ
						continue;
					}
					else if (eat_fish.first == cur.first) { // ���� row�� ���ٸ�
						if (eat_fish.second > cur.second) { // �� ���ʿ� �ִ� ��� 
							if (eat_fish != make_pair(0, 0)) {
								next_q.push(eat_fish);
							}
							eat_fish = cur; //������Ʈ
							continue;
						}
					}
				}				
			}
			next_q.push(cur);
		}		
		if (eat_fish_to_shark != 987654321) { // ���� ����⸦ ã������			
			space[cur_position.first][cur_position.second] = 0; // ��� ��ġ update			
			space[eat_fish.first][eat_fish.second] = 9; // ��� ��ġ -> ����� ��ġ			
			cur_position = eat_fish; // ��� ��ġ�� �Ű��ְ�
			ate++;		
			ans += visit[eat_fish.first][eat_fish.second]; // �� �������� ���� �ð� + ����
			fish_q = next_q;
			q = next_q; // ���� q Ž��
			if (ate == cur_size) { // ���� ���� ����� ������
				ate = 0; 
				cur_size++;
			}			
		}
		else { // ���� ����⸦ ��ã������ 			
			return;
		}			
	}
}

void print() {
	cout << ans;
}

int main() {
	input();
	get_distance();	
	bfs();
	print();
}