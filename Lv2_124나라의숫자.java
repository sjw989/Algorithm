package com.example.algorithm;

public class Lv2_124나라의숫자 {
    class Solution {
        String[] list = {"4", "1", "2"};
        public String solution(int n) {
            String answer = "";
            if(n < 4) {
                answer = list[n%3];
                return answer;
            }
            while(true) {
                int d = n / 3;
                int m = n % 3;
                answer = list[m] + answer;
                if( m == 0) {
                    n = d - 1;
                }
                else {
                    n = d;
                }
                if(n == 0) break;
            }

            return answer;
        }
    }
}
