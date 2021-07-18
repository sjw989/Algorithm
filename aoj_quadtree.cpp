#include <iostream>
#include <array>
#include <vector>
using namespace std;

int C; // tc ����
int N; // quad tree�� ������
int f_n; // x�ȿ� �ִ� x�� ����
string inp_data; // �Է� ���� ����Ʈ��
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
		string::iterator it = inp_data.begin(); // ���� decode / incode���� ĭ
		string ans = solve(it);		
		result.push_back(ans);
	}	
	print();	
}