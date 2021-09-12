#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int N;
long long ans;
array<long long, 100001> dist;
array<long long, 100001> price;


void input() {
	//ifstream in("test.txt");
	cin >> N;
	int k;
	for (int i = 1; i <= N-1; i++) {		
		cin >> k;
		dist[i] = k;
	} // ���ð��� �Ÿ�
	for (int i = 1; i <= N; i++) {
		cin >> k;
		price[i] = k;
	} // ������ ���ʹ� ����
}

void greedy() {
	/*
	�̹� ���� ������ ������ ���� ���� ������ ���ݺ��� ��θ�,
	�ּҸ� ����.
	�̹� ���� ������ ������ �ڽź��� ������� ������ ã�������� �����ְ�
	�װŸ�ŭ Ŀ��
	*/
	long long start = 1; // ������
	long long d = dist[start];
	for (int i = 2; i <= N - 1; i++) {
		if (price[start] < price[i]) { // ���� �����ҷ� ���� �� ���� Ŀ��ġ�� ���
			d += dist[i];
		}
		else {
			ans += d * price[start];
			d = dist[i];
			start = i;		

		}
	}
	ans += d * price[start];
}

int main() {
	input();
	greedy();
	cout << ans;
}