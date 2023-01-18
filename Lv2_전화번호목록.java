package com.example.algorithm;

import java.util.*;
public class Lv2_전화번호목록 {
    class Solution {
        public boolean solution(String[] phone_book) {
            boolean answer = true;
            HashMap<String,Integer> map = new HashMap();
            Arrays.sort(phone_book, (String s1, String s2) -> s1.length() - s2.length());
            for(String str : phone_book) {
                String key = "";
                for(int i = 0 ; i < str.length(); i ++){
                    key += String.valueOf(str.charAt(i));
                    if(map.containsKey(key)) {
                        answer = false;
                        return answer;
                    }
                }
                map.put(str, 0);
            }
            return answer;
        }
    }
}
