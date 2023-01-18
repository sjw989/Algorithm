package com.example.algorithm;
import java.util.*;
public class Lv2_괄호회전하기 {
    public boolean isAnswer(String s) {
        Stack<Character> st = new Stack();
        for(int i = 0 ; i < s.length(); i ++){
            char c = s.charAt(i);
            switch(c) {
                case '}' :
                    if(st.size() > 0 && st.peek() == '{') {
                        st.pop();
                    }
                    else st.push(c);
                    break;
                case ')' :
                    if(st.size() > 0 && st.peek() == '(') {
                        st.pop();
                    }
                    else st.push(c);
                    break;
                case ']' :
                    if(st.size() > 0 && st.peek() == '[') {
                        st.pop();
                    }
                    else st.push(c);
                    break;
                default :
                    st.push(c);
                    break;
            }
        }
        if(st.empty()) return true;
        return false;
    }

    public String rotate(int n, String s) {
        String newString = "";
        newString = s.substring(n,s.length()) + s.substring(0,n) ;
        return newString;
    }

    public int solution(String s) {
        int answer = 0;
        for(int i = 0 ; i < s.length(); i++) {
            String newString = rotate(i,s);
            if(isAnswer(newString)) {
                answer++;
            }
        }
        return answer;
    }
}
