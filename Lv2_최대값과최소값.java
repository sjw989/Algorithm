package com.example.algorithm;

import java.util.Collections;
import java.util.ArrayList;

public class Lv2_최대값과최소값 {

    public String solution(String s) {
        String answer = "";
        ArrayList<Integer> numbers = new ArrayList<Integer>();
        Boolean isNegative = false;
        int number = 0;

        // "1 2 3 4"
        for(int i = 0 ; i < s.length(); i++){
            char c = s.charAt(i);
            switch(c) {
                case '-' :
                    isNegative = true;
                    break;
                case ' ' :
                    if(isNegative) {
                        number = number * -1;
                        isNegative = false;
                    }
                    numbers.add(number);
                    number = 0;
                    break;
                default :
                    number = number*10 + (c - '0');
                    break;
            }
        }
        if(isNegative) {
            number = number* - 1;
        }
        numbers.add(number);
        int min = Collections.min(numbers);
        int max = Collections.max(numbers);
        System.out.println(numbers);
        answer = min + " " + max;
        return answer;
    }
}
