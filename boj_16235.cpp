#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

typedef struct Tree {
	int age;
	bool dead;
	Tree( int a, bool d) {
		age = a;
		dead = d;
	}
};
int N, M, K; // N x N, M : 묘목의 개수, K년이 지난 후
array<array<int, 11>, 11> board; // 각 칸의 양분을 표시
array<array<int, 11>, 11> power; // 로봇이 뿌릴 각 칸의 양분
array<array<vector<Tree>, 11>, 11> trees; // (i,j)에 있는 tree 정보
array<pii, 8 > delta = { make_pair(-1, -1 ), make_pair(-1, 0 ), make_pair( -1, +1 ),make_pair( 0,-1 ),
						make_pair( 0,+1 ), make_pair( +1,-1 ), make_pair( +1,0 ), make_pair( +1,+1 ) };

void input() {
	//ifstream in("test.txt");
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> power[i][j];
			board[i][j] = 5; // 초기양분 5
		}
	}
	for (int i = 0; i < M; i++) {
		int x, y, a;
		cin >> x >> y >> a;
		trees[x][y].push_back(Tree(a, false));
	}
}

bool cmp(Tree a, Tree b) {
	return a.age > b.age;
}
void solve() {
	int year = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sort(trees[i][j].begin(), trees[i][j].end(), cmp);
		}
	} // 처음에 나이 내림차순으로 정렬

	array<array<vector<Tree>, 11>, 11> new_trees;
	array<array<vector<Tree>, 11>, 11> spread;
	while (year < K) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				spread[i][j].clear();
				new_trees[i][j].clear();
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (trees[i][j].size() == 0) { continue; } // 나무가 없는 칸은 건너뜀
				vector<Tree>& cur_trees = trees[i][j];
				for (int t = cur_trees.size() - 1; t >= 0; t--) { // 봄
					if (board[i][j] >= cur_trees[t].age) {
						board[i][j] -= cur_trees[t].age;
						cur_trees[t].age++;
					}
					else {
						cur_trees[t].dead = true;
					}
				}
				// 여름 + 가을

				for (Tree t : cur_trees) {
					if (t.dead) { // 여름 :  나무가 죽어으면
						board[i][j] += t.age / 2;
					}
					else { // 가을 : 죽지않은 나무 번식
						new_trees[i][j].push_back(t);
						if (t.age % 5 == 0) {
							for (int d = 0; d < 8; d++) {
								int nr = i + delta[d].first;
								int nc = j + delta[d].second;
								if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
									spread[nr][nc].push_back(Tree(1, false));
								}
							}
						}
					}
				}
			}
		}
		for (int i = 1; i <= N; i++) { // 겨울
			for (int j = 1; j <= N; j++) {
				board[i][j] += power[i][j];
				if (spread[i][j].size() != 0) {
					for (Tree t : spread[i][j]) {
						new_trees[i][j].push_back(t);
					}
				}

			}
		}
	
		trees = new_trees;
		year++;
	}
}

void print() {
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ans += trees[i][j].size();
		}
	}
	cout << ans;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	solve();
	print();
	
}