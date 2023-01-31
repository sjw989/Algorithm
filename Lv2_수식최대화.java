package com.example.algorithm;

import java.util.*;
public class Lv2_수식최대화 {
    class Solution {

        long ans = 0;
        String[] priority = {"*+-", "*-+", "+-*", "+*-", "-+*", "-*+"};

        ArrayList<String> getExpressionList(String expression) {
            long l = 0;
            ArrayList<String> expressionList = new ArrayList();
            for(int i = 0 ; i < expression.length(); i++) {
                char c = expression.charAt(i);
                if(c == '+' || c == '-' || c=='*') {
                    expressionList.add(String.valueOf(l));
                    expressionList.add(String.valueOf(c));
                    l = 0;
                }
                else {
                    l = 10*l + Long.valueOf(c - '0');
                }
            }
            expressionList.add(String.valueOf(l));
            return expressionList;
        }
        ArrayList<String> calculate(ArrayList<String> expressionList, String operation) {
            ArrayList<String> newExpressionList = new ArrayList();

            for(int i = 0 ; i < expressionList.size(); i++) {

                if(expressionList.get(i).equals(operation)) {
                    long prev = Long.valueOf(newExpressionList.get(newExpressionList.size()-1));
                    long next = Long.valueOf(expressionList.get(i+1));
                    newExpressionList.remove(newExpressionList.size()-1);
                    if(operation.equals("+")){
                        newExpressionList.add(String.valueOf(prev+next));
                    }
                    else if(operation.equals("-")) {
                        newExpressionList.add(String.valueOf(prev-next));
                    }
                    else {
                        newExpressionList.add(String.valueOf(prev*next));
                    }
                    i++;
                }
                else {
                    newExpressionList.add(expressionList.get(i));
                }
            }

            return newExpressionList;

        }

        public long solution(String expression) {
            long answer = 0;
            for(String prio : priority) {
                ArrayList<String> expressionList = getExpressionList(expression);
                for(int i = 0 ; i < prio.length(); i++) {
                    String operator = String.valueOf(prio.charAt(i));
                    if(expressionList.contains(operator)) {
                        expressionList = calculate(expressionList, operator);
                    }
                }
                long result = Math.abs(Long.valueOf(expressionList.get(0)));
                if(ans < result) ans = result;
            }
            answer = ans;
            return answer;
        }
    }
}
