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
int M, S; // ������� ��, ���� Ƚ��
pii shark_pos; // ����� ��ġ

array<array<vector<Fish>, 5>, 5> board;
array<array<int, 5>, 5> smell; // ������� ������ ��� ���Ҵ���
array<pii, 9> delta = {mp(0,0), mp(0,-1), mp(-1,-1), mp(-1,0) ,mp(-1,1) 
                        ,mp(0,1) ,mp(1,1) ,mp(1,0) ,mp(1,-1) };
                      //   ��      �»�        ��       ���      ��      ����     ��        ����


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
    array<array<vector<Fish>, 5>, 5> new_board; // ������� �̵��� ��ģ ����
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (board[i][j].size() > 0) { // ����Ⱑ �ִ� ĭ�� �߰��ϸ�
                vector<Fish> fishes = board[i][j];
                for (Fish f : fishes) {
                    int dir = f.dir;
                    int c = 8;
                    bool is_move = false;
                    while (c > 0) { // 8���� Ž��
                        int nr = f.pos.first + delta[dir].first;
                        int nc = f.pos.second + delta[dir].second;
                        if (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) { // next�� ���� ���̰�
                            if (smell[nr][nc] == 0 && mp(nr, nc) != shark_pos) { // ��������, ���� �ٸ���ġ��
                                f.pos = mp(nr, nc);
                                f.dir = dir;
                                new_board[nr][nc].push_back(f); // ����� �̵�
                                is_move = true;
                                break; // ���� Ż��
                            }
                        }
                        dir--;
                        if (dir <= 0) {
                            dir = 8;
                        }
                        c--;
                    }
                    if (!is_move) { // 8���� �� Ž���ϰ� �̵� ���� ������ �����ڸ��� �״��
                        new_board[f.pos.first][f.pos.second].push_back(f);
                    }
                }
            }
        }
    }

    board = new_board; // ����� �̵��� ������ ���ڻ��� ����
}

// ���� �Ͽ�
array<int, 5> drow = { 0, -1, 0, 1, 0 };
array<int, 5> dcol = { 0,  0, -1, 0, 1 };
int best_eat;
int best_course = 987654321;

void moveShark(pii cur_pos, int visit[5][5], int course, int eat) {
    /*3. ���� �����ؼ� 3ĭ �̵� (�����¿�)
   -> �߰��� ���� ����� �̵� �Ұ����� �����
   -> �̵� ��ο� ����Ⱑ ������ �� ������ �������� ���� ����
   -> ������ ����߿��� �������� ����Ⱑ ���� ���� ����� ����
      -> ���������� ��� ���� ��
         -> ���� �� 
            -> ��(1) ��(2) ��(3) ��(4) �� �̾� �ٿ��� ������ ����� ���� �� */

    if (course > 100) { // �� 3�� �̵�������
        
        if (best_eat < eat) { // ������ �� �Դ� ����⺸�� �� ���� ���
            best_course = course;
            best_eat = eat; 
        }
        else if(best_eat == eat && best_course > course) { // ������ ��κ��� ������ �������
            best_course = course;
        }
        return;
    }
    
    for (int i = 1; i <= 4; i++) {
        int nr = cur_pos.first + drow[i];
        int nc = cur_pos.second + dcol[i];

        if (nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4) { // ���� ĭ�� ���� ���̰�, ���� �湮���� �ʾҴٸ�
            if (visit[nr][nc] == 0) {
                visit[nr][nc] = 1; // �湮ó��
                moveShark(mp(nr, nc), visit, (course * 10 + i), eat + board[nr][nc].size());
                visit[nr][nc] = 0; // �湮ó��
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
        // best_course : 134 �̸� 1 -> 3-> 4 ������ �̵��� ���̹Ƿ�
        int d = str[i] - '0';
        shark_pos = mp(shark_pos.first + drow[d], shark_pos.second + dcol[d]);
        if (board[shark_pos.first][shark_pos.second].size() > 0) {
            board[shark_pos.first][shark_pos.second].clear(); // �� �̵��� ��ġ�� ����� ��� ����
            smell[shark_pos.first][shark_pos.second] = 3; // ���� �Ѹ���
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
    while (S > 0){ // S�� �ݺ�
        S--;
        //cout << shark_pos.first << "," << shark_pos.second << endl;
        //print_board();
        array<array<vector<Fish>, 5>, 5> pre_board = board; // ����� ���縦 ���� �������� ����
        moveFish(); // ����� �̵�

        int visit[5][5];
        vector<pii> course;
        for (int i = 0; i < 5; i++) {
            memset(visit[i], 0, sizeof(visit[i]));
        }
        moveShark(shark_pos, visit, 0, 0 ); // ����̵�
        removeFish(); // �� ���� ������ ������
        //cout << best_course <<" " << best_eat << endl;
        //cout << endl;
        best_course = 987654321;
        best_eat = 0;
        removeSmell(); // ���� �����
        copyFish(pre_board); // ����� ����

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
1. ���� ���� (5������ ȿ�� ��Ÿ��)

2. ��� ����� 1ĭ �̵�
    1) ���, ����⳿���� ���� ĭ���θ� �̵�����
    2) �̵� ������ ������ ã�� �� ���� �ݽð� 45�� ȸ��
    3) �̵� ������ ĭ�� ������ �̵����� ����

3. ���� �����ؼ� 3ĭ �̵� (�����¿�)
   -> �߰��� ���� ����� �̵� �Ұ����� �����
   -> �̵� ��ο� ����Ⱑ ������ �� ������ �������� ���� ����
   -> ������ ����߿��� �������� ����Ⱑ ���� ���� ����� ����
      -> ���������� ��� ���� ��
         -> ���� �� 
            -> ��(1) ��(2) ��(3) ��(4) �� �̾� �ٿ��� ������ ����� ���� �� 
4. �� �� �� �������� ���� ������ ����� 
   -> ������ 2���� ����
5. ������ ������ �� �ڸ��� ��ġ�� ������ �״�� ������.
6. ���ڿ� ���� ������� ��������?






*/