#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int N;
long long ans;
array<long long, 100001> dist;
array<long long, 100001> price;


void input() {
	//ifstream in("test.txt");
	cin >> N;
	int k;
	for (int i = 1; i <= N-1; i++) {		
		cin >> k;
		dist[i] = k;
	} // 도시간의 거리
	for (int i = 1; i <= N; i++) {
		cin >> k;
		price[i] = k;
	} // 도시의 리터당 가격
}

void greedy() {
	/*
	이번 도시 주유소 가격이 다음 도시 주유소 가격보다 비싸면,
	최소만 넣음.
	이번 도시 주유소 가격이 자신보다 비싸지는 주유소 찾을때까지 더해주고
	그거만큼 커버
	*/
	long long start = 1; // 시작점
	long long d = dist[start];
	for (int i = 2; i <= N - 1; i++) {
		if (price[start] < price[i]) { // 현재 주유소로 다음 거 까지 커버치는 경우
			d += dist[i];
		}
		else {
			ans += d * price[start];
			d = dist[i];
			start = i;		

		}
	}
	ans += d * price[start];
}

int main() {
	input();
	greedy();
	cout << ans;
}