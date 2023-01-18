package com.example.algorithm;

import java.util.*;
public class Lv2_방문길이 {
    class Solution {
        int x = 6, y = 6;
        int[][][] visit = new int[12][12][4]; // 현재 좌표에서 상하좌우로 나간 적 있는지 확인

        public int solution(String dirs) {
            int answer = 0;
            for(int i = 0 ; i < dirs.length(); i++) {
                char cmd = dirs.charAt(i);
                int next_x = x, next_y = y;

                int dir = 0;
                int reverseDir = 1;
                switch(cmd) {
                    case 'U' :
                        if(next_y - 1 > 0) next_y -= 1;
                        else continue;
                        break;
                    case 'L' :
                        if(next_x - 1 > 0) next_x -= 1;
                        else continue;
                        dir = 2;
                        reverseDir = 3;
                        break;
                    case 'R' :
                        if(next_x + 1 < 12) next_x += 1;
                        else continue;
                        dir = 3;
                        reverseDir = 2;
                        break;
                    case 'D' :
                        if(next_y + 1 < 12) next_y += 1;
                        else continue;
                        dir = 1;
                        reverseDir = 0;
                        break;
                }

                if(visit[y][x][dir] == 0 && visit[next_y][next_x][reverseDir] == 0) {
                    visit[y][x][dir] = 1;
                    visit[next_y][next_x][reverseDir] = 1;
                    answer++;
                }
                x = next_x;
                y = next_y;
            }
            return answer;
        }
    }
}
