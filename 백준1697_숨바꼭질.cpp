#include <iostream>
#include <queue>
#include <array>
#include <algorithm>
using namespace std;

int N, K;
array<int, 100001> visit = { 0 };

int main() {
	cin >> N >> K;
	queue<int> soobin;
	soobin.push(N); // ���� ��ǥ
	visit[N] = 1;
	int count = 0;
	int seg_count = 1; // �ʱⰪ 1
	while (!soobin.empty()) {
		int seg = 0; // �� ������ ���� ������ �̾��� �� �ִ� segment�� ����
		for (int i = 0; i < seg_count; i++) {
			int nod = soobin.front();
			if (nod == K) {
				cout << count << endl;
				exit(0);
			}
			else {
				if (nod + 1 <= 100000 && visit[nod + 1] == 0) {
					soobin.push(nod + 1);
					visit[nod + 1] = 1;
					seg++;
				}
				if (nod - 1 <= 100000 && visit[nod - 1] == 0) {
					soobin.push(nod - 1);
					visit[nod - 1] = 1;
					seg++;
				}
				if (nod * 2 <= 100000 && visit[nod * 2] == 0) {
					soobin.push(nod * 2);
					visit[nod * 2] = 1;
					seg++;
				}
			}
			soobin.pop();
		}
		count++;
		seg_count = seg;
	}
}