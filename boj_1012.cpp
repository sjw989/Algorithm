#include <iostream>
#include <array>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;

int T; // tc ��
int M, N, K; // ����,����, ���߰���
int cnt;
array<array<int, 50>, 50> board;
array<array<int, 50>, 50> visit;
vector<int> result;

void init() {
    cnt = 0;
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            board[i][j] = 0;
            visit[i][j] = 0;
        }
    }
}

void input() {
    cin >> M >> N >> K;
    init();
    for (int i = 0; i < K; i++) {
        int c, r;
        cin >> c >> r;
        board[N - 1 - r][c] = 1; // ���� �־��ֱ�
    }    
}

void bfs(int row, int col) {
    queue<pii> q;
    q.push(make_pair(row, col)); // ���� ��ġ
    visit[row][col] = 1; //���� ��ġ �湮ó��

    while (!q.empty()) {
        pii s = q.front();
        q.pop();        
        if (s.first + 1 < N) { // �Ʒ��� Ž��
            if (board[s.first + 1][s.second] == 1 && visit[s.first + 1][s.second] == 0) {
                q.push(make_pair(s.first + 1, s.second));
                visit[s.first + 1][s.second] = 1;
            }
        }

        if (s.first - 1 >= 0) { // ���� Ž��
            if (board[s.first - 1][s.second] == 1 && visit[s.first - 1][s.second] == 0) {
                q.push(make_pair(s.first - 1, s.second));
                visit[s.first - 1][s.second] = 1;
            }
        }

        if (s.second + 1 < M) { // ������ Ž��
            if (board[s.first][s.second + 1] == 1 && visit[s.first][s.second + 1] == 0) {
                q.push(make_pair(s.first, s.second + 1));
                visit[s.first][s.second + 1] = 1;
            }
        }

        if (s.second - 1 >= 0) { // ���� Ž��
            if (board[s.first][s.second - 1] == 1 && visit[s.first][s.second - 1] == 0) {
                q.push(make_pair(s.first, s.second - 1));
                visit[s.first][s.second - 1] = 1;
            }
        }

    }    
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 1 && visit[i][j] == 0) {                
                bfs(i, j);
                cnt++;
            }
        }
    }
}

void print() {
    for (int ans : result) {
        cout << ans << "\n";
    }
}

int main() {    
    cin >> T;
    for (int i = 0; i < T; i++) {
        input();
        solve();
        result.push_back(cnt);        
    }
    print();
}

