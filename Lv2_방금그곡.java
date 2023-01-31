package com.example.algorithm;

import java.util.*;
public class Lv2_방금그곡 {
    class Solution {
        ArrayList<String> getInfo(String melody) {
            ArrayList<String> info = new ArrayList();
            for(int i = 0 ; i < melody.length(); i++) {
                if(i < melody.length() - 1) {
                    if(melody.charAt(i+1) == '#') {
                        info.add(melody.substring(i,i+2));
                        i++;
                    }
                    else {
                        info.add(String.valueOf(melody.charAt(i)));
                    }
                }
                else {
                    info.add(String.valueOf(melody.charAt(i)));
                }
            }
            return info;
        }
        ArrayList<String> getPlayed(ArrayList<String> info, int time) {
            ArrayList<String> played = new ArrayList();
            for(int i = 0 ; i < time; i ++) {
                if(i >= info.size()) {
                    played.add(info.get(i % info.size()));
                }
                else {
                    played.add(info.get(i));
                }
            }
            return played;
        }

        boolean isAnswer(ArrayList<String> played, ArrayList<String> heard) {
            for(int i = 0 ; i < played.size(); i++) {
                if(played.get(i).equals(heard.get(0))) { // 시작 가능 위치
                    if(i + heard.size() <= played.size()) {
                        if(played.subList(i,i+heard.size()).equals(heard)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        public String solution(String m, String[] musicinfos) {
            String answer = "";
            int playTime = 0;
            for(String str : musicinfos) {
                String[] strArr = str.split(",");
                String title = strArr[2];
                int start = Integer.valueOf(strArr[0].substring(0,2))*60+Integer.valueOf(strArr[0].substring(3,5));
                int end = Integer.valueOf(strArr[1].substring(0,2))*60+Integer.valueOf(strArr[1].substring(3,5));
                ArrayList<String> played = getPlayed(getInfo(strArr[3]), end-start);

                if(isAnswer(played, getInfo(m))) {
                    if(answer.equals("")) {
                        answer = title;
                        playTime = end - start;
                    }
                    else {
                        if(playTime < end - start) {
                            answer = title;
                            playTime = end - start;
                        }
                    }
                }
            }
            if(answer.equals("")) {
                answer = "(None)";
            }

            return answer;
        }
    }
}
