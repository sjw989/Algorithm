#include <iostream>
#include <fstream>
#include <array>
using namespace std;

string str1, str2; // input string
array<array<int, 1001>,1001> dp;

void input() {
	ifstream in("test.txt");
	in >> str1 >> str2;
}

void solve() {	
	for (int i = 1; i <= str1.size(); i++) {
		for (int j = 1; j <= str2.size(); j++) {
			if (str1[i - 1] == str2[j - 1]) {	
				if (!dp[i][j]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}				
			}
			else {
				dp[i][j] = max(dp[i - 1][j - 1], max(dp[i][j - 1], dp[i - 1][j]));
			}
		}
	}

}

void print() {		
	cout << dp[str1.size()][str2.size()];
}

int main() {
	input();	
	solve();
	print();
}


