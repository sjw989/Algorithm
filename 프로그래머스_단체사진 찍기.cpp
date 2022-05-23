#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;


// ���� ������ ������ ��� �Լ� ���� �ʱ�ȭ �ڵ带 �� �ۼ����ּ���.
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
            string condition = data[i]; // ���� ������
            char curf = condition[0]; // ������ ������ ������
            char nextf = condition[2]; // ��� ������
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
1. n : ������ ����,
2. data : n���� ���ҷ� �̷���� ���ڿ� �迭
3. data�� ���� 5�� string
  1,3 -> A C F J M  N  R T (�ɸ��� �̸�)
  1 -> ������ ������ �ɸ���
  3 -> ������ �ɸ���
  2 -> �׻� ~ ��
  4 -> =  <  >  ���� �̸�, �ʰ�
  5 -> 0 ~ 6 ���� ���ǿ� ���õǴ� ���� (�� �ɸ��� ������ �ٸ� �ɸ��� ��)
*/