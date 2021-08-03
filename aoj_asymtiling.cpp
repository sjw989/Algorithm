#include <iostream>
#include <array>
#include <vector>
using namespace std;

int C;
int n;
array<int, 101> dp;
array<int, 101> asym_dp;
vector<int> result;

void print() {
    for (auto ans : result) {
        cout << ans << "\n";
    }
}

long long solve(int n) {
    if (n == 1 || n == 2) {
        return dp[n];
    }
    if (dp[n] == 0) {
        dp[n] = solve(n - 1) % 1000000007 + solve(n - 2) % 1000000007;
    }
    return dp[n];
}

long long solve2(int n) {
    if (n == 1 || n == 2) {
        return asym_dp[n];
    }
    if (asym_dp[n] == 0) {
        if (n % 2 == 0) {
            asym_dp[n] = solve2(n - 1) % 1000000007 + solve2(n - 2) % 1000000007;
        }
        else {
            asym_dp[n] = solve2(n - 1) % 1000000007 - solve2(n - 2) % 1000000007;
        }
    }
    return asym_dp[n];
}

int main() {
    cin >> C;
    dp[1] = 1;
    dp[2] = 2;
    asym_dp[1] = 1;
    asym_dp[2] = 2;
    for (int i = 0; i < C; i++) {
        cin >> n;
        long long res = solve(n);
        long long asym_res = solve2(n);
        result.push_back((res + 1000000007 - asym_res)  % 1000000007);
    }
    print();
}