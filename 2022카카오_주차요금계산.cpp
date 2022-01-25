#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {    
    vector<int> answer;
    vector<vector<int>> record;
    record.resize(10000);    

    for (int i = 0; i < records.size(); i++) {
        string s = records[i];
        int h = (s[0] - '0') * 10 + (s[1] - '0');
        int m = (s[3] - '0') * 10 + (s[4] - '0');        
        int n = 0;
        for (int j = 6; j <= 9; j++) {            
            n = n * 10 + (s[j] - '0');            
        }        

        record[n].push_back(h * 60 + m);
    }    
    for (int i = 0; i < record.size(); i++) {
        vector<int> info = record[i];
        if (info.size() == 0) {
            continue;
        }
        int sum_time = 0;
        if (info.size() % 2 != 0) {            
            info.push_back(23 * 60 + 59);            
        }
        for (int j = 0; j < info.size() ; j += 2) {
            sum_time += info[j + 1] - info[j];
        }

        int fee = 0;
        if (sum_time <= fees[0]) {
            fee = fees[1];
        }
        else {
            sum_time -= fees[0];
            fee += fees[1];
            if (sum_time % fees[2] == 0) {
                fee += (sum_time / fees[2]) * fees[3];
            }
            else {
                fee += (sum_time / fees[2] + 1) * fees[3];
            }
        }
        answer.push_back(fee);
    }

    return answer;
}

int main() {
    vector<int> fees = { 180, 5000, 10, 600 };
    vector<string> records = { "05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT", "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN", "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT" };
    solution(fees, records);
}