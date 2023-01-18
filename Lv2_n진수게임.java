package com.example.algorithm;

public class Lv2_n진수게임 {
    class Solution {
        String getString(int n , int t, int m) {
            String str = "";
            int i = 0;
            while(str.length() < m*t) {
                str += Integer.toString(i, n);
                i++;
            }
            return str;
        }

        public String solution(int n, int t, int m, int p) {
            String answer = "";
            String str = getString(n, t, m);
            String tubeStr = "";
            int cnt = 0;
            while(cnt < t) {
                tubeStr += str.charAt((p-1) + m*(cnt));
                cnt++;
            }
            answer = tubeStr.toUpperCase();
            return answer;
        }
    }
}
