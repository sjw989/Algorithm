#include <iostream>
#include <fstream>
#include <vector>
#include <array>
using namespace std;

int C; // tc 개수
int H, W; // 가로 x 세로
int cnt; // 답 개수

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
            board[i][j] = 0; // 모든 칸을 0으로 초기화
        }
    }
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            char c;
            cin >> c;
            switch (c) {
            case '#':
                board[i][j] = -1; // 못채우는 칸
                break;
            case '.':
                board[i][j] = 1; // 채울 수 있는 칸
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
                return false; // 채워지지 않은 칸이 하나라도 존재
            }
        }
    }
    return true; // 모든 칸이 다 채워진 경우
}

void solve() { // 시작위치        4r
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (board[i][j] == 1) { // 빈칸인 경우                
                for (int k = 0; k < 4; k++) { // 4가지 경우 검사
                    if (can_fill(i, j, k)) { // 채울 수 있으면          

                        board[i][j] = -1;
                        board[i + drow1[k]][j + dcol1[k]] = -1;
                        board[i + drow2[k]][j + dcol2[k]] = -1;
                        // 보드 채우기                        

                        if (all_full()) {
                            cnt++;
                        } // 가득찼는지 검사
                        else {
                            solve();
                        } // 가득 안찼으면 재귀
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