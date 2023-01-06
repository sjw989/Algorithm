package com.example.algorithm;

import java.util.HashMap;
public class Lv2_N개의최소공배수 {
    public int solution(int[] arr) {
        int answer = 0;
        HashMap<Integer,Integer> map = new HashMap();
        for(int i = 0 ; i < arr.length; i ++){
            int n = arr[i];
            if(!map.containsKey(n)){
                map.put(n, 1);
            }
            else {
                int value = map.get(n);
                map.put(n,value + 1);
            }
            if(map.get(n) == arr.length) {
                answer = n;
                return answer;
            }
        }
        int weight = 2;
        while(true) {
            for(int i = 0 ; i < arr.length; i ++){
                int cur = arr[i];
                int next = cur * weight;
                if(!map.containsKey(next)){
                    map.put(next, 1);
                }
                else {
                    int value = map.get(next);
                    map.put(next,value + 1);
                }
                if(map.get(next) == arr.length) {
                    answer = next;
                    return answer;
                }
            }
            weight++;
        }
    }
}
