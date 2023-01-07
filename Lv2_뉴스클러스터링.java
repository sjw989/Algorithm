package com.example.algorithm;

import java.util.*;
public class Lv2_뉴스클러스터링 {

    public ArrayList<String> getStringList(String str) {
        ArrayList<String> arr = new ArrayList();
        for(int i = 0 ; i < str.length() - 1; i++) {
            char cur = str.charAt(i);
            char next = str.charAt(i+1);

            if(cur >= 'a' && cur <= 'z'
                    && next >= 'a' && next <= 'z' ) {
                arr.add(String.valueOf(cur) + String.valueOf(next));
            }
        }
        return arr;
    }

    public int solution(String str1, String str2) {
        int answer = 0;
        ArrayList<String> arr1 = getStringList(str1.toLowerCase());
        ArrayList<String> arr2 = getStringList(str2.toLowerCase());
        int arr2Size = arr2.size();

        ArrayList<String> intersectList = new ArrayList();
        for(int i = 0; i < arr1.size(); i ++) {
            String s = arr1.get(i);
            if(arr2.contains(s)) {
                arr2.remove(s);
                intersectList.add(s);
            }
        }

        int intersection = intersectList.size();
        int union = arr1.size() + arr2Size - intersection;
        if(intersection == 0 && union == 0) answer = 65536;
        else {
            Double d = Double.valueOf(intersection) / Double.valueOf(union);
            d = d * 65536.0;
            answer = d.intValue();
        }
        return answer;
    }
}
