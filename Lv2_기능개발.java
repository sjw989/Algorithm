package com.example.algorithm;

import java.util.ArrayList;

public class Lv2_기능개발 {

    public int getCompleteDay(int p, int s) {
        int d = 1;
        while (true) {
            if (p + s * d >= 100) return d;
            d++;
        }
    }

    public int[] solution(int[] progresses, int[] speeds) {
        int[] answer = {};
        ArrayList<Integer> completeDay = new ArrayList();
        ArrayList<Integer> ans = new ArrayList();
        for (int i = 0; i < progresses.length; i++) {
            completeDay.add(getCompleteDay(progresses[i], speeds[i]));
        }
        int comp = completeDay.get(0);
        int cnt = 1;
        for (int i = 1; i < completeDay.size(); i++) {
            int n = completeDay.get(i);
            if (comp >= n) cnt++;
            else {
                ans.add(cnt);
                comp = n;
                cnt = 1;
            }
        }
        ans.add(cnt);
        answer = new int[ans.size()];
        for (int i = 0; i < ans.size(); i++) {
            answer[i] = ans.get(i);
        }
        System.out.println(completeDay);
        return answer;
    }
}
