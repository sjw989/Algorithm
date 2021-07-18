#include <iostream>
#include <array>
#include <vector>
using namespace std;

int C; // tc 개수
int N; // quad tree의 사이즈
int f_n; // x안에 있는 x의 개수
string inp_data; // 입력 압축 쿼드트리
vector<string> result;

string solve(string::iterator& it) {
	if (inp_data.size() == 1) {
		return inp_data;
	}	
	string area[4];
	
	for (int i = 0; i < 4; i++) {
		it++;
		if (*it != 'x') {			
			area[i] = *it;
		}
		else {
			area[i] = solve(it);
		}
	}

	return "x" + area[2] + area[3] + area[0] + area[1];
}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

int main() {	
	cin >> C; 	
	for (int i = 0; i < C; i++) {
		cin >> inp_data;		
		string::iterator it = inp_data.begin(); // 현재 decode / incode중인 칸
		string ans = solve(it);		
		result.push_back(ans);
	}	
	print();	
}