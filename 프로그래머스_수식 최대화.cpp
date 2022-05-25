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
		array<char, 3> cur_prio = prio[p]; // 현재 우선순위
		string exp = expression;
		vector<string> element = get_vec(exp);
		
		for (int i = 0; i < 3; i++) { // 연산자 3개 계산
			vector<string> next_element;
			for (int j = 0; j < element.size(); j++) {
				if (element[j] != "-" && element[j] != "*" && element[j] != "+") {
					next_element.push_back(element[j]);
				}
				else {
					string str = "";
					if (element[j] == str + cur_prio[i]) { // 현재 우선순위 연산자인 경우
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
						j++; // right를 썼으므로 한 칸 더 증가시켜줌
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
1. 연산자는 + - * 3가지
2. 같은 우선순위는 존재하지않음
3. 계산된 결과가 음수라면 절대값으로
4. 제출한 숫자가 가장 큰 것은?

*/