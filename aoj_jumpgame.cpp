#include <iostream>
#include <array>
#include <vector>
using namespace std;
int C; // tc����
int n; // ���� ũ��

vector<int> result;
array<array<int, 101>, 101> board;
array<array<int, 101>, 101> can_down;
array<array<int, 101>, 101> can_right;

void input() {    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }
}

int solve(int row, int col) {        
    if (board[row][col] == 0) {        
        return 1; // ����
    }

    if (board[row][col] == -1) {
        return -1; // �ش� ĭ�� Ž�� �� �ʿ� ����
    }

    int jump = board[row][col]; // ���� �� �� �ִ� ĭ ��
    if (row + jump <= n) { // down üũ ����
        if (solve(row + jump, col) == 1) {
            return 1;
        }
        else {
            can_down[row][col] = -1;
        }
    }
    else {
        can_down[row][col] = -1;
    }
    if (col + jump <= n) { // right üũ ����
        if (solve(row, col + jump) == 1) {
            return 1;
        }
        else {
            can_right[row][col] = -1;
        }
    }
    else {
        can_right[row][col] = -1;
    }

    if (can_right[row][col] == -1 && can_down[row][col] == -1) {
        board[row][col] = -1;
        return -1;
    }

}
void print() {
    for (auto ans : result) {
        if (ans == 1) {
            cout << "YES" << "\n";
        }
        else {
            cout << "NO" << "\n";
        }
    }
}

int main() {    
    cin >> C;
    for (int i = 0; i < C; i++) {
        cin >> n;
        input();
        if (solve(1, 1) == 1) {
            result.push_back(1);
        }
        else {
            result.push_back(0);
        }        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                can_down[i][j] = 0;
                can_right[i][j] = 0;                
            }            
        }        
    }    
    print();    
}