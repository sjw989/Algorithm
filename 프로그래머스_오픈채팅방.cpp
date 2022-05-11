#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <map>
using namespace std;

map<string, string> set;
vector<array<string, 2>> msg; // 0 : ��/��   1: id , 2 : �̸�

vector<string> solution(vector<string> record) {
    vector<string> answer;
    for (string rec : record) {
        vector<string> data; // �� record�� ������ ���ͷ� ��ȯ

        stringstream ss(rec); // ������ �������� ���ڿ� �ڸ���
        string str = "";
        while (ss >> str) {
            data.push_back(str);
        } // ������� ���ڿ� �ڸ��� end

        if (data[0] == "Enter") {
            array<string, 2> m;
            m[0] = data[0]; // ��,�� ����
            m[1] = data[1]; // id
            msg.push_back(m); // ���ο� ���� �߰�
            set[m[1]] = data[2]; // <id,�г���>���� ��Ī
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
        str += "���� ";
        if (msg[i][0] == "Enter") {
            str += "���Խ��ϴ�.";
        }
        else if (msg[i][0] == "Leave") {
            str += "�������ϴ�.";
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