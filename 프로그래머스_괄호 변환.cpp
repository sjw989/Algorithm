#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_correct(string str) {
    // 괄호는 항상 열림 -> 닫힘 순으로
    int n = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            n++;
        }
        else {
            n--;
        }
        if (n < 0) {
            return false;
        }
    }
    return true;
}

pair<string, string> divide_string(string p) {
    int left = 0, right = 0; // 왼쪽볼록, 오른쪽볼록 개수
    string u = "", v = "";
    for (int i = 0; i < p.length(); i++) {
        if (left != 0 && (left == right)) {
            v += p[i];
        }
        else {
            if (p[i] == '(') {
                left++;
                u += p[i];
            }
            else {
                right++;
                u += p[i];
            }
        } 
    }
    return make_pair(u, v);
}

string solve(string p) {
    pair<string, string> divided = divide_string(p);
    string u = divided.first, v = divided.second; // 문자열 u와 v로 쪼개기
    if (is_correct(u)) { // u가 올바른 괄호 문자열이라면
        if (v != "") { // v가 빈칸이 아닌경우
            v = solve(v); // v를 올바른 괄호 문자열로 만들어줌
        }        
        return u + v; // 수행항 결과를 u에 붙여 리턴
    }
    
    string temp = "(";
    temp += solve(v);
    temp += ")";
    for (int i = 1; i < u.length() - 1; i++) {
        if (u[i] == '(') {
            temp += ')';
        }
        else {
            temp += '(';
        }
    }    
    return temp;
}

string solution(string p) {
    string answer = "";    

    if (is_correct(p)) { // 입력이 "올바른 괄호 문자열"인 경우
        //cout << p;
        return p;
    }
    answer = solve(p);

    



    //cout << answer;
    return answer;
}

int main() {
    string p = ")()()()()()()()(";
    solution(p);
}

/*
1. ( 혹은 ) 로만 이루어진 문자열인 경우, 개수가 같다면 
    -> 균형잡힌 괄호 문자열

2. 1 + 두개의 짝도 모두 같을 경우 
    -> 올바른 괄호 문자열

3.  1(w)을 2로 바꿀수있음
   3-1. 빈 문자열인 경우, 빈 문자열을 return
   3-2. w를 두개의 균형잡힌 문자열 u, v로 분리
         -> 단 u는 더이상 분리 불가능해야하며, v는 빈문자열 가능
   3-3. u가 올바른 문자열인 경우, v에 대해서 1부터 다시수행
        -> u+v를 리턴
   3-4.올바른 문자열이 아닌경우
       -> 빈 문자열에 첫 번째 문자로 (를 붙인다
       -> v에 대해서 1단계부터 재귀적으로 수행한 결과를 이어붙인다.
       -> )를 붙인다
       -> u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서
          뒤에 붙인다
       -> 리턴



*/