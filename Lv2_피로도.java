package com.example.algorithm;

import java.util.*;
public class Lv2_피로도 {
    class Solution {

        int ans = 0;
        int[] visit = new int[9];

        public void dfs(int cur_k, int[][] dungeons, int cnt) {

            for(int i = 0 ; i < dungeons.length; i++) {
                if(visit[i] == 0 && cur_k >= dungeons[i][0]) {
                    visit[i] = 1;
                    dfs(cur_k - dungeons[i][1], dungeons, cnt + 1);
                    visit[i] = 0;
                }
            }
            ans = Math.max(ans, cnt);
            return;
        }

        public int solution(int k, int[][] dungeons) {
            int answer = -1;
            dfs(k, dungeons, 0);

            answer = ans;
            return answer;
        }
    }
}
