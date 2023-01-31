package com.example.algorithm;

import java.util.LinkedList;
import java.util.Queue;

public class Lv2_게임맵최단거리 {
    class Solution {

        int[] drow = {1, -1, 0, 0};
        int[] dcol = {0, 0, 1, -1};

        class Pair {
            int row, col;

            Pair(int row, int col) {
                this.row = row;
                this.col = col;
            }
        }

        public int solution(int[][] maps) {
            int answer = -1;
            int n = maps.length;
            int m = maps[0].length;
            int visit[][] = new int[n + 1][m + 1];
            Queue<Pair> q = new LinkedList();
            visit[1][1] = 1;
            q.add(new Pair(1, 1));
            while (!q.isEmpty()) {
                Pair cur = q.poll();
                for (int i = 0; i < 4; i++) {
                    int nr = cur.row + drow[i];
                    int nc = cur.col + dcol[i];

                    if (nr >= 1 && nr <= n && nc >= 1 && nc <= m) {
                        if (nr == n && nc == m) {
                            answer = visit[cur.row][cur.col] + 1;
                            return answer;
                        }
                        if (visit[nr][nc] == 0 && maps[nr - 1][nc - 1] == 1) {
                            q.add(new Pair(nr, nc));
                            visit[nr][nc] = visit[cur.row][cur.col] + 1;
                        }
                    }

                }
            }


            return answer;
        }
    }
}
