#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#define pii pair<int,int>
#define OFFSET 65536
using namespace std;


bool is_alphabet(char c) {
    // �ҹ��� : 97 ~ 122
    // �빮�� : 65 ~ 90
    if (((int)c >= 97 && (int)c <= 122) ||
        ((int)c >= 65 && (int)c <= 90)) {
        return true; // �ƽ�Ű�ڵ�� ȯ���ؼ� �빮�� or �ҹ����� ���
    }
    return false;
}

vector<pii> get_set(string str) {
    vector<pii> string_set; // ��������
    int n = str.size();
    for (int i = 0; i < n - 1; i++) {
        if (is_alphabet(str[i]) && is_alphabet(str[i + 1])) { // �Ѵ� ���ĺ��ΰ��
            string_set.push_back(make_pair((int)str[i], (int)str[i + 1]));
        }
    }
    return string_set;
}

bool is_same_alphabet(pii str1, pii str2) {
    // a z
    // A Z
    bool first = false;
    if (abs(str1.first - str2.first) == 32 || abs(str1.first - str2.first) == 0) {
        first = true;
    }
    bool second = false;
    if (abs(str1.second - str2.second) == 32 || abs(str1.second - str2.second) == 0) {
        second = true;
    }

    if ( first && second) {
        return true;
    }
    return false;
}

pii get_union_intersect(vector<pii> set1, vector<pii> set2) {
    // aa aa ab cc dd
    // aa ad aa bb cc
    for (int i = 0; i < set1.size(); i++) {
        cout << (char)set1[i].first << (char)set1[i].second <<  " " ;
    }
    cout << endl;
    for (int i = 0; i < set2.size(); i++) {
        cout << (char)set2[i].first << (char)set2[i].second << " ";
    }
    cout << endl;
    int num_of_intersection = 0;
    int num_of_union = 0;    
    for (int i = 0; i < set1.size(); i++) {
        pii sub_str1 = set1[i];
        for (int j = 0; j < set2.size(); j++) {
            pii sub_str2 = set2[j];
            if (set2[j].first != -1 && // ���� ���ڿ��� ã��, ������� ������                
                is_same_alphabet(sub_str1, sub_str2) ) {
                cout << (char)sub_str1.first << (char)sub_str1.second << " ";
                cout << endl;
                cout << (char)sub_str2.first << (char)sub_str2.second << " ";
                cout << endl;
                set2[j].first = -1; // �ߺ������� ���� disable�� -1 ����                
                num_of_intersection++;
                break;
            }
        }
    }    
    num_of_union = set1.size() + set2.size() - num_of_intersection;
    // �������� ���� = ����1 + ����2 - ������    

    cout << num_of_intersection << " " << num_of_union << endl;
    return make_pair(num_of_intersection, num_of_union);
}

int get_jacad(vector<pii> set1, vector<pii> set2) {
    double ans = 0;    
    pii res = get_union_intersect(set1, set2);
    if (res.first == 0 && res.second == 0) {
        return 1*OFFSET;
    }
    //cout << res.first << " " << res.second << endl;
    ans = (double)res.first / (double)res.second;    
    ans *= (double)OFFSET;      
    return (int)ans;
}

int solution(string str1, string str2) {    
    int answer = 0;    
    vector<pii> set1 = get_set(str1);
    vector<pii> set2 = get_set(str2);
   
    answer = get_jacad(set1, set2);
    return answer;
}

int main() {
    // HG GN NH HU
    // CR RS SH HV
    string str1 = "HGNHU";    
    string str2 = "CRSHV";
    int ans = solution(str1, str2);        
   
    cout << ans;        
}