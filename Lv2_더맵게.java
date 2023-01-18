package com.example.algorithm;

import java.util.*;
public class Lv2_더맵게 {
    class Solution {
        public int solution(int[] scoville, int K) {
            int answer = 0;

            PriorityQueue<Integer> pq = new PriorityQueue();

            for(int s : scoville) {
                pq.add(s);
            }

            while(pq.peek() < K) {
                if(pq.size() == 1) return -1;
                int first = pq.poll();
                int second = pq.poll();
                int newScoville = first + (second * 2);
                pq.add(newScoville);
                answer++;
            }
            return answer;
        }
    }
}
