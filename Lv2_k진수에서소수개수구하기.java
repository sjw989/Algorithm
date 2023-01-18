package com.example.algorithm;

import java.util.*;
public class Lv2_k진수에서소수개수구하기 {
    class Solution {
        public String getKnary(int n , int k) {
            String kNary = "";
            while(n / k != 0) {
                int t = n % k;
                kNary = String.valueOf(t) + kNary;
                n = n / k;
            }
            kNary = String.valueOf(n%k) + kNary;
            return kNary;
        }
        public boolean isPrime(long n) {
            if(n < 2) return false;
            long pivot = Math.round((Math.sqrt(n)));
            for(long i = 2; i <= pivot; i++) {
                if(n % i == 0) {
                    return false;
                }
            }
            return true;
        }

        public int solution(int n, int k) {
            int answer = -1;
            String kNary = getKnary(n,k);
            kNary += "0";
            ArrayList<Long> arr = new ArrayList();
            long num = 0L;

            for(int i = 0; i < kNary.length(); i++) {
                int nth = kNary.charAt(i) - '0';
                if( nth >= 1 && nth <= 9) {
                    num = num*10 + nth;
                }
                else {
                    if(isPrime(num)){
                        arr.add(num);
                    }
                    num = 0L;
                }
            }
            answer = arr.size();
            return answer;
        }
    }
}
