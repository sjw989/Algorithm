package com.example.algorithm;

public class Lv2_n2배열자르기 {

    public int longToInt(Long n) {
        return Long.valueOf(n).intValue();
    }

    public int[] solution(int n, long left, long right) {
        int[] answer = {};
        answer = new int[longToInt(right - left) + 1];
        for (long i = left; i <= right; i++) {
            long row = i / n;
            long col = i % n;

            row++;
            col++;

            int idx = longToInt(i - left);
            answer[idx] = longToInt(Math.max(row, col));
        }
        return answer;
    }


/*
   n = 3, left = 2, right = 5
   i = 2  row = 0 , col = 2
   i = 3  row = 1, col = 0
   i = 4  row = 1, col = 1
   i = 5  row = 1, col = 2

   1 2 3
   2 2 3
   3 3 3



   1  2  3  4  5
   2  2  3  4  5
   3  3  3  4  5
   4  4  4  4  5
   5  5  5  5  5
   n = 4
   value = max(row, col)
   left = 6 --> [left / n][left % n ]
                    1         1
   right = 25 --> [right / n] [right % n ]
                    5          0
*/
}
