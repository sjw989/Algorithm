#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


typedef struct Row{
    int key; // 초기 번호
    Row* prev; // 이전 행
    Row* next; // 다음 행
};
Row* head; // 제일 앞
Row* tail; // 제일 끝
Row* cur; // 현재 행
stack<Row*> garbage; // 삭제된 행


string getSolution(int n) {
    vector<int> num;
    Row* cur = head;
    while (!cur->next == NULL) {
        num.push_back(cur->key);
        cur = cur->next;
    }
    num.push_back(cur->key);

    string str = "";
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (num[idx] == i) {
            str += 'O';
            idx++;
        }
        else {
            str += 'X';
        }
    
    }
    return str;

}

void solve(char c, int cnt) {
    switch (c) {
        case 'U': {
            for (int i = 0; i < cnt; i++) {
                cur = cur->prev;
            }
            break;
        }
        case 'C': { // 삭제하고 아래 행을 선택, tail이면 그 prev를 선택
            garbage.push(cur); // 현재 행을 스택에 쌓음
            if (cur == tail) { // 현재 행이 가장 아래행인 경우
                cur->prev->next = NULL; // 이전 행의 next 없애줌
                tail = cur->prev; // tail 업데이트
                cur = tail;
            }
            else if (cur == head){ // 현재 행이 가장 위인경우
                cur->next->prev = NULL;
                head = cur->next;
                cur = head;
            }
            else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                cur = cur->next;
            }
            break;
        }
        case 'D': {
            for (int i = 0; i < cnt; i++) {
                if (cur->next != NULL) {
                    cur = cur->next;
                }
            }
            break;

        }
        case 'Z': {
            Row* recovery = garbage.top();
            garbage.pop();

            if (recovery->prev == NULL) { // head가 삭제된 경우
                head->prev = recovery;
                head = recovery;
            }
            else if (recovery->next == NULL) { // tail이 삭제된 경우
                tail->next = recovery;
                tail = recovery;
            }
            else { // 나머지 경우
                recovery->prev->next = recovery;
                recovery->next->prev = recovery;
            }
            break;
        }

    }
}

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    for (int i = 0; i < n; i++) {
        Row* r = new Row();
        r->key = i;
        if (i == 0) {
            head = r;
            tail = r;
        }
        else {
            tail->next = r;
            r->prev = tail;
            tail = r;
        }
        if (i == k) {
            cur = r;
        }
    }
    for (int i = 0; i < cmd.size(); i++) { // 명령어 개수만큼 반복
        string cur_cmd = cmd[i];
        char c = cur_cmd[0];
        int cnt = 0;
        for (int j = 2; j < cur_cmd.size(); j++) {
            cnt = (cnt * 10) + (cur_cmd[j] - '0');
        }
        solve(c, cnt);
    }


    answer = getSolution(n);
    return answer;
}
int main() {
    int n = 8; // 처음 행의 개수
    int k = 2; // 처음 선택된 행
    vector<string> cmd = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C" };

    string ans = solution(n, k, cmd);
    cout << ans;
}
/*
U X - 현재 행에서 X만큼 위에있는 행 선택
D X - 현재 행에서 X 만큼 아래에있는 행 선택
C - 현재 행을 삭제, 바로 아래행을 선택
    -> 가장 마지막 행인 경우 바로 윗행을 선택
Z - 가장 최근에 삭제된 행을 복구, 현재 선택된 행은 변하지않음



*/
