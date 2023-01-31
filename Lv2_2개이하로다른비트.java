package com.example.algorithm;

public class Lv2_2개이하로다른비트 {
    class Solution {
        long getFx(long n) {
            String str = Long.toString(n, 2);
            long cmp = 0;
            int cnt = 0;

            for(int i = str.length() - 1; i >= 0 ; i--) {
                if(str.charAt(i) == '1') {
                    cnt++;
                }
                else {
                    break;
                }
            }
            if(cnt <= 1) {
                cmp = n + 1;
            }
            else {
                long e = 1;
                for(int i = 0 ; i < cnt - 1; i++) {
                    e *= 2 ;
                }
                cmp = n + e;
            }
            return cmp;
        }

        public long[] solution(long[] numbers) {
            long[] answer = new long[numbers.length];
            for(int i = 0 ; i < numbers.length; i++) {
                long n = numbers[i];
                answer[i] = getFx(n);
            }
            return answer;
        }
    }
}
