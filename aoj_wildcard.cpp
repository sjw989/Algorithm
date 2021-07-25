#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int C; // tc 개수
int N; // 파일명의 수
string wildcard;
string file;
vector<string> file_name;
vector<string> result;

void input() {		
	cin >> wildcard >> N;
	file_name.clear();
	result.clear();
	for (int i = 0; i < N; i++) {
		string name;
		cin >> name;
		file_name.push_back(name);
	}	
}



int solve(int idx_f, int idx_w) {		
	while (idx_f < file.size() || idx_w < wildcard.size()) {
		if (file[idx_f] == wildcard[idx_w] || wildcard[idx_w] == '?') {
			idx_f++, idx_w++;
		}				
		else {
			break;
		}
	}

	if (idx_f == file.size() && idx_w == wildcard.size()) {
		return 1;
	}
	else {
		if (wildcard[idx_w] == '*') {
			for (int i = 0; i + idx_f <= file.size(); i++) {				
				int res = solve(idx_f + i, idx_w + 1);
				if (res == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
	
}

void print() {
	for (auto ans : result) {
		cout << ans << "\n";
	}
}

int main() {	
	cin >> C;
	for (int i = 0; i < C; i++) {		
		input();
		for(auto str : file_name){			
			file = str;			
			if (solve(0, 0) == 1) {
				result.push_back(file);
			}						
		}		
		sort(result.begin(), result.end());
		print();
	}	
	
}