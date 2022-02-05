#include <iostream>
#include <string>
#include <vector>
using namespace std;

int gap;
vector<int> lion_ans;

void get_answer(vector<int> info, vector<int> lion) {
/*
    vector<int> v = { 1,1,1,1,1,1,1,1,0,0,2 };
    if (lion == v) {
        cout << 123 << endl;
    }*/
    int score_appeach = 0;
    int score_lion = 0;
    for (int i = 0; i < info.size(); i++) {
        if (info[i] == 0 && lion[i] == 0) { // �Ѵ� �ϳ��� ������ ���
            continue; // �ƹ��� ���� �� ������
        }
        if (info[i] >= lion[i]) { // ����ġ�� �� ���� ���� ���
            score_appeach += (10 - i); // k�� ��������
        }
        else { // ���̾��� �� ���� ���� ���
            score_lion += (10 - i); // k�� ��������
        }
    }
    if (score_appeach < score_lion) { // ���̾��� �������� ���� ���
        int cur_gap = score_lion - score_appeach; // �������̸� ���ϰ�
        if (gap == 0) { // ������ ���� ���̰� ���� �� ������
            lion_ans = lion;
            gap = cur_gap;
        }
        else if (cur_gap > gap) { // ������ ���������� ū���  
            gap = cur_gap; // ���� �� ����
            lion_ans = lion;
        }
        else if (cur_gap == gap) { // ������ ���� ���� ���� ���
            for (int i = 10; i >= 0; i--) { // ���峷�� ������ ������� Ž��
                if (lion_ans[i] < lion[i]) { // ���ο� ������ �������� ������ ������
                    lion_ans = lion; // vector ������Ʈ
                    break;
                }
                else if (lion_ans[i] > lion[i]) { // ������ �������� ������ ������
                    break;
                }
                // ������ ����ؼ� for�� Ž��
            }
        }
    }
}

void dfs(vector<int> info, vector<int> lion, int k, int p) {
    // ����ġ ����, ���̾� ����, ���� ȭ��, �� ��° ���� ī��������
    if (k == 0 || p == 10) { 
        // ���� ȭ���� ���ų�, 0���� �� �־�� �Ǵ� ���
        lion[p] = k;
        get_answer(info, lion);
    }
    else { // ���� ȭ���� �ִ� ���
        for (int i = 0; i <= k; i++) { // p��° ������ ȭ�� i�� ����
            lion[p] = i;
            dfs(info, lion, k - i, p + 1);
        }
    }
}


vector<int> solution(int n, vector<int> info) {
    vector<int> answer;
    vector<int> lion = { 0,0,0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i <= n; i++) {
        lion[0] = i; // lion�� 10��¥�� ��������� �������� for�� ����
        dfs(info, lion, n - i, 1); // �׻� 9��¥������ (n-i)�� ���� dfs �����
    }
    if (lion_ans.size() == 0) {
        answer.push_back(-1);
    }
    else {
        answer = lion_ans;
    }
    return answer;
}

int main() {
    int n = 10;
    vector<int> info = { 0,0,0,0,0,0,0,0,3,4,3 };
    vector<int> ans = solution(n, info);
    for (auto a : ans) {
        cout << a << " ";
    }
    cout << endl;


}