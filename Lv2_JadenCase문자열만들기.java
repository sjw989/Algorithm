package com.example.algorithm;

import java.util.ArrayList;
import java.util.Arrays;

public class Lv2_JadenCase문자열만들기 {

    public String solution(String s) {
        String answer = "";
        boolean isFirst = true;
        for(int i = 0 ; i < s.length();i++){
            char c = s.charAt(i);
            if(c == ' ') {
                answer += ' ';
                isFirst= true;
            }
            else if (c - '0' > 0 && c - '0' < 9) {
                isFirst = false;
                answer += c;
            }
            else {
                if(isFirst) {
                    answer += Character.toString(c).toUpperCase();
                    isFirst = false;
                }
                else {
                    answer += Character.toString(c).toLowerCase();;
                }
            }
        }

        return answer;
    }
}
