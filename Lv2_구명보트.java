package com.example.algorithm;

import java.util.Arrays;
public class Lv2_구명보트 {
    public int solution(int[] people, int limit) {
        int answer = 0;
        Arrays.sort(people);
        int left = 0;
        int right = people.length - 1;
        while(left <= right) {
            int lw = people[left];
            int rw = people[right];
            if(lw + rw <= limit) {
                left++;
            }
            right--;
            answer++;
        }
        return answer;
    }
}
