package com.example.algorithm;

import java.util.*;
public class Lv2_가장큰수 {
    class Solution {
        public String solution(int[] numbers) {
            String answer = "";
            ArrayList<String> strArr = new ArrayList();
            for(int i = 0 ; i < numbers.length; i++) {
                strArr.add(String.valueOf(numbers[i]));
            }

            Collections.sort(strArr, new Comparator<String>() {
                @Override
                public int compare(String s1, String s2) {
                    int a = Integer.valueOf(s1+s2);
                    int b = Integer.valueOf(s2+s1);
                    if(a < b) {
                        return 1;
                    }
                    else if(b == a) {
                        return 0;
                    }
                    else {
                        return -1;
                    }
                    // int a = Integer.valueOf(s1+s2);
                    // int b = Integer.valueOf(s2+s1);
                    // if(a < b) {
                    //     return 1;
                    // }
                    // else if( a == b) return 0;
                    // return -1;
                }
            });

            if(strArr.get(0).charAt(0) == '0') {
                return "0";
            }

            for(String str : strArr) {
                answer += str;
            }

            return answer;
        }
    }
}
