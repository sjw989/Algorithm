#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int N; // ��ü ���� ��
int w; // ���� ����

bool compare(array<long long, 2> c1, array<long long, 2> c2) {
	return c1[1] > c2[1];
}

int main() {
	cin >> N >> w;
	vector<array<long long, 2>> all_candy;

	for (int i = 0; i < N; i++) {
		array<long long, 2> candy = { 0 };
		for (int j = 0; j < 2; j++) {
			int n;
			cin >> n;
			candy[j] = n;
		}
		all_candy.push_back(candy);
	} // end of input
	sort(all_candy.begin(), all_candy.end(), compare);
	// ������������ ����
	vector<array<long long,2>> sum_3;
	vector<array<long long, 2>> sum_5;

	array<long long, 2> init = { 0 };
	sum_3.push_back(init);
	sum_5.push_back(init);
	for (auto i : all_candy) {
		if (i[0] == 3) {
				i[0] += sum_3.back()[0];
				i[1] += sum_3.back()[1];
				sum_3.push_back(i);
		}
		if (i[0] == 5) {
				i[0] += sum_5.back()[0];
				i[1] += sum_5.back()[1];
				sum_5.push_back(i);
		}
	} // ������ ���ϴ� �ڵ�
	
	int max_5 = w / 5; // ���� 5�� ������ �ִ� ����
	int size_5 = sum_5.size() -1;
	int size_3 = sum_3.size() -1;

	long long result = 0;
	/*
		min (max_5, size)�� �ϴ� ������ ���࿡ 5g ������ 5�� �ۿ� ���µ�
		����뷮�� 30g�̸� 30/5=6���� �߸������� �� ����
		min (num_3, size)�� �ϴ� ������ ����
	*/
	for (int i = 0; i <= min(max_5,size_5); i++) {
		int max_3 = (w - sum_5[i][0]) / 3 ;
		int num_3 = min(max_3, size_3);
		result = max(result, sum_5[i][1] + sum_3[num_3][1]);
	}
	 // 5�� ������ �ϳ��� �÷����鼭 �׿� ���� 3�� ������ �ٲ��
	 // �װſ� �°� ������ ���Ϳ��� �ε����� �ҷ���
	cout << result << endl;
}