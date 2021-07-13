#include <iostream>
#include <fstream>
#include <vector>
#include <array>
using namespace std;

int C; // tc ����
int H, W; // ���� x ����
int cnt; // �� ����

array<array<int, 21>, 21> board;
array<int, 4 > drow1 = { +1, +1, 0,  0 };
array<int, 4 > dcol1 = { 0,  0, +1, +1 };
array<int, 4 > drow2 = { +1, +1, +1, +1 };
array<int, 4 > dcol2 = { -1, +1, +1, 0 };
vector<int> result;
void input() {
    cin >> H >> W;
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            board[i][j] = 0; // ��� ĭ�� 0���� �ʱ�ȭ
        }
    }
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            char c;
            cin >> c;
            switch (c) {
            case '#':
                board[i][j] = -1; // ��ä��� ĭ
                break;
            case '.':
                board[i][j] = 1; // ä�� �� �ִ� ĭ
                break;
            }
        }
    }
}

bool can_fill(int row, int col, int k) {
    if (row + drow1[k] >= 1 && row + drow1[k] <= 20
        && col + dcol1[k] >= 1 && col + dcol1[k] <= 20
        && row + drow2[k] >= 1 && row + drow2[k] <= 20
        && col + dcol2[k] >= 1 && col + dcol2[k] <= 20) {
        if (board[row + drow1[k]][col + dcol1[k]] == 1
            && board[row + drow2[k]][col + dcol2[k]] == 1) {
            return true;
        }
    }
    return false;

}

bool all_full() {
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (board[i][j] == 1) {
                return false; // ä������ ���� ĭ�� �ϳ��� ����
            }
        }
    }
    return true; // ��� ĭ�� �� ä���� ���
}

void solve() { // ������ġ        4r
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (board[i][j] == 1) { // ��ĭ�� ���                
                for (int k = 0; k < 4; k++) { // 4���� ��� �˻�
                    if (can_fill(i, j, k)) { // ä�� �� ������          

                        board[i][j] = -1;
                        board[i + drow1[k]][j + dcol1[k]] = -1;
                        board[i + drow2[k]][j + dcol2[k]] = -1;
                        // ���� ä���                        

                        if (all_full()) {
                            cnt++;
                        } // ����á���� �˻�
                        else {
                            solve();
                        } // ���� ��á���� ���
                        board[i][j] = 1;
                        board[i + drow1[k]][j + dcol1[k]] = 1;
                        board[i + drow2[k]][j + dcol2[k]] = 1;
                    }
                }
                return;
            }
        }
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
        cnt = 0;
        input();
        solve();
        result.push_back(cnt);
    }
    print();    
}