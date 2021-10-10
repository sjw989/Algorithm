#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;


int N, M; // �迭 ������ NxN, �̵���� M��
array<array<int, 51>, 51> board; // board[i][j] = ���� ���� ��
array<int, 9> drow = { 0,0,-1,-1,-1,0,1,1,1 };
array<int, 9> dcol = { 0,-1,-1,0,1,1,1,0,-1 };
array<int, 4> diagonal_drow = { -1,-1,+1,+1 };
array<int, 4> diagonal_dcol = { -1,+1,-1,+1 };
vector<pii> moving;
queue<pii> cloud_position;

void input() {
    //ifstream in("1.inp");
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        int d, s; // ���� d, �Ÿ� s
        cin >> d >> s;
        moving.push_back(make_pair(d, s));
    }
}

void get_init_cloud_position() {
    cloud_position.push(make_pair(N, 1));
    cloud_position.push(make_pair(N, 2));
    cloud_position.push(make_pair(N - 1, 1));
    cloud_position.push(make_pair(N - 1, 2));
}

vector<pii> move_cloud(pii mv) {
    vector<pii> moved_cloud;
    while (!cloud_position.empty()) { // �� ������ �̵����Ѿ���
        pii cur_cloud = cloud_position.front(); // �̵���ų ���� ����
        cloud_position.pop();
        int next_row = cur_cloud.first, next_col = cur_cloud.second;
        for (int i = 0; i < mv.second; i++) {
            next_row += drow[mv.first];
            next_col += dcol[mv.first];
            if (next_row == 0) {
                next_row = N;
            }
            if (next_row == N + 1) {
                next_row = 1;
            }
            if (next_col == 0) {
                next_col = N;
            }
            if (next_col == N + 1) {
                next_col = 1;
            }
        }// ���� �̵�      
        moved_cloud.push_back(make_pair(next_row, next_col));
    }
    return moved_cloud;
}

void inc_water(vector<pii> moved_cloud) {
    for (pii p : moved_cloud) {
        board[p.first][p.second]++;
    }
}

void copy_water(vector<pii> moved_cloud) {
    for (pii cur_cloud : moved_cloud) { // ������ �̵��� ��ġ
        for (int i = 0; i < 4; i++) { // �밢�� ��ġ
            if (cur_cloud.first + diagonal_drow[i] >= 1 && cur_cloud.first + diagonal_drow[i] <= N
                && cur_cloud.second + diagonal_dcol[i] >= 1 && cur_cloud.second + diagonal_dcol[i] <= N) {
                if (board[cur_cloud.first + diagonal_drow[i]][cur_cloud.second + diagonal_dcol[i]] != 0) {
                    board[cur_cloud.first][cur_cloud.second]++;
                }
            }
        }
    }
}

void make_cloud(vector<pii> moved_cloud) {
    array<array<int, 51>, 51> visit;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            visit[i][j] = 0;
        }
    }
    for (pii cloud : moved_cloud) {
        visit[cloud.first][cloud.second] = 1;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (visit[i][j] == 0 && board[i][j] >= 2) {
                board[i][j] -= 2; // ���Ǿ� �����
                cloud_position.push(make_pair(i, j));
            }
        }
    }
}

void solve() {
    for (pii mv : moving) {
        vector<pii> moved_cloud = move_cloud(mv); // ���� �̵���Ű��   
        inc_water(moved_cloud); // �� �� ������Ű��
        copy_water(moved_cloud); // �� ���� ����
        make_cloud(moved_cloud); // ���� ����      
    }
}

void print() {
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            ans += board[i][j];
        }
    }
    cout << ans;
}


int main() {
    input();
    get_init_cloud_position();
    solve();
    print();
}