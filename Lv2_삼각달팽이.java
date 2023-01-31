package com.example.algorithm;

import java.util.*;
public class Lv2_삼각달팽이 {
    class Solution {
        int[][] board = new int[1001][1001];

        public int[] solution(int n) {
            int[] answer = {};
            int left = 1, right = n, top = 1, bottom = n;
            int k = 1;
            while(top <= bottom) {

                // 좌하 대각선 채우기
                for(int i = top; i <= bottom; i++) {
                    board[i][left] = k;
                    k++;
                }
                top++;
                left++;

                // 가로 채우기
                for(int i = left; i <= right; i++) {
                    board[bottom][i] = k;
                    k++;
                }
                bottom--;
                right--;

                // 좌상 대각선 채우기
                int col = right;
                for(int i = bottom; i >= top; i--) {
                    board[i][col] = k;
                    k++;
                    col--;
                }
                right--;
                top++;
            }

            ArrayList<Integer> numList = new ArrayList();
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <=n; j++) {
                    if(board[i][j] == 0) break;
                    else numList.add(board[i][j]);
                }
            }
            answer = new int[numList.size()];
            for(int i = 0 ; i < answer.length; i++) {
                answer[i] = numList.get(i);
            }

            return answer;
        }
    }
}
