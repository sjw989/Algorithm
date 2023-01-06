package com.example.algorithm;

public class Lv2_숫자의표현 {
    public int solution(int n) {
        int answer = 0;

        for(int i = 1; i <= n ; i++) {
            int t = 0;
            for(int j = i; j <= n; j++){
                t += j;
                if(t >= n) {
                    if(t == n) answer++;
                    break;
                }
            }
        }
        return answer;
    }
}
