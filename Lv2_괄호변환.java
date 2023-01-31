package com.example.algorithm;

import java.util.*;
public class Lv2_괄호변환 {
    class Solution {

        boolean isBalancedString(String p) {
            int left = 0, right = 0;
            for(int i = 0 ; i < p.length(); i++) {
                char c = p.charAt(i);
                if(c == '(') left++;
                else right++;
            }
            if(left == right) return true;
            return false;
        }

        boolean isCorrectString(String p) {
            Stack<Character> st = new Stack();
            if(!isBalancedString(p)) return false;
            for(int i = 0 ; i < p.length(); i++) {
                char c = p.charAt(i);
                if(c == '(') st.add(c);
                else {
                    if(st.size() == 0) st.add(c);
                    else if(st.peek() == '(') st.pop();
                    else st.add(c);
                }
            }
            if(st.size() == 0) return true;
            return false;
        }

        String[] getDividedString(String p) {
            String[] strArr = {"",""};
            for(int i = 1; i <= p.length(); i++) {
                if(isBalancedString(p.substring(0,i))) {
                    strArr[0] = p.substring(0,i);
                    strArr[1] = p.substring(i,p.length());
                    break;
                }
            }
            return strArr;
        }

        String transformToCorrectString(String p) {
            if(p == "") return p;
            String[] strArr = getDividedString(p);
            String u = strArr[0], v = strArr[1];
            System.out.println("u: " + u + " v: " + v);
            if(isCorrectString(u)) {
                String transformedV = transformToCorrectString(v);
                //System.out.println(u + " " + transf)
                return u + transformedV;
            }
            String newStr = "(";
            newStr += transformToCorrectString(v);
            newStr += ")";
            //System.out.println(newStr);
            for(int i = 1; i < u.length() - 1; i++) {
                if(u.charAt(i) == '(') newStr += ")";
                else newStr += "(";
            }
            //System.out.println(newStr);
            return newStr;
        }


        public String solution(String p) {
            String answer = "";
            if(isCorrectString(p)) return p;
            answer = transformToCorrectString(p);
            return answer;
        }
    }
}
