package com.example.algorithm;

import java.util.*;
public class Lv2_귤고르기 {
    class Solution {
        public int solution(int k, int[] tangerine) {
            int answer = 0;
            HashMap<Integer, Integer> map = new HashMap();
            for(Integer n : tangerine) {
                if(!map.containsKey(n)) {
                    map.put(n, 1);
                }
                else {
                    map.put(n, map.get(n) + 1);
                }
            }

            ArrayList<Integer> arr = new ArrayList();
            for(int key : map.keySet()) {
                arr.add(map.get(key));
            }

            Collections.sort(arr);
            int cnt = 0;
            for(int i = arr.size() - 1; i >= 0; i--) {
                cnt += arr.get(i);
                if(cnt >= k) {
                    answer++;
                    break;
                }
                else {
                    answer++;
                }
            }

            return answer;
        }
    }
// 1 2 2 3 3 4 5 5
}
