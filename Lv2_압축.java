package com.example.algorithm;

import java.util.*;
public class Lv2_압축 {
    class Solution {

        HashMap<String,Integer> getInitialMap() {
            HashMap<String,Integer> map = new HashMap();
            // 97 ~ 122
            for(int i = 1; i <= 26; i++) {
                String key = String.valueOf((char)(i+64));
                int value = i;
                map.put(key,value);
            }
            return map;
        }

        public int[] solution(String msg) {
            int[] answer = {};
            ArrayList<Integer> arr = new ArrayList();
            HashMap<String, Integer> map = getInitialMap();
            // KAKAO
            int start = 0;
            int end = 0;

            for(int i = 0 ; i< msg.length(); i++) {
                for(int j = i+1; j <= msg.length(); j++) {
                    String subStr = msg.substring(i,j);
                    if(map.containsKey(subStr)) {
                        if(j == msg.length()){
                            arr.add(map.get(subStr));
                            i = j - 1;
                        }
                    }
                    else {
                        map.put(subStr, map.size() + 1);
                        String prevStr = msg.substring(i, j - 1);
                        arr.add(map.get(prevStr));

                        i = j - 2;
                        break;
                    }
                }
            }

            answer = new int[arr.size()];
            for(int i = 0 ; i < arr.size(); i++) {
                answer[i] = arr.get(i);
            }
            return answer;
        }
    }
}
