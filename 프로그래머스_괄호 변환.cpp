#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_correct(string str) {
    // ��ȣ�� �׻� ���� -> ���� ������
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
    int left = 0, right = 0; // ���ʺ���, �����ʺ��� ����
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
    string u = divided.first, v = divided.second; // ���ڿ� u�� v�� �ɰ���
    if (is_correct(u)) { // u�� �ùٸ� ��ȣ ���ڿ��̶��
        if (v != "") { // v�� ��ĭ�� �ƴѰ��
            v = solve(v); // v�� �ùٸ� ��ȣ ���ڿ��� �������
        }        
        return u + v; // ������ ����� u�� �ٿ� ����
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

    if (is_correct(p)) { // �Է��� "�ùٸ� ��ȣ ���ڿ�"�� ���
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
1. ( Ȥ�� ) �θ� �̷���� ���ڿ��� ���, ������ ���ٸ� 
    -> �������� ��ȣ ���ڿ�

2. 1 + �ΰ��� ¦�� ��� ���� ��� 
    -> �ùٸ� ��ȣ ���ڿ�

3.  1(w)�� 2�� �ٲܼ�����
   3-1. �� ���ڿ��� ���, �� ���ڿ��� return
   3-2. w�� �ΰ��� �������� ���ڿ� u, v�� �и�
         -> �� u�� ���̻� �и� �Ұ����ؾ��ϸ�, v�� ���ڿ� ����
   3-3. u�� �ùٸ� ���ڿ��� ���, v�� ���ؼ� 1���� �ٽü���
        -> u+v�� ����
   3-4.�ùٸ� ���ڿ��� �ƴѰ��
       -> �� ���ڿ��� ù ��° ���ڷ� (�� ���δ�
       -> v�� ���ؼ� 1�ܰ���� ��������� ������ ����� �̾���δ�.
       -> )�� ���δ�
       -> u�� ù ��°�� ������ ���ڸ� �����ϰ�, ������ ���ڿ��� ��ȣ ������ �����
          �ڿ� ���δ�
       -> ����



*/