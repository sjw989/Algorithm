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
    for (int i = 1; i <= N / 2; i++) { // ������ ����
        string cur = s.substr(0, i);
        string cmp_str = ""; // ����� ���ڿ�
        int cnt = 0; // �ݺ��� Ƚ��

        for (int j = i; j < N ; j += i) { // �κ� ���ڿ��� ���� �ε���
            string sub = s.substr(j, i);
            if (cur == sub) {
                cnt++; // �ݺ��Ǵ� Ƚ�� ī����
            }
            else {
                if (cnt > 0) { // �ݺ��� �� ������
                    cmp_str += to_string(cnt + 1);
                }
                cmp_str += cur;
                cur = sub;
                cnt = 0;
            }
        }

        if (cnt > 0) { // �ݺ��� �� ������
            cmp_str += to_string(cnt + 1);
        }
        cmp_str += cur; // �������� �������� ���� ���ڿ�
        

        int len = cmp_str.size();
        answer = min(answer, len);
    }
    return answer;
}
int main() {
    solution("ac");
}