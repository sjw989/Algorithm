#include <iostream>
#include <array>
using namespace std;

int N, M, K; // �л� ��, ģ������ �� , �������ִ� ��
array<int, 10001> student;
array<int, 10001> cost;

int find_parent(int node) { // ��ǥ��� ã��
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
} // ��ǥ��� ��ġ��

int main() {

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        student[i] = i;
    } // �ڱ� �ڽ��� ��ǥ���� ������ ��ȣ��Ÿ����
    for (int i = 1; i <= N; i++) {
        cin >> cost[i];
    } // ģ����� �Է�
    for (int i = 0; i < M; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        union_parent(node1, node2);
    } // ģ������ �α�

    int b_young = 0; // ģ�����
    for (int i = 1; i <= N; i++) {
        int parent = find_parent(i);
        if (cost[parent] != -1) {
            b_young += cost[parent];
            cost[parent] = -1;
        }
    } // for-loop�� ���鼭 ����� ���ذ��ǵ� �ߺ����� ���ϱ����� 
      // �� �� ����� ��ǥ����� cost���� -1�� �ٲ��ش�   
    if (b_young <= K) {
        printf("%d\n", b_young);
    }
    else {
        printf("Oh no\n");
    }

    return 0;

}