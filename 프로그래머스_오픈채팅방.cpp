#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <map>
using namespace std;

map<string, string> set;
vector<array<string, 2>> msg; // 0 : 출/입   1: id , 2 : 이름

vector<string> solution(vector<string> record) {
    vector<string> answer;
    for (string rec : record) {
        vector<string> data; // 각 record의 정보를 벡터로 변환

        stringstream ss(rec); // 공백을 기준으로 문자열 자르기
        string str = "";
        while (ss >> str) {
            data.push_back(str);
        } // 공백기준 문자열 자르기 end

        if (data[0] == "Enter") {
            array<string, 2> m;
            m[0] = data[0]; // 출,입 정보
            m[1] = data[1]; // id
            msg.push_back(m); // 새로운 입장 추가
            set[m[1]] = data[2]; // <id,닉네임>으로 매칭
            cout << set[m[1]] << endl;
        }
        else if (data[0] == "Leave") {
            array<string, 2> m;
            m[0] = data[0];
            m[1] = data[1];
            msg.push_back(m);
        }
        else if (data[0] == "Change") {
            set[data[1]] = data[2];
        }
    }
    for (int i = 0; i < msg.size(); i++) {
        array<string,2> cur_msg = msg[i];
        string str = "";
        str += set[cur_msg[1]];
        str += "님이 ";
        if (msg[i][0] == "Enter") {
            str += "들어왔습니다.";
        }
        else if (msg[i][0] == "Leave") {
            str += "나갔습니다.";
        }
        answer.push_back(str);
    }
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << endl;
    }
    return answer;
}

int main() {
    vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo",
                "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan" };
    solution(record);

    
}