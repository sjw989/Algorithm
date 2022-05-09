#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#define psi pair<string,int>

using namespace std;

vector<vector<string>> sub_str;
vector<string> str_set;
vector<psi> result;
array<int, 11> arr_course;

void solve(string s) {
    int cnt = 0;    
    for (vector<string> sub_s : sub_str) {
        auto it = find(sub_s.begin(), sub_s.end(), s);
        if (it != sub_s.end()) { // 벡터 내에 존재한다면
            cnt++;
        }
    }
    auto it = find(str_set.begin(), str_set.end(), s);
    if (it == str_set.end()) {
        result.push_back(make_pair(s, cnt));
    }    
}
vector<string> get_substr(string str, int n) {
    vector<string> sub_str;
    for (int i = 0; i < (1 << n); ++i) {
        string s = "";
        for (int j = 0; j < n; ++j)
            if (i & (1 << j))
                s += str[j];
        sub_str.push_back(s);
    }
    return sub_str;
}

void print_substr(vector<string> sub_str) {
    for (string s : sub_str) {
        cout << s << " ";
    }
    cout << endl;
}

vector<string> solution(vector<string> orders, vector<int> course) {    
    vector<string> answer;
    for (string str : orders) {
        vector<string> sub_s = get_substr(str, str.size());        
        for (int i = 0; i < sub_s.size(); i++) {
            sort(sub_s[i].begin(), sub_s[i].end());            
        }
        sort(sub_s.begin(), sub_s.end());
        sub_str.push_back(sub_s);
        print_substr(sub_s);        
    }
    

    for (int n : course) {
        for (vector<string> sub_s : sub_str) {            
            for (int i = 0; i < sub_s.size(); i++) {
                if (n == sub_s[i].size()) {
                    solve(sub_s[i]);
                    auto it = find(str_set.begin(), str_set.end(), sub_s[i]);
                    if (it == str_set.end()) {
                        str_set.push_back(sub_s[i]);
                    }                    
                }
            }
        }
    }
    for (auto ans : result) {
        cout << ans.first << " " << ans.second << endl;
    }
    cout << endl;

    int cnt = 0;
    for (int n : course) {
        for (psi s : result) {
            if (s.first.size() == n) {
                arr_course[n] = max(arr_course[n],s.second);
            }
        }
    }
    for (int n : course) {        
        for (psi s : result) {
            if (s.second == arr_course[n] && s.first.size() == n && s.second >= 2) {
                answer.push_back(s.first);
            }
        }
    }
    sort(answer.begin(), answer.end());

    return answer;
}
 

int main() {
    vector<string> orders = { "XYZ", "XWY", "WXA" };
    vector<int> course = { 2,3,4 };
    vector<string> ans = solution(orders, course);    
    for (auto a : ans) {
        cout << a << " ";
    }
    cout << endl;
}


/*
1. order의 모든 조합 저장
2. for order
        for 


*/
