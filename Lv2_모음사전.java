package com.example.algorithm;

import java.util.*;
public class Lv2_모음사전 {
    class Solution {

        String[] strArr = {"A","E","I","O","U"};
        ArrayList<String> dic = new ArrayList();
        void dfs(String w) {
            dic.add(w);
            if(w.length() == 5) return;
            for(int i = 0 ; i < 5; i++) {
                dfs(w + strArr[i]);
            }
        }

        public int solution(String word) {
            int answer = 0;
            for(int i = 0 ; i < strArr.length; i++) {
                dfs(strArr[i]);
            }
            for(int i = 0 ; i < dic.size(); i++) {
                if(word.equals(dic.get(i))) {
                    answer = i + 1;
                    break;
                }
            }
            return answer;
        }
    }
}
