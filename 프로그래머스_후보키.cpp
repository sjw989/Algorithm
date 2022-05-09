#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> ans;
int answer;
void dfs(int idx, vector<int> col, vector<vector<string>> relation) {
    for (int i = idx; i < relation[0].size(); i++) {
        col.push_back(i);
        vector<vector<string>> s;
        for (int j = 0; j < relation.size(); j++) {
            vector<string> row;
            for (int c : col) {                
                row.push_back(relation[j][c]);
            }
            s.push_back(row);
        }
        sort(s.begin(), s.end());
        int n = unique(s.begin(), s.end()) - s.begin();
        if (n == relation.size()) {            
            ans.push_back(col);
        }
        else {
            dfs(i + 1, col, relation);
        }
        col.pop_back();
    }    
} 

bool cmp(vector<int> a, vector<int> b) {
    return a.size() < b.size();
}

void get_result() {
    vector<bool> can_use;    
    for (int i = 0; i < ans.size(); i++) {
        can_use.push_back(true);
    }        
    sort(ans.begin(), ans.end(), cmp);
   
    for (int i = 0; i < ans.size(); i++) {        
        if (can_use[i]) {
            vector<int> pivot = ans[i];                  
            for (int j = i+1; j < ans.size(); j++) {
                vector<int> sub_pivot = ans[j];                
                if (pivot != sub_pivot) {
                    int cnt = 0;
                    for (int p = 0; p < pivot.size(); p++) {
                        for (int q = 0; q < sub_pivot.size(); q++) {
                            if (pivot[p] == sub_pivot[q]) {
                                cnt++;
                            }
                        }
                    }
                    if (pivot.size() == cnt) {                        
                        can_use[j] = false;
                    }
                }
            }
        }                   
    }
    for (bool b : can_use) {
        if (b) { answer++; }
    }

}
int solution(vector<vector<string>> relation) {            
    vector<int> col;
    dfs(0, col,relation);
    get_result();
    return answer;
}

int main() {    
    vector<vector<string>> relation = { {"a","1","aaa","c","ng"},
        {"b","1","bbb","c","g"},
        {"d","2","bbb","d","ng"} ,
        {"c","1","aaa","d","ng"} };      
    solution(relation);
}
