#include <iostream>
#include <vector>
using namespace std;

int C; // tc ����
vector<int> height;
vector<int> result;

void input() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int h;
		cin >> h;
		height.push_back(h);
	}
}

int solve(int start, int end) {		
	int left = 0, right = 0, mid = 0;
	if (start == end) {
		return height[start];
	}
	else {				
		left = solve(start, (start + end) / 2);
		right = solve((start + end) / 2 + 1, end);

		int l = (start + end) / 2, r = (start + end) / 2 + 1 ;
		mid = min(height[l], height[r]) * 2;
		int h = min(height[l], height[r]);
		
		while (start < l || r < end) {
			if (start < l && r < end ) { // ���� ���� ����
				if ( height[l - 1] <= height[r + 1] ){ // ���������� ���� ���
					r++;
					h = min(h, height[r]);
					mid = max(mid, h * (r - l + 1));
				}
				else { // �������� ���� ���
					l--;
					h = min(h, height[l]);
					mid = max(mid, h * (r - l + 1));
				}
			}
			else {
				if (start < l) { // �������θ� �� �� �ִ� ���
					l--;
					h = min(h, height[l]);
					mid = max(mid, h * (r - l + 1));
				}
				else { // ���������θ� �� �� �ִ� ���
					r++;
					h = min(h, height[r]);
					mid = max(mid, h * (r - l + 1));
				}
			}
		}		
		return max(mid, max(left, right));
	}	
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
		int ans = solve(0, height.size() - 1);				
		height.clear();
		result.push_back(ans);		
	}
	print();	
}