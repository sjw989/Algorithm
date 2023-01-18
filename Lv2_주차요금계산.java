package com.example.algorithm;

import java.util.*;
public class Lv2_주차요금계산 {
    class Solution {
        public int[] solution(int[] fees, String[] records) {
            int[] answer = {};
            ArrayList<String[]> record = new ArrayList();
            for(String r : records) record.add(r.split(" "));
            Collections.sort(record, (String[] s1, String s2[])
                    -> Integer.valueOf(s1[1]) - Integer.valueOf(s2[1]));
            for(int i = 0 ; i < record.size(); i++) {
                String[] rec = record.get(i);
                rec[0] = rec[0].replace(":", "");
                rec[0] = String.valueOf(Integer.valueOf(rec[0].substring(0,2))*60
                        + Integer.valueOf(rec[0].substring(2,4)));
                record.set(i,rec);
            }

            ArrayList<String[]> updatedRecord = new ArrayList();
            for(int i = 0 ; i < record.size(); i++){
                String[] rec = record.get(i);
                updatedRecord.add(rec);
                if((i < record.size() - 1 && rec[2].equals("IN") && record.get(i+1)[2].equals("IN"))
                        || (i == record.size() - 1 && rec[2].equals("IN"))) {
                    String[] newRec = new String[3];
                    newRec[0] = String.valueOf(23*60 + 59);
                    newRec[1] = rec[1];
                    newRec[2] = "OUT";
                    updatedRecord.add(newRec);
                }
            }

            ArrayList<String> keyList = new ArrayList();
            Map<String,Integer> timeMap = new HashMap();
            for(int i = 0 ; i < updatedRecord.size(); i++) {
                String[] rec = updatedRecord.get(i);
                if(i == 0) keyList.add(rec[1]);
                else {
                    if(!rec[1].equals(updatedRecord.get(i-1)[1])) {
                        keyList.add(rec[1]);
                    }
                }
                int time = 0;
                if(rec[2].equals("IN")) {
                    time = (-1)*Integer.valueOf(rec[0]);
                }
                else {
                    time = Integer.valueOf(rec[0]);
                }
                if(timeMap.containsKey(rec[1])) {
                    timeMap.put(rec[1], timeMap.get(rec[1]) + time);
                }
                else {
                    timeMap.put(rec[1], time);
                }
            }

            answer = new int[keyList.size()];
            for(int i = 0 ; i < keyList.size(); i++) {
                int time = timeMap.get(keyList.get(i));
                int fee = 0;
                if(time <= fees[0]) {
                    fee = fees[1];
                }
                else {
                    int extraTime = time - fees[0];
                    int extraFee = 0;
                    if(extraTime % fees[2] == 0) {
                        extraFee = extraTime / fees[2] * fees[3];
                    }
                    else {
                        extraFee = ((extraTime / fees[2]) + 1) * fees[3];
                    }
                    fee = fees[1] + extraFee;
                }
                answer[i] = fee;
            }


            return answer;
        }
    }
}
