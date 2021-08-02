#include <iostream>
#include <array>
#include <vector>
using namespace std;

int C;
int n;
long long cnt;
array<int, 101> dp;
vector<int> result;

long long solve(int n) {
    if (dp[n] == 0) {
        dp[n] = solve(n - 1) % 1000000007 + solve(n - 2) % 1000000007;
    }
    return dp[n];
}

void ans_print() {
    for (auto ans : result) {
        cout << ans << endl;
    }
}
int main() {
    cin >> C;    
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 0; i < C; i++) {        
        cin >> n;
        cnt = solve(n);        
        result.push_back(cnt % 1000000007);
    }
       ans_print();

}