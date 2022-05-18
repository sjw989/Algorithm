#include <iostream>
#include <string>
#include <vector>
using namespace std;

int new_board[1001][1001];

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    for (vector<int> sk : skill) {
        int sr = sk[1], sc = sk[2];
        int er = sk[3], ec = sk[4];
        int degree = sk[5];
        if (sk[0] == 1) {  // 적의 공격인 경우는 음수처리
            degree *= -1;
        }
        new_board[sr][sc] += degree;
        new_board[sr][ec + 1] += -1 * degree;
        new_board[er + 1][sc] += -1 *  degree;
        new_board[er + 1][ec + 1] += degree;
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            new_board[i][j + 1] += new_board[i][j];
        }
    }
    for (int j = 0; j < board[0].size(); j++) {
        for (int i = 0; i < board.size(); i++) {
            new_board[i + 1][j] += new_board[i][j];
        }
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            board[i][j] += new_board[i][j];
            if (board[i][j] > 0) {
                answer++;
            }
        }
    }

    
    return answer;
}

int main() {

    vector<vector<int>> board = {{5, 5, 5, 5, 5}, 
                                {5, 5, 5, 5, 5}, 
                                {5, 5, 5, 5, 5}, 
                                {5, 5, 5, 5, 5}};

    vector<vector<int>> skill = {{1, 0, 0, 3, 4, 4},
                                {1, 2, 0, 2, 3, 2}, 
                                {2, 1, 0, 3, 1, 2}, 
                                {1, 0, 1, 3, 3, 1}};

}