package com.example.algorithm;

import java.util.*;
public class Lv2_주식가격 {
    class Solution {

        class Pair {
            int first;
            int second;
            Pair(int first, int second) {
                this.first = first;
                this.second = second;
            }
        }

        public int[] solution(int[] prices) {
            int[] answer = new int[prices.length];
            Stack<Pair> st = new Stack();

            for(int i = 0; i < prices.length; i++) {
                int price = prices[i];
                if(st.empty()) {
                    Pair pii = new Pair(i, price);
                    st.add(pii);
                }
                else {
                    while(true) {
                        if(st.empty()) {
                            st.add(new Pair(i,price));
                            break;
                        }
                        if(st.peek().second > price) { // 하락장
                            answer[st.peek().first] = i - st.peek().first;
                            st.pop();
                        }
                        else {
                            st.add(new Pair(i, price));
                            break;
                        }
                    }
                }
            }
            int size = st.size();
            for(int i = 0 ; i < size; i++) {
                Pair pii = st.pop();
                //System.out.println( pii.first + " " + pii.second);
                answer[pii.first] = prices.length - (pii.first + 1);
            }
            return answer;
        }
    }

}
