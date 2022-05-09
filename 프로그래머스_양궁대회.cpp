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
        if (info[i] == 0 && lion[i] == 0) { // 둘다 하나도 못맞춘 경우
            continue; // 아무도 점수 안 가져감
        }
        if (info[i] >= lion[i]) { // 어피치가 더 많이 맞춘 경우
            score_appeach += (10 - i); // k점 가져가기
        }
        else { // 라이언이 더 많이 맞춘 경우
            score_lion += (10 - i); // k점 가져가기
        }
    }
    if (score_appeach < score_lion) { // 라이언이 최종점수 높은 경우
        int cur_gap = score_lion - score_appeach; // 점수차이를 구하고
        if (gap == 0) { // 이전에 점수 차이가 계산된 적 없으면
            lion_ans = lion;
            gap = cur_gap;
        }
        else if (cur_gap > gap) { // 기존의 점수차보다 큰경우  
            gap = cur_gap; // 점수 차 저장
            lion_ans = lion;
        }
        else if (cur_gap == gap) { // 기존의 점수 차와 같은 경우
            for (int i = 10; i >= 0; i--) { // 가장낮은 점수의 과녁부터 탐색
                if (lion_ans[i] < lion[i]) { // 새로운 점수의 낮은점수 과녁이 많으면
                    lion_ans = lion; // vector 업데이트
                    break;
                }
                else if (lion_ans[i] > lion[i]) { // 기존의 낮은점수 과녁이 많으면
                    break;
                }
                // 같으면 계속해서 for문 탐색
            }
        }
    }
}

void dfs(vector<int> info, vector<int> lion, int k, int p) {
    // 어피치 정보, 라이언 정보, 남은 화살, 몇 번째 과녁 카운팅인지
    if (k == 0 || p == 10) { 
        // 남은 화살이 없거나, 0점에 다 넣어야 되는 경우
        lion[p] = k;
        get_answer(info, lion);
    }
    else { // 남은 화살이 있는 경우
        for (int i = 0; i <= k; i++) { // p번째 점수에 화살 i개 적중
            lion[p] = i;
            dfs(info, lion, k - i, p + 1);
        }
    }
}


vector<int> solution(int n, vector<int> info) {
    vector<int> answer;
    vector<int> lion = { 0,0,0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i <= n; i++) {
        lion[0] = i; // lion의 10점짜리 몇발인지를 기준으로 for문 돌림
        dfs(info, lion, n - i, 1); // 항상 9점짜리부터 (n-i)발 남은 dfs 돌면됨
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
