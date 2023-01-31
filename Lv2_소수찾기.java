package com.example.algorithm;

import java.util.*;
public class Lv2_소수찾기 {
    class Solution {
        int[] visit;
        int ans = 0;
        Set<Integer> set = new HashSet();
        boolean isPrime(int n) {
            for(int i = 2; i < n ; i++) {
                if(n % i == 0) {
                    return false;
                }
            }
            return true;
        }

        void dfs(int[] numList, int cur_n) {
            //System.out.println(cur_n);
            if(cur_n > 1 && isPrime(cur_n)) {
                set.add(cur_n);
            }
            for(int i = 0 ; i < numList.length; i++) {
                if(visit[i] == 0){
                    visit[i] = 1;
                    dfs(numList, cur_n * 10 + numList[i]);
                    visit[i] = 0;
                }
            }
        }

        public int solution(String numbers) {
            int answer = 0;
            visit = new int[numbers.length() + 1];
            int[] numList = new int[numbers.length()];
            for(int i = 0 ; i < numbers.length(); i++) {
                numList[i] = numbers.charAt(i) - '0';
            }
            dfs(numList, 0);
            answer = set.size();
            return answer;
        }
    }
}
