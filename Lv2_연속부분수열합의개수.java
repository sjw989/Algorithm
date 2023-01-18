package com.example.algorithm;

import java.util.*;
public class Lv2_연속부분수열합의개수 {
    class Solution {
        public int solution(int[] elements) {
            int answer = 0;
            Set<Integer> set = new HashSet();

            for(int length = 1; length <= elements.length; length++) {
                for(int i = 0 ; i < elements.length; i++) { // 가능한 시작위치
                    int cnt = 0;
                    int n = 0;
                    int idx = i;
                    while(cnt < length) {
                        if(idx >= elements.length) {
                            idx = 0;
                        }
                        n += elements[idx];
                        cnt++;
                        idx++;
                    }
                    set.add(n);
                }
            }
            answer = set.size();
            return answer;
        }
    }
}
