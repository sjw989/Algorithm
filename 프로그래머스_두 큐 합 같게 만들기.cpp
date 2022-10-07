#include <iostream>
#include <string>
#include <vector>
#define ll long long
using namespace std;


vector<ll> cumulative;
ll target = 0;

void getCumulativeVector(vector<int> queue1, vector<int> queue2) {
    
    cumulative.push_back(0);

    for(int i : queue1){
        if(cumulative.size() == 0) {
            cumulative.push_back(i);
        }
        else {
            cumulative.push_back(cumulative.back() + i);
        }
    }

    for(int i : queue2) {
        cumulative.push_back(cumulative.back() + i);
    }
}

ll getTarget() {
    if(cumulative.back() % 2 == 1) {
        return -1;
    }
    return cumulative.back() / 2;
}

int solution(vector<int> queue1, vector<int> queue2) {

    getCumulativeVector(queue1, queue2);
    
    ll target = getTarget();
    
    if(target == -1 ) {
        return -1;
    }


    int answer = -2;
    
    int left = 1;
    int right = queue1.size();
    int cnt = 0;
    
    while(left <= right) {

        ll value = cumulative[right] - cumulative[left - 1];

        if(value == target) {
            answer = cnt;
            break;
        }
        if(value > target) { // left 증가
            left++;
        }
        else if(value < target) { // right 증가
            if(right == cumulative.size() - 1) {
                break;
            }
            right++;
        }
        cnt++;
    
    }

    if(answer == -2) {
        answer =  -1;
    }
    cout << answer << endl;
    return answer;
}



int main() {
    //vector<int> queue1 = {3,2,7,2};
    vector<int> queue1;
    vector<int> queue2;
    for(int i = 0 ; i< 300000; i++){
        queue1.push_back(4);
        queue2.push_back(2);
    }
    //vector<int> queue2 = {4,6,5,1};
    solution(queue1,queue2);
}