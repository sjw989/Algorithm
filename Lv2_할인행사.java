package com.example.algorithm;

import java.util.*;
public class Lv2_할인행사 {
    class Solution {
        public int solution(String[] want, int[] number, String[] discount) {
            int answer = 0;
            Map<String,Integer> wantMap = new HashMap();
            for(int i = 0 ; i < want.length; i++) {
                wantMap.put(want[i], number[i]);
            }

            Map<String,Integer> saleMap = new HashMap();
            for(int i = 0; i <= discount.length - 10; i++) {
                for(int j = 0 ; j < 10; j++) {
                    String food = discount[i+j];
                    if(saleMap.containsKey(food)) {
                        saleMap.put(food, saleMap.get(food) + 1);
                    }
                    else {
                        saleMap.put(food, 1);
                    }
                }
                if(wantMap.equals(saleMap)) {
                    System.out.println(i);
                    answer++;
                }
                saleMap.clear();
            }

            return answer;
        }
    }
}
