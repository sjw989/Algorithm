#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int pointList[7] = {3,2,1,0,1,2,3};
map<char,int> pointInfo;

/*
1번 : R T
    2번 : C F
    3번 : J M
    4번 : A N
*/


char getTypeByPoint(string arg) {
    if (pointInfo[arg[0]] > pointInfo[arg[1]]) {
        return arg[0];
    }
    else {
        if(pointInfo[arg[0]] == pointInfo[arg[1]]) {
            sort(arg.begin(), arg.end());
            return arg[0];
        }
        else {
            return arg[1];
        }
    }
}

string makeAsner() {
    string ans = "";
    vector<string> typeList = { "RT", "CF", "JM", "AN"};
    for(string type : typeList) {
        ans += getTypeByPoint(type);
    } 
    return ans;
}

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    
    for(int i = 0 ; i < survey.size(); i++) {
        int ch = choices[i];
        string sv = survey[i];
        int pt = pointList[ch-1]; // 획득한 점수
        if(ch > 4 ) { // 뒤에 유형
            pointInfo[sv[1]] += pt;
        }
        else if (ch < 4) { // 앞에 유형
            pointInfo[sv[0]] += pt;
        }
    }

    answer = makeAsner();
    cout << answer << endl;
    return answer;
}


int main () {
    vector<string> survey = {"AN", "CF", "MJ", "RT", "NA"};
    vector<int> choices = {5,3,2,7,5};
    solution(survey, choices);
}

/*
1. 총 4개의 지표
2. 각 지표당 2개의 성격 유형이 있음
    1번 : R T
    2번 : C F
    3번 : J M
    4번 : A N
--> 4개의 지표 이므로 총 16개의 성격유형이 가능

3. 검사지에는 총 n개의 질문이 있고, 각 질문에는 7개의 선택지가 있다. 
매우 비동의  --------- 매우 동의
3   2   1  0   1  2  3

4. 순서는 상관없으나, 각 선택지마다 고정적인 점수가 있음
5. 더 높은 점수를 얻는 것이 해당 질문에서 자신의 성격 유형
6. 하나의 지표에서 점수가 같으면 사전 순
7. survey : 질문마다 판단하는 지표를 담은 1차원 문자열 배열
   choices : 각 질문마다 선택한 선택지 : n개
*/