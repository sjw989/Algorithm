#include <iostream>
#include <vector>
#include <array>
using namespace std;

int C; // tc ����
int n, m; // ģ�� ��, �� �� �ƴ� ���� ��
int min_food; // �ּ� ���� ��
int cnt; // �ؾ��ϴ� ���� ��
array<int, 51> num_canEat; // num_canEat[1] = 1 --> ù��° ģ���� ���� ������ 1��
array<vector<int>, 51> person_to_food; // �� ������� ���� �� �ִ� ����
array<vector<int>, 51> food_to_person; // �� ���ĸ��� ���� �� �ִ� ���
vector<string> friends;
vector<int> result;

int get_friendsIndex(string name) {
	for (int i = 0; i < friends.size(); i++) {
		if (name == friends[i]) {
			return i + 1;
		}
	}
	/*
	a b c d �̷��� ģ���� ������ ��,
	get_friendsIndex(d) �� 4�� return
	4��° ģ����� �ǹ�
	*/
}

void init() {
	cnt = 0;
	min_food = 987654321;
	friends.clear();	
	for (int i = 1; i <= 50; i++) {
		num_canEat[i] = 0;
		food_to_person[i].clear();	
		person_to_food[i].clear();
	}	
}

void input() {
	cin >> n >> m;
	init();
	for (int i = 0; i < n; i++) {
		string name;
		cin >> name;
		friends.push_back(name);
	} // ģ�� �̸� �߰�

	for (int i = 1; i <= m; i++) {		
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			string name;
			cin >> name;
			int idx = get_friendsIndex(name);
			food_to_person[i].push_back(idx);
			person_to_food[idx].push_back(i);
		}
	} // i��° ������ idx��° ģ������ ���� �� ����
}


int all_eat() {
	for(int i = 1; i <= n; i++) {
		if (num_canEat[i] == 0) {
			return i; // ���� ������ ���� ģ���� �ε����� return
		}
	}
	return 0; // ��� ���� ������ �ִٴ� �ǹ�
}

void solve() {
	int k = all_eat();
	if (k == 0) { 
		min_food = min(cnt, min_food);
		return; // ��� ���� ������ �ִٴ� �ǹ� 
	}

	// k���� ���� ������ ���� ģ���� �ε����� ������
	for (auto fd : person_to_food[k]) {
		// fd = k��° ģ���� ���� �� �ִ� ���� ��ȣ

		if (min_food - cnt == 1) {
			return; // min_food - cnt == 1 �̶�� �ǹ̴� ���̻� �ּҰ��� ã�� �� ����
		}				
		for (int p : food_to_person[fd]) { 
			// k ��° ģ���� ���� �غ��� �������� ���� �� �ִ� �ֵ� üũ
			num_canEat[p]++;
		}
		cnt++; // fd�� �غ��Ѵٰ� ����

		solve(); // �������� ���� ���� ���� ģ�� Ž��

		for (int p : food_to_person[fd]) {
			// k ��° ģ���� ���� �غ��� �������� ���� �� �ִ� �ֵ� ����
			num_canEat[p]--;
		}
		cnt--;
	}
}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}


int main() {	
	cin >> C;	
	for (int i = 0; i < C; i++) {		
		input();
		solve();
		result.push_back(min_food);
	}	
	print();
}

