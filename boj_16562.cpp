#include <iostream>
#include <array>
using namespace std;

int N, M, K; // 학생 수, 친구관계 수 , 가지고있는 돈
array<int, 10001> student;
array<int, 10001> cost;

int find_parent(int node) { // 대표노드 찾기
    if (student[node] == node) {
        return student[node];
    }
    else {
        return student[node] = find_parent(student[node]);
    }
}

void union_parent(int node1, int node2) {
    int parent1 = find_parent(node1);
    int parent2 = find_parent(node2);
    if (cost[parent1] <= cost[parent2]) {
        student[parent2] = parent1;
        cost[parent2] = cost[parent1];
    }
    else {
        student[parent1] = parent2;
        cost[parent1] = cost[parent2];
    }
} // 대표노드 합치기

int main() {

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        student[i] = i;
    } // 자기 자신을 대표노드로 가지는 상호배타집합
    for (int i = 1; i <= N; i++) {
        cin >> cost[i];
    } // 친구비용 입력
    for (int i = 0; i < M; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        union_parent(node1, node2);
    } // 친구관계 맺기

    int b_young = 0; // 친구비용
    for (int i = 1; i <= N; i++) {
        int parent = find_parent(i);
        if (cost[parent] != -1) {
            b_young += cost[parent];
            cost[parent] = -1;
        }
    } // for-loop을 돌면서 비용일 더해갈건데 중복없이 더하기위해 
      // 한 번 계산한 대표노드의 cost값을 -1로 바꿔준다   
    if (b_young <= K) {
        printf("%d\n", b_young);
    }
    else {
        printf("Oh no\n");
    }

    return 0;

}
