#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

map<string, vector<int>> m;
vector<string> can_query;
       
void make_all_query(vector<string> info) {  
    //"java backend junior pizza 150"
    // 이 하나의 info로 만들 수 있는 모든 query에 150을 넣어줌
    string information[4][2] = { {"-"},{"-"} ,{"-"} ,{"-"} };    
    for (int i = 0; i < info.size(); i++) {
        string cur_info = info[i];
        stringstream ss;
        int score = 0;
        ss.str(cur_info);
        ss >> information[0][1] >> information[1][1] >> information[2][1] >> information[3][1];
        ss >> score;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                for (int c = 0; c < 2; c++) {
                    for (int d = 0; d < 2; d++) {
                        string str = information[0][a] + information[1][b]+ information[2][c]+ information[3][d];
                        m[str].push_back(score);
                        can_query.push_back(str);
                        //sort(m[str].begin(), m[str].end());
                    }
                }
            }
        }            
    }            
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;        
    make_all_query(info); // 입력 info를 <condition, point> 로 mapping
    for (auto itr = m.begin(); itr != m.end(); itr++) {
        sort(itr->second.begin(), itr->second.end());
    }
    // 정렬을 하고 들어가야되는데
    /*
    for (int i = 0; i < can_query.size(); i++) {
        sort(m[can_query[i]].begin(), m[can_query[i]].end());
    }*/

    for (int i = 0; i < query.size(); i++) { // 쿼리 개수만큼 반복
        stringstream ss;        
        ss.str(query[i]);        
        string cond = "";
        string s[8];
        ss >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5] >> s[6] >> s[7];        
        cond = s[0] + s[2] + s[4] + s[6];
        vector<int> candidate = m[cond];        
        if (candidate.size() == 0) {
            answer.push_back(0);
        }
        else {                         
            //sort(candidate.begin(), candidate.end());
            int cnt = candidate.end() - lower_bound(candidate.begin(), candidate.end(), stoi(s[7]));
            answer.push_back(cnt);            
        }                        
    }      
    return answer;
}

int main() {
    vector<string> info = {"java backend junior pizza 150", "python frontend senior chicken 210", "python frontend senior chicken 150", "cpp backend senior pizza 260", "java backend junior chicken 80", "python backend senior chicken 50"};
    vector<string> query ={"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"} ;
    solution(info, query);
}