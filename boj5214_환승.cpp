#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, K, M; // ���� ��, ������Ʃ�갡 �����ϴ� ���� ����, ������Ʃ�� ����
array<vector<int>,100000+1000+1> station; // MAX_N = 100,000 , MAX_M = 1000
array<int, 100000 + 1000 + 1> visit;

int main() {
    cin >> N >> K >> M;
    for (int i = 1; i <= M; i++) {        
        for (int j = 0; j < K; j++) {
            int n;
            cin >> n;
            station[100000 + i].push_back(n);
            station[n].push_back(100000 + i);
        }
    }    
    queue<int> node;
    node.push(1); // ��� ��ġ    
    visit[1] = 1;

    while (!node.empty()) {
        int current = node.front();
        node.pop();
        if (current == N) {
            cout << visit[current] << endl;
            return 0;
        }
        for (int i = 0; i < station[current].size(); i++) {            
            int next = station[current][i];            
            if (next > 100000) {
                node.push(next);
                visit[next] = visit[current];
            }
            else {
                if (visit[next] == 0) {
                    node.push(next);
                    visit[next] = visit[current] + 1;
                }

            }
        }
    }
    cout << -1 << endl;
}