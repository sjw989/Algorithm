#include <iostream>
#include <queue>
#include <vector>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;

int visit[101][101];
int drow[4] = { 0,0,1,-1 };
int dcol[4] = { 1,-1,0,0 };

int bfs(int r, int c, int m , int n, vector<vector<int>> picture) {
    int color = picture[r][c];
    int area_size = 1; // 현재 칸을 포함하므로
    queue<pii> q;
    q.push(mp(r, c));
    visit[r][c] = 1;

    while (!q.empty()) {
        pii cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = cur.first + drow[i];
            int nc = cur.second + dcol[i];            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                if (picture[nr][nc] == color && visit[nr][nc] == 0) {     
                    area_size++;
                    visit[nr][nc] = 1;
                    q.push(mp(nr, nc));
                }
            }
        }
    }    
    return area_size;
}

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;    

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            visit[i][j] = 0;
        }
    } // visit 초기화

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (picture[i][j] > 0 && visit[i][j] == 0) {
                number_of_area++; // 영역 +1
                int area_size = bfs(i, j, m, n, picture);
                max_size_of_one_area = max(max_size_of_one_area, area_size);
            }
        }
    }

    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;




    return answer;
}

int main() {
    int m = 6, n = 4;
    vector<vector<int>> picture = {{1, 1, 1, 0},
                                    {1, 2, 2, 0},
                                    {1, 0, 0, 1},
                                    {0, 0, 0, 1}, 
                                    {0, 0, 0, 3},
                                    {0, 0, 0, 3}};

    solution(m, n, picture);


}