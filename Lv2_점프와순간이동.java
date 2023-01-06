package com.example.algorithm;

public class Lv2_점프와순간이동 {

    public int solution(int n) {
        int answer = 0;
        while (n > 1) {
            if (n % 2 == 0) { // 짝수
                n = n / 2;
            } else { // 홀수
                answer++;
                n = (n - 1) / 2;
            }
        }
        answer++;
        return answer;
    }
}
