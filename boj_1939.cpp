#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

int N, M; // 섬의 개수, 다리의 개수
int fac1, fac2; // 공장을 가지고있는 섬의 번호
int ans;
int max_weight;
array<int, 100001> visit; // 방문여부	           
array<vector<pii>, 100001> island; // i번째 섬이 가지고있는 다리들의 정보


void input() {
	//ifstream in("test.txt");
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		island[a].push_back(make_pair(b, c)); // 연결된 섬 번호 + 중량
		island[b].push_back(make_pair(a, c)); // 양방향 연결
		max_weight = max(max_weight, c);
	}
	cin >> fac1 >> fac2;
}

bool bfs(int high_weight) {	
	for (int i = 1; i < 100001; i++) {
		visit[i] = 0;
	}

	queue<int> q;
	q.push(fac1);	// 공장1에서 시작 
	visit[fac1] = 1;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		vector<pii> cur_island = island[cur]; // 현재 섬에 연결되어있는 다리 정보
		for (int i = 0; i < cur_island.size(); i++) {
			pii next_island = cur_island[i]; // 다음 섬에 대한 정보
			if (next_island.second >= high_weight && visit[next_island.first] == 0) { 
				// 무게제한을 통과하면
				
				if (next_island.first == fac2) { // 다음 섬이 2번공장이면
					return true;
				}
				q.push(next_island.first);
				visit[next_island.first] = 1;
			}
		}
	}
	return false; // bfs로 2번 공장을 가지못하면 false 리턴
}

void solve() {
	int lower = 1; // 가능한 중량 최소값
	int upper = max_weight; // 가능한 중량 최대값

	while (lower <= upper) {
		int mid = (lower + upper) / 2; // 내가 찾을 무게
		//cout << mid << " " << lower << " " << upper << endl;
		if (bfs(mid)) { // 2번 공장을 찾을 수 있으면						
			lower = mid + 1; // 현재 무게로 2번공장을 찾을 수 있으면 lower를 증가시켜 최대값 찾기
		}
		else { // 2번 공장을 찾을 수 없으면
			upper = mid - 1 ; // 현재 무게로 2번 공장 찾을 수 없으면 upper를 감소시키기
		}
	}

	ans = upper;
}

void print() {
	cout << ans;
}

int main() {
	input();
	solve();
	print();
}