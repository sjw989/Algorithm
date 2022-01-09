#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int N; // ���� ��
int M; // �� ����
int ans; // ����
int total; // �� ���� ������ �� ��
vector<int> budget; // ����

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
	int result = 0; // ���濡 �Ҵ��� ���� �հ�
	for (int b : budget) { 
		if (b - max_budget <= 0) { // �� ������ ������ �� �ִ� ������ ���Ѿ� ���� ���� ���
			result += b; // ���Ѿ��� ���� ������ ������.
		}
		else {
			result += max_budget;
		}
	}
	return result;
}

void solve() {
	sort(budget.begin(), budget.end());
	int lower = 0; // �ʱ� ���Ѿ�
	int upper = budget[N  - 1]; // �ʱ� ���Ѿ�

	while (lower < upper) {
		int mid = (lower + upper) / 2;
		int t = get_budget(mid);
		
		//cout << lower << " " << upper << " " << mid << " " << t << endl;
		if (t <= M && t > total) { // �� ������ �ѿ����� ���� �ѿ��꺸�� �۰� ������ ���պ��� ū���			
			ans = max(ans, mid);
			lower = mid + 1;		
			total = t;
		}
		else {
			upper = mid;
		}
	}

	// lower == upper ��� ó�� �ȵǾ����Ƿ� ����
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