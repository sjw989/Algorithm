package com.example.algorithm;

import java.util.*;
public class Lv2_오픈채팅방 {
    class Solution {

        Map<String,String> nameMap = new HashMap();

        public String[] solution(String[] record) {
            String[] answer = {};
            ArrayList<String[]> res = new ArrayList();
            for(String rec : record) {
                String[] log = rec.split(" ");
                String[] str = new String[2];
                str[0] = log[1];
                switch(log[0]) {
                    case "Enter" :
                        str[1] = "님이 들어왔습니다.";
                        nameMap.put(log[1], log[2]);
                        res.add(str);
                        break;
                    case "Leave" :
                        str[1] = "님이 나갔습니다.";
                        //nameMap.remove(log[1]);
                        res.add(str);
                        break;
                    case "Change" :
                        nameMap.replace(log[1], log[2]);
                        break;
                }
            }
            answer = new String[res.size()];
            for(int i = 0 ; i < res.size(); i++) {
                answer[i] = nameMap.get(res.get(i)[0]) + res.get(i)[1];
            }

            return answer;
        }
    }
}
