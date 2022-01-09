#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int N; // 지방 수
int M; // 총 예산
int ans; // 정답
int total; // 각 지방 예산의 총 합
vector<int> budget; // 예산

void input() {
	//ifstream in("test.txt");
	cin >> N;
	for (int i = 0; i < N; i++) {
		int k;
		cin >> k;
		budget.push_back(k);
	}
	cin >> M;
}

int get_budget(int max_budget) {
	int result = 0; // 지방에 할당할 예산 합계
	for (int b : budget) { 
		if (b - max_budget <= 0) { // 각 지방이 가져갈 수 있는 예산이 상한액 보다 작은 경우
			result += b; // 상한액을 넘지 않으면 더해줌.
		}
		else {
			result += max_budget;
		}
	}
	return result;
}

void solve() {
	sort(budget.begin(), budget.end());
	int lower = 0; // 초기 하한액
	int upper = budget[N  - 1]; // 초기 상한액

	while (lower < upper) {
		int mid = (lower + upper) / 2;
		int t = get_budget(mid);
		
		//cout << lower << " " << upper << " " << mid << " " << t << endl;
		if (t <= M && t > total) { // 각 지방의 총예산이 국가 총예산보다 작고 이전의 총합보다 큰경우			
			ans = max(ans, mid);
			lower = mid + 1;		
			total = t;
		}
		else {
			upper = mid;
		}
	}

	// lower == upper 경우 처리 안되었으므로 해줌
	int b = get_budget(upper); 
	if (b <= M && b > total) {
		ans = max(ans, upper);
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