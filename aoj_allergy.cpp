#include <iostream>
#include <vector>
#include <array>
using namespace std;

int C; // tc 개수
int n, m; // 친구 수, 할 줄 아는 음식 수
int min_food; // 최소 음식 수
int cnt; // 해야하는 음식 수
array<int, 51> num_canEat; // num_canEat[1] = 1 --> 첫번째 친구가 먹을 음식은 1개
array<vector<int>, 51> person_to_food; // 각 사람마다 먹을 수 있는 음식
array<vector<int>, 51> food_to_person; // 각 음식마다 먹을 수 있는 사람
vector<string> friends;
vector<int> result;

int get_friendsIndex(string name) {
	for (int i = 0; i < friends.size(); i++) {
		if (name == friends[i]) {
			return i + 1;
		}
	}
	/*
	a b c d 이렇게 친구가 들어왔을 때,
	get_friendsIndex(d) 는 4를 return
	4번째 친구라는 의미
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
	} // 친구 이름 추가

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
	} // i번째 음식은 idx번째 친구들이 먹을 수 있음
}


int all_eat() {
	for(int i = 1; i <= n; i++) {
		if (num_canEat[i] == 0) {
			return i; // 먹을 음식이 없는 친구의 인덱스를 return
		}
	}
	return 0; // 모두 먹을 음식이 있다는 의미
}

void solve() {
	int k = all_eat();
	if (k == 0) { 
		min_food = min(cnt, min_food);
		return; // 모두 먹을 음식이 있다는 의미 
	}

	// k에는 먹을 음식이 없는 친구의 인덱스가 들어가있음
	for (auto fd : person_to_food[k]) {
		// fd = k번째 친구가 먹을 수 있는 음식 번호

		if (min_food - cnt == 1) {
			return; // min_food - cnt == 1 이라는 의미는 더이상 최소값을 찾을 수 없음
		}				
		for (int p : food_to_person[fd]) { 
			// k 번째 친구를 위해 준비한 음식으로 먹을 수 있는 애들 체크
			num_canEat[p]++;
		}
		cnt++; // fd를 준비한다고 가정

		solve(); // 다음으로 먹을 음식 없는 친구 탐색

		for (int p : food_to_person[fd]) {
			// k 번째 친구를 위해 준비한 음식으로 먹을 수 있는 애들 해제
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

