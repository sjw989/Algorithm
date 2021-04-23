#include <iostream>
#include <string>
#include <array>
using namespace std;

array<array<int, 100>, 100> input = { 0 }; // max size input array

int get_sum(int start_n, int end_n, int start_m, int end_m) {
	int sum = 0;
	for (int i = start_n; i <= end_n; i++) {
		for (int j = start_m; j <= end_m; j++) {
			sum += input[i][j];
		}
	} // 시작 행 ~ 끝 행 + 시작 열 ~ 끝 열
	return sum;
}

int main() {
	int n, m; // n : 행 , m : 열
	cin >> n >> m; // 행과 열 입력
		
	// start input
	for (int i = 0; i < n; i++) {
		string inp;
		cin >> inp;
		for (int j = 0; j < inp.length(); j++) {
			char k = inp[j];
			input[i][j] = k - '0';
		}
	} // end of input
	
	long long best = 0; // result
	long long multi = 0; // 세 직사각형의 곱

	// case 1 --> 위에서 아래로 나란히 세 개
	for (int i = 0; i < n - 2; i++) { // 첫 번째 직사각형이 택할 수 있는 최대 행 수
		for (int j = i+1; j < n - 1; j++) {
			long long rect1_sum = get_sum(0, i, 0, m-1);
			long long rect2_sum = get_sum(i + 1, j, 0, m-1);
			long long rect3_sum = get_sum(j+1, n - 1, 0, m-1);
			multi = rect1_sum * rect2_sum * rect3_sum;
			best = max(multi, best);
		}
	}
	// case 2 --> 왼쪽에서 오른쪽으로 나란히 세 개
	for (int i = 0; i < m - 2; i++) { // 첫 번째 직사각형이 택할 수 있는 최대 행 수
		for (int j = i + 1; j < m - 1; j++) {
			long long rect1_sum = get_sum(0, n - 1, 0, i);
			long long rect2_sum = get_sum(0, n - 1, i+1, j);
			long long rect3_sum = get_sum(0, n - 1 , j+1, m-1);
			multi = rect1_sum * rect2_sum * rect3_sum;
			best = max(multi, best);
		}
	}
	// --> 오르쪽 아래위로 모퉁이 포함
	// case 3 --> 왼쪽 아래로 쭈욱, 오른쪽 아래위로 두 개
	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			long long rect1_sum = get_sum(0, n - 1, 0, i);
			long long rect2_sum = get_sum(0, j, i + 1, m - 1);			
			long long rect3_sum = get_sum(j+1, n - 1, i+1, m - 1);
			multi = rect1_sum * rect2_sum * rect3_sum;
			best = max(multi, best);
		}
	}
	// cout << rect1_sum << " " << rect2_sum << " " << rect3_sum << " " << endl;
	// --> 왼쪽 아래위로 모퉁이 포함
	// case 4 --> 오른쪽 아래로 쭈욱, 왼쪽 아래위로 두 개
	for (int i = m-1; i > 0; i--) {
		for (int j = 0; j < n - 1; j++) {
			long long rect1_sum = get_sum(0, n - 1, i, m - 1);
			long long rect2_sum = get_sum(0, j, 0, i - 1);
			long long rect3_sum = get_sum(j + 1, n - 1, 0, i-1);
			multi = rect1_sum * rect2_sum * rect3_sum;
			best = max(multi, best);
		}
	}
	// case 5 --> 위에 왼쪽에서 오른쪽우로 쭈욱, 밑에 좌우로 두 개
	for (int i = 0; i < n - 1 ; i++) {
		for (int j = 0; j < m-1; j++) {
			long long rect1_sum = get_sum(0, i, 0, m - 1);
			long long rect2_sum = get_sum(i+1, n - 1, 0, j);
			long long rect3_sum = get_sum(i+1, n - 1, j+1, m-1);
			multi = rect1_sum * rect2_sum * rect3_sum;
			best = max(multi, best);
		}
	}
	// case 6 --> 밑에 왼쪽에서 오른쪽우로 쭈욱, 위에 좌우로 두 개
	for (int i = n-1; i > 0; i--) {
		for (int j = 0; j < m - 1; j++) {
			long long rect1_sum = get_sum(i, n - 1 , 0, m - 1);
			long long rect2_sum = get_sum(0, i - 1 , 0, j);
			long long rect3_sum = get_sum(0, i - 1, j + 1, m - 1);
			multi = rect1_sum * rect2_sum * rect3_sum;
			best = max(multi, best);
		}
	}
	cout << best << endl;
	return 0;
}