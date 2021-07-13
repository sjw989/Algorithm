#include <iostream>
#include <fstream>
#include <array>
#include <vector>
using namespace std;

int C; // tc ����
int n, m; // �л� ��, ģ�� �� ��
int result; // ���
vector<int> res;
array<vector<int>, 10> friends; // ģ�� ����
array<bool, 10> can_pair; // ¦�� �ִ��� ������

void input() {
	cin >> n >> m;	
	for (int i = 0; i < m; i++) {
		int s1 = 0, s2 = 0;
		cin >> s1 >> s2;
		friends[s1].push_back(s2);
		friends[s2].push_back(s1);
	}
}

bool all_pair() {
	for (int i = 0; i < n; i++) {
		if (can_pair[i]) { // �ϳ��� ¦ ���� �� �ִ°� ������
			return false;
		}
	}
	return true; // ��� ¦ ���� �� ������
}

void solve(int cur) {			
	can_pair[cur] = false; // cur ¦���� ó��
	
	vector<int> can_friend = friends[cur];
	for (auto num : can_friend) {
		
		if(can_pair[num]) { // cur�� ģ���� num�� �� ���� ¦�� ���� ���
			can_pair[num] = false; // cur�� ¦�� ������

			if (all_pair()) { // ��� ¦����������			
				result++;
				can_pair[num] = true; // cur�� ¦ ����
				continue;
			}			
			for (int next = cur + 1; next < n; next++) {			
				if (can_pair[next]) {					
					solve(next);
					break;
				}
			}			
			can_pair[num] = true; // cur�� ¦ ����
		}	
	}
	can_pair[cur] = true;
}

void print() {
	for (auto ans : res) {
		cout << ans << endl;
	}
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {				
		input();
		for (int j = 0; j < n; j++) {
			can_pair[j] = true;
		}
		
		solve(0);		
		for (int j = 0; j < n; j++) {
			friends[j].clear();
			can_pair[j] = true;
		}
		res.push_back(result);
		result = 0;		
	}
	print();	
}