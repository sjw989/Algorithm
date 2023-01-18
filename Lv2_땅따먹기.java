package com.example.algorithm;

public class Lv2_땅따먹기 {
    class Solution {

        int[][] dp;

        int solution(int[][] land) {
            int answer = 0;
            dp = new int[land.length][4];
            for(int i = 0; i < 4; i++) {
                dp[0][i] = land[0][i];
            }

            for(int row = 1; row < dp.length; row++) {
                for(int col = 0; col < 4; col++) {
                    int maximum = 0;
                    for(int c = 0 ; c < 4; c++) {
                        if(col == c) continue;
                        maximum = Math.max(maximum, dp[row-1][c] + land[row][col]);
                    }
                    dp[row][col] = maximum;
                }
            }

            for(int i = 0 ; i < 4; i++) {
                answer = Math.max(dp[land.length - 1 ][i], answer);
            }
            return answer;
        }
    }
}
