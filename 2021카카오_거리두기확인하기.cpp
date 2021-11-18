#include <Iostream>
#include <vector>
#define pii pair<int,int>
using namespace std;



vector<pii> people;
vector<string> room;

void get_people(int row, vector<vector<string>> places) {		
	room = places[row]; 
	people.clear();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (room[i][j] == 'P') {
				people.push_back(make_pair(i, j));
			}
		}		
	}	
}

int get_distance(pii a, pii b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

bool solve() {
	for (int i = 0; i < people.size(); i++) {
		pii cur = people[i];
		for (int j = i + 1; j < people.size(); j++) {
			pii next = people[j];
			if (get_distance(cur, next) <= 2) { // ����ư �Ÿ��� 2 ������ ���
				if (cur.first == next.first) { // �� ����� row�� ���� ���
					if (abs(cur.second - next.second) == 1|| 
						room[cur.first][(cur.second + next.second) / 2] == 'O') { 
						// �ٷ� ���ڸ� or �� ���̰� ��ĭ�� ���
						return false; // �Ÿ��α� ����
					}
				}
				else if (cur.second == next.second) { // �� ����� col�� ���� ���
					if (abs(cur.first - next.first) == 1 ||
						room[(cur.first + next.first) / 2][cur.second] == 'O') {
						// �ٷ� ���Ʒ� �ڸ� or �� ���̰� ��ĭ�� ���						
						return false; // �Ÿ��α� ����
					}
				}

				else { // �밢���� ��ġ�� ���
					if (cur.second < next.second) { // 11-5 �밢������ ���� ���
						if (room[cur.first][cur.second + 1] == 'O' || room[cur.first + 1][cur.second] == 'O') {
							// cur�� �� or �Ʒ��� ��ĭ�� ���							
							return false; // ����
						}
					}
					else { // 1 - 7 �밢������ ���� ���
						if (room[cur.first][cur.second - 1] == 'O' || room[cur.first + 1][cur.second] == 'O') {
							// cur�� �� or �Ʒ��� ��ĭ�� ���							
							return false; // ����
						}
					}
				}
			}
		}
	}
	return true;
}

int main() {
	vector<vector<string>> places = { {"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},
								 {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
								 {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
								 {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
								 {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"} };
	vector<int> answer;
	for (int i = 0; i < 5; i++) {
		get_people(i, places);
		if ( solve() ) {
			answer.push_back(1);
		}
		else {
			answer.push_back(0);
		}
	}	
}