#include <iostream>
#include <fstream>
#include <array>
#define arr array<array<int,6>,6>
using namespace std;

int N; // 행렬 사이즈
long long B; // 지수승
arr matrix; // 행렬 최대 5x5
void input() {
	//ifstream in("test.txt");
	cin >> N >> B;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> matrix[i][j];
		}
	}
}

arr calc(arr sub_mat1, arr sub_mat2) {
	arr calc_arr = {0,};
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			calc_arr[i][j] = 0;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int v = 0;
			for (int k = 1; k <= N; k++) {
				v += (sub_mat1[i][k]%1000 * sub_mat2[k][j] % 1000) % 1000;
			}
			calc_arr[i][j] = v % 1000;
		}
	}
	return calc_arr;
}
void print(arr ans) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << ans[i][j]%1000 << " ";
		}
		cout << endl;
	}	
}
arr solve(arr sub_matrix, long long e) {				
	if (e == 1) { // base state
		return sub_matrix; // 인자로 받은 행렬 그대로 return
	}
	else {
		arr sub_mat1 = solve(sub_matrix, e / 2 );		
		if (e % 2 == 0) { // e가 짝수인 경우			
			return calc(sub_mat1, sub_mat1); // 똑같은 애들끼리 걍 연산해서 return
		}		
		// 홀수인 경우		
		return calc(calc(sub_mat1, sub_mat1),sub_matrix); 
	}
}

int main() {	
	input();
	arr ans = solve(matrix, B);
	print(ans);	
}