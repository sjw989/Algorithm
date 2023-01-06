package com.example.algorithm;

public class Lv2_카펫 {
    public int[] solution(int brown, int yellow) {
        int[] answer = new int[2];

        for(int i = 1; i <= yellow; i++) {
            int row = i; // 세로 1
            int col = yellow / row; // 가로 2

            if(2*(col+2) + 2*row == brown) {
                if(col + 2 >= row + 2) {
                    answer[0] = col + 2;
                    answer[1] = row + 2;
                }
                else break;
            }
        }
        return answer;
    }
}
