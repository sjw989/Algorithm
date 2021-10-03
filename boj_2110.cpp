#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int N, C; // ���� ��, ��ġ�Ϸ��� �������� ��
int ans;
vector<int> home;

void input() {
	//ifstream in("test.txt");
	cin >> N >> C;
	for (int i = 0; i < N; i++) {
		int k;
		cin >> k;
		home.push_back(k);
	}
}

void binary_search() {
	int start = 1, end = home[N - 1] - home[0];
	// N >= 2�̹Ƿ�, ������ ������ �ּҰ��� : 1, �ִ밣�� : ������ - ó��

	int cnt = 0;
	while (start <= end) {
		int before = home[0]; // ù��° ������ ������ ��ġ�ؾ���
		cnt = 1;
		int mid = (start + end) / 2; 
		/* start�� end�� �߰��� �������� ��� �����Ⱑ ��ġ��������		   
		    �Ǵ��غ��� ���� ������ ����*/		
		for (int i = 1; i < N; i++) {
			if (home[i] - before >= mid) { // mid �̻��� �������� ���� �� �ִ� ������				
				cnt++;
				before = home[i];
			}
		}		
		if (cnt >= C) { // ��� �����⸦ ���� �� �ִٸ�			
			ans = max(ans, mid);
			start = mid + 1; // �Ÿ��� �� ������ ã�ƺ�
		}
		else {
			end = mid - 1; // �Ÿ��� ����
		}
	}
}

void print() {
	cout << ans;
}

int main() {
	input();
	sort(home.begin(), home.end());
	binary_search();
	print();
}