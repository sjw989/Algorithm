#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int N, H; // N x H ����
int ans_break = 200001; // �ı��ؾ��ϴ� �ּ� ��ֹ� ��
int ans_cnt = 0; // �ı��ؾ��ϴ� �ּ� ��ֹ� ���� ���� ������ ����
vector<int> stalagmite; // ���� ����
vector<int> stalactite; // ������ ����

void input() {
	//ifstream in("test.txt");
	cin >> N >> H;
	for (int i = 1; i <= N; i++) {
		int k;
		cin >> k;
		if (i % 2 == 0) { // ¦����°�� ������			
			stalactite.push_back(k);
		}
		else { // Ȧ����°�� ����
			stalagmite.push_back(k);
		}		
	}	
}

void solve() {
	for (int h = 1; h <= H; h++) { // HlogN 
		int bottom = lower_bound(stalagmite.begin(),stalagmite.end(), h) - stalagmite.begin(); // ���� ���̿��� �ı��ϴ� ������ ����
		int top = upper_bound(stalactite.begin(), stalactite.end(), H - h) - stalactite.begin(); // ���� ���̿��� �ı��ϴ� �������� ����

		int cur_bottom = N / 2 - bottom;
		int cur_top = N / 2 - top; // ������ ó���� �ʿ��� ����		
		if (cur_bottom + cur_top < ans_break) { // ���ο� �ּҰ��� �߰�
			ans_cnt = 1; // cnt �ʱ�ȭ
			ans_break = cur_bottom + cur_top; // �ּҰ� ������Ʈ
		}
		else if (cur_bottom + cur_top == ans_break) {
			ans_cnt++;
		}
	}
}

void print() {	
	cout << ans_break << " " << ans_cnt;
}

int main() {
	input();
	sort(stalagmite.begin(), stalagmite.end());		
	sort(stalactite.begin(), stalactite.end());	
	solve();	
	print();
}