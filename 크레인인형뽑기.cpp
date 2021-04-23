#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> pop_doll;
    for (auto index : moves) {
        int pos = -1;
        for (int j = 0; j < board.size(); j++) {
            if (board[j][index - 1] != 0) {
                pos = j;
                break;
            }
        }
        if (pos != -1) {
            if (!pop_doll.empty() && pop_doll.top() == board[pos][index - 1]) {
                pop_doll.pop();
                answer += 2;
            }
            else {
                pop_doll.push(board[pos][index - 1]);
            }
            board[pos][index - 1] = 0;
        }
    }
    return answer;
}
int main() {
    vector<vector<int>> board = { {0, 0, 0, 0, 0}, {0, 0, 1, 0, 3}, {0, 2, 5, 0, 1},
                                 {4, 2, 4, 4, 2}, {3, 5, 1, 3, 1} };
    vector<int> moves = { 1, 5, 3, 5, 1, 2, 1, 4 };

    int result = solution(board, moves);
    cout << result << endl;
}