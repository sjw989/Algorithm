#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <bitset>
#include <queue>
#define pii pair<int,int>
using namespace std;

int minimum = 987654321;
int N, M; // ���� ũ��, ġŲ���� �ִ� ����
array<array<int, 51>, 51> village;
array<array<int, 51>, 51> dist;
vector<pii> chicken; // �� ġŲ���� ��ġ�� �������
vector<bool> can_chicken; // �� ġŲ���� ��ġ�� �������
vector<pii> home;

void input() {
	//ifstream in("test.txt");
	cin >> N >> M;	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> village[i][j];
			if (village[i][j] == 2) {
				chicken.push_back(make_pair(i, j)); // ġŲ�� ��ǥ ����
				can_chicken.push_back(true);
			}
			else if (village[i][j] == 1) {
				home.push_back(make_pair(i, j)); // �� ��ǥ ����
			}
			dist[i][j] = 987654321;
		}
	}
}

int calc_dist(pii a, pii b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int get_chickenDistance() {
	int chicken_dist = 0;
	for (int i = 0; i < home.size(); i++) {
		chicken_dist += dist[home[i].first][home[i].second];						
	} // init		
	if (chicken_dist < 0) {
		return 987654321;
	}
	return chicken_dist;
}

void dfs(int start) {				
	for (int i = 0; i < home.size(); i++) {
		dist[home[i].first][home[i].second] = 987654321;
	}
	for (int i = start; i < chicken.size(); i++) {
		pii remove_chicken = chicken[i]; // �����Ű���� �ϴ� ġŲ��
		can_chicken[i] = false; // ���ó��

		for (int i = 0; i < home.size(); i++) {
			for (int j = 0; j < chicken.size(); j++) {
				if (can_chicken[j]) {
					int d = calc_dist(home[i], chicken[j]);					
					dist[home[i].first][home[i].second] = min(dist[home[i].first][home[i].second], d);					
				}				
			}
		} // ��� �� �� ġŲ���� Ž���ؼ� �� ������ ġŲ�Ÿ� ����

		int n = 0;
		for (int i = 0; i < can_chicken.size(); i++) {
			if (can_chicken[i]) {
				n++;
			}
		}
		if (M == n) {			
			int d = get_chickenDistance();
			minimum = min(minimum, d); // ������ ġŲ�Ÿ� update		
		}				
		if (i + 1 <= chicken.size()) {
			dfs(i + 1); // dfs
		}		
		can_chicken[i] = true; 
	}
}

int main() {
	input();
	
	for (int i = 0; i < home.size(); i++) {
		for (int j = 0; j < chicken.size(); j++) {
			int d = calc_dist(home[i], chicken[j]);
			dist[home[i].first][home[i].second] = min(dist[home[i].first][home[i].second], d);
		}
	} 	
	int n = 0;
	for (int i = 0; i < can_chicken.size(); i++) {
		if (can_chicken[i]) {
			n++;
		}
	}
	if (M == n) {
		int d = get_chickenDistance();
		minimum = min(minimum, d); // ������ ġŲ�Ÿ� update		
	}	
	dfs(0);
	cout << minimum;	
}