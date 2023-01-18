package com.example.algorithm;

import java.util.*;
public class Lv2_프렌즈4블록 {
    class Solution {

        int[] drow = {1,1,0};
        int[] dcol = {0,1,1};

        class Pair {
            int first,second;
            Pair(int first, int second) {
                this.first = first;
                this.second = second;
            }
        }

        public int solution(int m, int n, String[] board) {
            int answer = 0;

            char[][] boards= new char[m+2][n+2];
            for(int i = 0 ; i <= m + 1; i++) {
                for(int j = 0 ; j <= n + 1; j++) {
                    if(i == 0 || j == 0 || i == m + 1 || j == n + 1) {
                        boards[i][j] = '1';
                    }
                    else {
                        boards[i][j] = board[i-1].charAt(j-1);
                    }
                }
            }

            while(true) {
                ArrayList<Pair> removed = new ArrayList();
                int[][] visit = new int[m+2][n+2];
                for(int i = 1; i <= m-1; i++) {
                    for(int j = 1; j <= n-1; j++) {
                        if(boards[i][j] == '0') continue; // 빈칸
                        int cnt = 1;
                        for(int k = 0; k < 3; k ++){
                            int nr = i + drow[k];
                            int nc = j + dcol[k];
                            if(boards[i][j] == boards[nr][nc]) {
                                cnt++;
                            }
                        }

                        if(cnt == 4) {
                            if(visit[i][j] == 0) {
                                removed.add(new Pair(i,j));
                                visit[i][j] = 1;
                            }
                            for(int k = 0; k < 3; k ++){
                                int nr = i + drow[k];
                                int nc = j + dcol[k];
                                if(visit[nr][nc] == 0) {
                                    removed.add(new Pair(nr,nc));
                                    visit[nr][nc] = 1;
                                }
                            }
                        }
                    }
                }

                if(removed.size() == 0) { // 더이상 지울 블록이 없음
                    break;
                }
                for(Pair pii : removed) { // 블록 지우기
                    boards[pii.first][pii.second] = '0';
                    answer++;
                }

                for(int j = 1; j <= n ; j++) {
                    for(int i = m; i >= 1; i--) {
                        if(boards[i][j] == '0') {
                            for(int k = i-1; k >= 1; k--) {
                                if(boards[k][j] != '0') {
                                    boards[i][j] = boards[k][j];
                                    boards[k][j] = '0';
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            return answer;
        }
    }
}
