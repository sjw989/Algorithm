#include <iostream>
#include <fstream>
#include <array>
#include <cstring>
#include <vector>
#include <string>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
using namespace std;

struct Fish {
    pii pos;
    int dir;
};
int M, S; // 물고기의 수, 연습 횟수
pii shark_pos; // 상어의 위치

array<array<vector<Fish>, 5>, 5> board;
array<array<int, 5>, 5> smell; // 물고기의 냄새가 몇번 남았는지
array<pii, 9> delta = {mp(0,0), mp(0,-1), mp(-1,-1), mp(-1,0) ,mp(-1,1) 
                        ,mp(0,1) ,mp(1,1) ,mp(1,0) ,mp(1,-1) };
                      //   좌      좌상        상       우상      우      우하     하        좌하


void input() {
    //ifstream in("test.txt");
    cin >> M >> S;
    for (int i = 0; i < M; i++) {
        int r, c, d;
        cin >> r >> c >> d;
        Fish fish;
        fish.pos = mp(r, c);
        fish.dir = d;
        board[r][c].push_back(fish);
    }
    int r, c;
    cin >> r >> c;
    shark_pos = mp(r, c);
}

void moveFish() {
    array<array<vector<Fish>, 5>, 5> new_board; // 물고기의 이동이 마친 격자
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (board[i][j].size() > 0) { // 물고기가 있는 칸을 발견하면
                vector<Fish> fishes = board[i][j];
                for (Fish f : fishes) {
                    int dir = f.dir;
                    int c = 8;
                    bool is_move = false;
                    while (c > 0) { // 8방향 탐색
                        int nr = f.pos.first + delta[dir].first;
                        int nc = f.pos.second + delta[dir].second;
                        if (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) { // next가 격자 안이고
                            if (smell[nr][nc] == 0 && mp(nr, nc) != shark_pos) { // 냄새없고, 상어랑 다른위치면
                                f.pos = mp(nr, nc);
                                f.dir = dir;
                                new_board[nr][nc].push_back(f); // 물고기 이동
                                is_move = true;
                                break; // 루프 탈출
                            }
                        }
                        dir--;
                        if (dir <= 0) {
                            dir = 8;
                        }
                        c--;
                    }
                    if (!is_move) { // 8방향 다 탐색하고도 이동 못한 물고기는 원래자리에 그대로
                        new_board[f.pos.first][f.pos.second].push_back(f);
                    }
                }
            }
        }
    }

    board = new_board; // 물고기 이동이 끝나고 격자상태 저장
}

// 상좌 하우
array<int, 5> drow = { 0, -1, 0, 1, 0 };
array<int, 5> dcol = { 0,  0, -1, 0, 1 };
int best_eat;
int best_course = 987654321;

void moveShark(pii cur_pos, int visit[5][5], int course, int eat) {
    /*3. 상어는 연속해서 3칸 이동 (상하좌우)
   -> 중간에 범위 벗어나면 이동 불가능한 방법임
   -> 이동 경로에 물고기가 있으면 그 물고기는 없어지고 냄새 남김
   -> 가능한 방법중에서 없어지는 물고기가 가장 많은 방법을 선택
      -> 여러가지인 경우 사전 순
         -> 사전 순 
            -> 상(1) 좌(2) 하(3) 우(4) 를 이어 붙여서 정수로 만들고 작은 순 */

    if (course > 100) { // 상어가 3번 이동했으면
        
        if (best_eat < eat) { // 기존의 상어가 먹는 물고기보다 더 많은 경우
            best_course = course;
            best_eat = eat; 
        }
        else if(best_eat == eat && best_course > course) { // 기존의 경로보다 사전식 빠른경우
            best_course = course;
        }
        return;
    }
    
    for (int i = 1; i <= 4; i++) {
        int nr = cur_pos.first + drow[i];
        int nc = cur_pos.second + dcol[i];

        if (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) { // 다음 칸이 격자 안이고, 아직 방문하지 않았다면
            if (visit[nr][nc] == 0) {
                visit[nr][nc] = 1; // 방문처리
                moveShark(mp(nr, nc), visit, (course * 10 + i), eat + board[nr][nc].size());
                visit[nr][nc] = 0; // 방문처리
            }
            else {
                moveShark(mp(nr, nc), visit, (course * 10 + i), eat);
            }
        }
    }
}

void removeFish() {
    string str = to_string(best_course);
    if (str.size() < 3) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        // best_course : 134 이면 1 -> 3-> 4 순으로 이동한 것이므로
        int d = str[i] - '0';
        shark_pos = mp(shark_pos.first + drow[d], shark_pos.second + dcol[d]);
        if (board[shark_pos.first][shark_pos.second].size() > 0) {
            board[shark_pos.first][shark_pos.second].clear(); // 상어가 이동한 위치의 물고기 모두 없앰
            smell[shark_pos.first][shark_pos.second] = 3; // 냄새 뿌리기
        }
        
    }
}

void copyFish(array<array<vector<Fish>, 5>, 5> pre_board) {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (pre_board[i][j].size() > 0) {
                for (int k = 0; k < pre_board[i][j].size(); k++) {
                    board[i][j].push_back(pre_board[i][j][k]);
                }
            }
        }
    }
}
void print_board() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            cout << board[i][j].size() << " ";
        }
        cout << endl;
    }
}
void removeSmell() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (smell[i][j] > 0) {
                smell[i][j]--;
            }
        }
    }
}

void solve() {
    while (S > 0){ // S번 반복
        S--;
        //cout << shark_pos.first << "," << shark_pos.second << endl;
        //print_board();
        array<array<vector<Fish>, 5>, 5> pre_board = board; // 물고기 복사를 위해 이전상태 저장
        moveFish(); // 물고기 이동

        int visit[5][5];
        vector<pii> course;
        for (int i = 0; i < 5; i++) {
            memset(visit[i], 0, sizeof(visit[i]));
        }
        moveShark(shark_pos, visit, 0, 0 ); // 상어이동
        removeFish(); // 상어가 먹은 물고기들 없애줌
        //cout << best_course <<" " << best_eat << endl;
        //cout << endl;
        best_course = 987654321;
        best_eat = 0;
        removeSmell(); // 냄새 지우기
        copyFish(pre_board); // 물고기 복제

    }

}
void print() {
    int ans = 0;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            ans += board[i][j].size();
        }
    }
    cout << ans;
}
int main() {
    input();
    solve();
    print();
}
/*
1. 복제 시작 (5번에서 효과 나타남)

2. 모든 물고기 1칸 이동
    1) 상어, 물고기냄새가 없는 칸으로만 이동가능
    2) 이동 가능한 방향을 찾을 때 까지 반시계 45도 회전
    3) 이동 가능한 칸이 없으면 이동하지 않음

3. 상어는 연속해서 3칸 이동 (상하좌우)
   -> 중간에 범위 벗어나면 이동 불가능한 방법임
   -> 이동 경로에 물고기가 있으면 그 물고기는 없어지고 냄새 남김
   -> 가능한 방법중에서 없어지는 물고기가 가장 많은 방법을 선택
      -> 여러가지인 경우 사전 순
         -> 사전 순 
            -> 상(1) 좌(2) 하(3) 우(4) 를 이어 붙여서 정수로 만들고 작은 순 
4. 두 번 전 연습에서 생긴 냄새가 사라짐 
   -> 냄새는 2턴을 가짐
5. 복제된 물고기는 그 자리에 위치와 방향을 그대로 가진다.
6. 격자에 남은 물고기의 마릿수는?






*/