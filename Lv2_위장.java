package com.example.algorithm;

import java.util.ArrayList;
import java.util.HashMap;

public class Lv2_위장 {
    public int solution(String[][] clothes) {
        int answer = 1;
        HashMap<String, ArrayList<String>> hash = new HashMap();
        for (int i = 0; i < clothes.length; i++) {
            String[] set = clothes[i];
            if (hash.get(set[1]) == null) {
                ArrayList<String> arr = new ArrayList();
                arr.add(set[0]);
                hash.put(set[1], arr);
            } else {
                ArrayList<String> arr = hash.get(set[1]);
                if (!arr.contains(set[0])) {
                    arr.add(set[0]);
                    hash.replace(set[1], arr);
                }
            }
        }
        for (String key : hash.keySet()) {
            answer *= hash.get(key).size() + 1;
        }
        return answer - 1;

    }
/*
 (a+b+c+d) + (ab + ac + ad + bc + bd +cd) + (abc + abd + bcd) + abcd
 (x+a)(x+b)(x+c)(x+d)
 */
}
