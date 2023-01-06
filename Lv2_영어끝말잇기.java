package com.example.algorithm;

import java.util.HashMap;

public class Lv2_영어끝말잇기 {
    public int[] solution(int n, String[] words) {
        int[] answer = new int[2];
        int[] turn = new int[11];
        HashMap<String, Boolean> used = new HashMap();
        int user = 1;
        for (int i = 0; i < words.length; i++) {
            if (used.containsKey(words[i]) && used.get(words[i])) {
                answer[0] = user;
                answer[1] = ++turn[user];
                break;
            } else {
                if (i > 0 && words[i].charAt(0) != words[i - 1].charAt(words[i - 1].length() - 1)) {
                    answer[0] = user;
                    answer[1] = ++turn[user];
                    break;
                }
                used.put(words[i], true);
                turn[user]++;
                user++;
                if (user > n) {
                    user = 1;
                }
            }
        }
        return answer;

    }
}
