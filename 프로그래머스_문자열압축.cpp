#include <iostream>
#include <string>
#include <vector>

using namespace std;


int solution(string s) {
    int answer = 987654321;
    int N = s.length();
    if (N == 1) {
        return 1;
    }
    for (int i = 1; i <= N / 2; i++) { // 가능한 길이
        string cur = s.substr(0, i);
        string cmp_str = ""; // 압축된 문자열
        int cnt = 0; // 반복된 횟수

        for (int j = i; j < N ; j += i) { // 부분 문자열의 시작 인덱스
            string sub = s.substr(j, i);
            if (cur == sub) {
                cnt++; // 반복되는 횟수 카운팅
            }
            else {
                if (cnt > 0) { // 반복된 적 있으면
                    cmp_str += to_string(cnt + 1);
                }
                cmp_str += cur;
                cur = sub;
                cnt = 0;
            }
        }

        if (cnt > 0) { // 반복된 적 있으면
            cmp_str += to_string(cnt + 1);
        }
        cmp_str += cur; // 마지막에 더해지지 못한 문자열
        

        int len = cmp_str.size();
        answer = min(answer, len);
    }
    return answer;
}
int main() {
    solution("ac");
}