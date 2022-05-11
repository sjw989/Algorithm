#include <iostream>
#include <string>
#include <array>
#include <vector>

using namespace std;


array<array<int, 101>, 101> board;
array<array<int, 101>, 101> temp;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    int cnt = 1;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            board[i][j] = cnt;
            cnt++;
        }
    } // 초기 행렬 채우기

    
    

    for (vector<int> q : queries) {
        int sr = q[0], sc = q[1];
        int er = q[2], ec = q[3];
        
        // 가로 방향 -> row 고정시키고 col만 변경
        int cnt = 0;
        for (int i = sc; i < ec; i++) {
            temp[sr][i + 1] = board[sr][i];
            temp[er][ec - cnt - 1] = board[er][ec - cnt];
            cnt++;
        }
        cnt = 0;
        // 세로 방향 -> col 고정시키고 row만 변경
        for (int i = sr; i < er; i++) {
            temp[i + 1][ec] = board[i][ec];
            temp[er - cnt - 1][sc] = board[er - cnt][sc];
            cnt++;
        }
        int minimum = 987654321;
        for (int i = sr; i <= er; i++) {
            for (int j = sc; j <= ec; j++) {
                if (temp[i][j] != 0) {
                    minimum = min(minimum, temp[i][j]);
                    board[i][j] = temp[i][j];
                    temp[i][j] = 0;
                }
            }
        }
        answer.push_back(minimum);

        
     

    }

    
    return answer;
}

int main() {

    int rows = 6;
    int columns = 6;
    vector<vector<int>> queries = {{2, 2, 5, 4}, {3, 3, 6, 6}, {5, 1, 6, 3}};
    solution(rows, columns, queries);

}