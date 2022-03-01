#include <iostream>
#include <string>
#include <vector>
#define pii pair<int,int>
using namespace std;


vector<vector<int>> rotate(vector<vector<int>> key){    
    int n[20][20];
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < key.size(); j++) {
            n[i][j] = key[key.size() - j - 1][i];
        }
    }
    vector<vector<int>> new_key;    
    for (int i = 0; i < key.size(); i++) {
        vector<int> k;
        for (int j = 0; j < key.size(); j++) {
            k.push_back(n[i][j]);
        }
        new_key.push_back(k);        
    }
    for (int i = 0; i < key.size(); i++) {      
        for (int j = 0; j < key.size(); j++) {
            cout << new_key[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return new_key;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    vector<pii> lock_point;
    for (int i = 0; i < lock.size(); i++) {
        for (int j = 0; j < lock.size(); j++) {
            if (lock[i][j] == 0) {
                lock_point.push_back(make_pair(i, j));
            }
        }
    }
    if (lock_point.size() == 0) {
        answer = true;
        return answer;
    }
    for (int r = 0; r < 4; r++) {
        key = rotate(key);        
        vector<pii> key_point;             
        for (int i = 0; i < key.size(); i++) {
            for (int j = 0; j < key.size(); j++) {
                if (key[i][j] == 1) {
                    key_point.push_back(make_pair(i, j));
                }                
            }
        }
        for (pii kp : key_point) {
            for (pii lp : lock_point) {
                int dr = lp.first - kp.first;
                int dc = lp.second - kp.second;
                vector<pii> test_point;
                for (int i = 0; i < key_point.size(); i++) {
                    test_point.push_back(make_pair(key_point[i].first + dr, key_point[i].second + dc));
                }
                int cnt = 0;
                int no = 0;
                for (int i = 0; i < test_point.size(); i++) {
                    pii tp = test_point[i];                 
                    if (tp.first >= 0 && tp.first < lock.size() && tp.second >= 0 && tp.second < lock.size()) {
                        if (lock[tp.first][tp.second] == 0) {
                            cnt++; // 열쇠의 돌기와 자물쇠의 홈의 개수
                        }
                        else { // 열쇠의 돌기와 자물쇠의 돌기가 만난 개수
                            no++;
                        }
                    }
                }    
                if (cnt >= lock_point.size() && no == 0) {
                    answer = true;
                    return answer;;
                }                
            }
        }
    }        
    cout << answer << endl;
    return answer;
}


int main() {
    vector<vector<int>> lock = { {1,1,1},{1,1,0},{1,0,1} };
    vector<vector<int>> key = { {0,0,0},{1,0,0},{0,1,1} };
    solution(key, lock);    
}