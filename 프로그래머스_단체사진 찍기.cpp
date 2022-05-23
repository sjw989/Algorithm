#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;


// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {    
    array<char, 8> name = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
    vector<string> permutation;
    do {
        string str = "";
        for (int i = 0; i < name.size(); i++) {
            str += name[i];
        }
        permutation.push_back(str);
    } while (next_permutation(name.begin(), name.end()));
    
    int answer = 0;
    for (string pmt : permutation) {
        bool is_correct = true;
        for (int i = 0; i < data.size(); i++) {
            string condition = data[i]; // 현재 데이터
            char curf = condition[0]; // 조건을 제시한 프렌즈
            char nextf = condition[2]; // 상대 프렌즈
            int num = condition[4] - '0';
            int dist = abs(distance(find(pmt.begin(), pmt.end(), curf), find(pmt.begin(), pmt.end(), nextf))) - 1;
            //cout << pmt << " " << curf << "," << nextf << " " << dist << endl;
            if (condition[3] == '=') {
                if (dist != num) {
                    is_correct = false;
                    break;
                }
            }
            else if (condition[3] == '<') {
                if (dist >= num) {
                    is_correct = false;
                    break;
                }
            }
            else {
                if (dist <= num) {
                    is_correct = false;
                    break;
                }
            }
        }
        if (is_correct) {
            answer++;
        }
    }
    return answer;

}

int main() {
    int n = 2;
    vector<string> data = { "N~F<6" };
    solution(n, data);    
}

/*
1. n : 조건의 개수,
2. data : n개의 원소로 이루어진 문자열 배열
3. data는 길이 5의 string
  1,3 -> A C F J M  N  R T (케릭터 이름)
  1 -> 조건을 제시한 케릭터
  3 -> 상대방의 케릭터
  2 -> 항상 ~ 임
  4 -> =  <  >  같음 미만, 초과
  5 -> 0 ~ 6 정수 조건에 제시되는 간격 (두 케릭터 사이의 다른 케릭터 수)
*/