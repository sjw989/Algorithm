package com.example.algorithm;

import java.util.Stack;
public class Lv2_짝지어제거하기 {
    public int solution(String s)
    {
        int answer = 0;
        Stack<Character> st =  new Stack();
        for(int i = 0 ; i < s.length(); i++) {
            char c = s.charAt(i);
            if(st.empty()) {
                st.push(c);
                continue;
            }
            char top = st.peek();
            if(top == c) st.pop();
            else st.push(c);
        }
        if(st.empty()) answer = 1;
        return answer;
    }
}
