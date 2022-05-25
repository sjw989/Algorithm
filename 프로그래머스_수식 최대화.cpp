#include <iostream>
#include <string>
#include <vector>
#include <array>
#define ll long long
using namespace std;


vector<array<char, 3>> prio = { {'*','-','+'}, {'*','+','-'},
								{'+','-','*'}, {'+','*','-'},
								{'-','*','+'}, {'-','+','*'} };

vector<string> get_vec(string expression) {
	ll operand = 0;
	vector<string> element;
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] != '-' && expression[i] != '+' && expression[i] != '*') {
			operand *= 10;
			operand += expression[i] - '0';
			if (i == expression.length() - 1) {
				element.push_back(to_string(operand));
			}
		}
		else {
			element.push_back(to_string(operand));
			operand = 0;
			string str = "";
			element.push_back(str + expression[i]);
		}
	}
	return element;
}

long long solution(string expression) {
	ll answer = 0;
	for (int p = 0; p < prio.size(); p++) {
		array<char, 3> cur_prio = prio[p]; // ���� �켱����
		string exp = expression;
		vector<string> element = get_vec(exp);
		
		for (int i = 0; i < 3; i++) { // ������ 3�� ���
			vector<string> next_element;
			for (int j = 0; j < element.size(); j++) {
				if (element[j] != "-" && element[j] != "*" && element[j] != "+") {
					next_element.push_back(element[j]);
				}
				else {
					string str = "";
					if (element[j] == str + cur_prio[i]) { // ���� �켱���� �������� ���
						ll left = stol(element[j - 1]);
						ll right = stol(element[j + 1]);
						next_element.pop_back();
						if (element[j] == "+") {
							next_element.push_back(to_string(left + right));
						}
						else if (element[j] == "-") {
							next_element.push_back(to_string(left - right));
						}
						else if (element[j] == "*") {
							next_element.push_back(to_string(left * right));
						}
						element[j + 1] = next_element.back();
						j++; // right�� �����Ƿ� �� ĭ �� ����������
					}
					else {
						next_element.push_back(str + element[j]);
					}
				}
			}
			element = next_element;
		}
		if (answer < abs(stol(element[0]))) {
			answer = abs(stol(element[0]));
		}
	}
	return answer;
}

int main() {
	string exp = "100-200*300-500+20";
	solution(exp);

}

/*
1. �����ڴ� + - * 3����
2. ���� �켱������ ������������
3. ���� ����� ������� ���밪����
4. ������ ���ڰ� ���� ū ����?

*/