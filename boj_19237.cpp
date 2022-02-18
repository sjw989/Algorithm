#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#define MAX_SIZE 20+1
#define MAX_N 20*20+1
#define pii pair<int,int>
using namespace std;

typedef struct Shark {
    pii pos; // ����� ��ġ
    int id; // ����� ��ȣ
    int direction; // ����
    Shark(pii p, int i) {
        pos = p;
        id = i;
    }
};

int N, M, K; // N x N , M - ����� ���� ��, K - ���� ���Ӱ��� �ð�
int ans; // ����
int drow[4] = { 0,0,1,-1 };
int dcol[4] = { 1,-1,0,0 };
array<array<pii,MAX_SIZE>,MAX_SIZE> board; // ���� (����� ��ȣ, ���� �ð�)
array<array<array<int, 5>, 5>, MAX_N> priority;
map<int, pii> m = { {1,make_pair(-1,0)}, {2,make_pair(1,0)}, {3,make_pair(0,-1)}, {4,make_pair(0,1)} };
vector<Shark> shark;

bool cmp(Shark a, Shark b) {
    return a.id > b.id;
}

void input() {
    //ifstream in("test.txt");
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int k;
            cin >> k;
            board[i][j] = make_pair(k,0);
            if (board[i][j].first != 0) {
                shark.push_back(Shark(make_pair(i, j), board[i][j].first));                
            }
        }
    }
    sort(shark.begin(), shark.end(),cmp); // ����ȣ ������������ ����    

    for (int i = M-1; i >=0; i--) {
        cin >> shark[i].direction;
    }    
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= 4; j++) {
            for (int k = 1; k <= 4; k++) {
                cin >> priority[i][j][k];            
            }
        }
    }    
}

void solve() {          
    while (shark.size() > 1) { // �� 1������ �� �� ���� �ݺ�
        
        if (ans == 1000) { // 1000�ʰ� �Ǹ� return ��? -> �� �̵��ؼ� 1���� ���´ٰ��ص� �̹� 1001��
            ans = -1;
            return;
        }
        // ��� �� ���� �Ѹ���
        for (int i = 0; i < shark.size(); i++) {
            board[shark[i].pos.first][shark[i].pos.second] = make_pair(shark[i].id, K);
        }

        vector<Shark> new_shark; // �̵��� ������ ���� ����
        // ��� �� ���ؼ� �̵�
        for (int s = 0; s < shark.size(); s++) {
            Shark cur_shark = shark[s];

            bool is_empty = false; // ������ ĭ���� ����ִ� ĭ�� �����ϴ���
            for (int i = 0; i < 4; i++) { // ������ 4������ �Ѿ �� �ִ� ĭ Ž��
                int nr = cur_shark.pos.first + drow[i];
                int nc = cur_shark.pos.second + dcol[i];
                if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) { // ���� ĭ�� ���� �ȿ� �����ϰ�                    
                    if (board[nr][nc].second == 0) { // ���� ĭ�� �ƹ� ������ ������                       
                        is_empty = true;
                        break;
                    }
                }
            }
         
            array<int, 5> cur_priority = priority[cur_shark.id][cur_shark.direction];
            if (is_empty) { // ����ִ� ĭ�� �����ϴ� ��� �켱������ ���� �̵�                
                for (int i = 1; i <= 4; i++) {
                    int dir_priority = cur_priority[i]; // ����� �켱���� ������ ���� �Ѱ������⾿ ��������
                    int nr = cur_shark.pos.first + m[dir_priority].first; // �켱������ ���� ���� ���� row
                    int nc = cur_shark.pos.second + m[dir_priority].second; // �켱������ ���� ���� ���� col

                    if (nr >= 1 && nr <= N && nc >=1 && nc <= N &&
                        board[nr][nc].second == 0) { // �� ������ �ϴ� ������ ����ִٸ�
                        board[nr][nc].first = cur_shark.id; // �ڽ��� ������ ǥ��
                        // -> ��� ��ȣ�� ū �ֵ���� �̵��߱� ������ �׳� ����ᵵ ��.

                        new_shark.push_back(Shark(make_pair(nr, nc), cur_shark.id)); // ����� ���ο� ��ġ push
                        new_shark.back().direction = dir_priority; // �ٶ󺸴� ���� = �켱���� �̵��� ����
                        break;
                    }                    
                }
            }
            else { // ����ִ� ĭ�� �������� �ʴ°��, �ڽ��� ������ �ִ� ������ �̵�
                for (int i = 1; i <= 4; i++) {
                    int dir_priority = cur_priority[i]; // ����� �켱���� ������ ���� �Ѱ������⾿ ��������
                    int nr = cur_shark.pos.first + m[dir_priority].first; // �켱������ ���� ���� ���� row
                    int nc = cur_shark.pos.second + m[dir_priority].second; // �켱������ ���� ���� ���� col

                    if (nr >= 1 && nr <= N && nc >= 1 && nc <= N
                        && board[nr][nc].first == cur_shark.id) { // �ڽ��� id���� ������ ĭ���� �̵�
                        board[nr][nc].second = -1; // ���Ӱ� �̵��� ������ ǥ��
                        new_shark.push_back(Shark(make_pair(nr, nc), cur_shark.id)); // ����� ���ο� ��ġ push
                        new_shark.back().direction = dir_priority; // �ٶ󺸴� ���� = �켱���� �̵��� ����                           
                        break;
                    }
                }

            }               
        }


        /*
        Next Shark ���ϴ� ����
        1. new_shark �ĺ��� �߿��� ������ �� id����
           ���� board�� ����Ǿ��ִ� (������ �� �̵��� ĭ)�� �����ϴٸ�
           �ٸ� ���� ������ �ʰ� �� �̵��� ���̹Ƿ� �߰�
           second ���� 0 ���Ͽ��� �ϴ� ������, �ڽ��� ������ ã�Ƽ� �̵��� ���̽�����
           �����ϱ� ����        
        */
        vector<Shark> next_shark;
        for (Shark s : new_shark) {
            bool is_dead = true;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (s.id == board[i][j].first && board[i][j].second <= 0) { // id���� ����, �����̵��� ���̸�
                        is_dead = false; // �������
                    }
                }
            }
            if (!is_dead) { // ��������� �߰�
                next_shark.push_back(s);
            }
        }

        shark = next_shark; // shark ���� ������Ʈ
        sort(shark.begin(), shark.end(), cmp); // ū ��ȣ ������ �̵��ϱ����� ����

        for (int i = 1; i <= N; i++) { // ���� ���ҽ�Ű��
            for (int j = 1; j <= N; j++) {
                if (board[i][j].second > 0) { 
                    board[i][j].second--;// ���� ���ҽ�Ű��

                    if (board[i][j].second == 0) { // 0�� �Ǿ����� ���� ���ε� �����ֱ�
                        board[i][j] = make_pair(0, 0); // ��ĭ���� ����
                    }
                }                
            }
        }
        ans++;

    }
}
void print() {        
    cout << ans;    
}

int main() {    
    input();
    solve();
    print();
}