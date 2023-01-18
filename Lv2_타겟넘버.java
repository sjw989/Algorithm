package com.example.algorithm;

public class Lv2_타겟넘버 {
    class Solution {
        int ans = 0;

        public void dfs(int[] numbers, int target, int idx, int n) {
            if(idx == numbers.length) {
                if( n == target) ans++;
                return;
            }

            int curN = numbers[idx];
            dfs(numbers, target, idx + 1, n + curN);
            dfs(numbers, target, idx + 1, n + (-1 * curN));
        }

        public int solution(int[] numbers, int target) {
            int answer = 0;
            dfs(numbers, target, 0, 0);
            answer = ans;
            return answer;
        }
    }
}
