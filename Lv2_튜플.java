package com.example.algorithm;
import java.util.*;
public class Lv2_튜플 {
    public ArrayList<ArrayList<Integer>> getSetList(String s) {
        ArrayList<ArrayList<Integer>> setList = new ArrayList();
        ArrayList<Integer> set = new ArrayList();
        int n = 0;
        for(int i = 1; i < s.length() - 1; i++) {
            char c = s.charAt(i);
            if(c - '0' >= 0 && c - '0' <= 9) {
                n = n*10 + (c-'0');
            }
            else if(c == '}') {
                if( n > 0 ) {
                    set.add(n);
                    n = 0;
                }
                setList.add(set);
                set = new ArrayList();
            }
            else if(c == ',' && n > 0) {
                set.add(n);
                n = 0;
            }
        }
        return setList;
    }

    public int[] solution(String s) {
        int[] answer = {};
        int[] visit = new int[100001];
        ArrayList<ArrayList<Integer>> setList = getSetList(s);
        Collections.sort(setList, (l1,l2) -> l1.size() - l2.size());
        answer = new int[setList.get(setList.size()-1).size()];
        int idx = 0;
        for(ArrayList<Integer> set : setList) {
            for(Integer n : set) {
                if(visit[n] != 1) {
                    answer[idx] = n;
                    idx++;
                    visit[n] = 1;
                }
            }
        }
        return answer;
    }
}
