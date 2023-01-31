package com.example.algorithm;

import java.util.*;
public class Lv2_메뉴리뉴얼 {
    class Solution {

        ArrayList<String> list;
        int[] isCourse = new int[11];

        void dfs(int idx, String str, String cur) {
            if(isCourse[cur.length()] == 1) {
                list.add(cur);
            }

            for(int i = idx + 1; i < str.length(); i++) {
                dfs(i, str, cur + String.valueOf(str.charAt(i)));
            }
        }
        void getOrderCombination(String str) {
            list = new ArrayList();
            for(int i = 0 ; i < str.length(); i++) {
                dfs(i, str, String.valueOf(str.charAt(i)));
            }
        }

        public String[] solution(String[] orders, int[] course) {
            String[] answer = {};
            for(int n : course) {
                isCourse[n] = 1;
            }
            Map<String,Integer> map = new HashMap();
            for(String str : orders) {
                char[] strArr = str.toCharArray();
                Arrays.sort(strArr);
                getOrderCombination(new String(strArr));
                for(int i = 0 ; i < list.size(); i++) {
                    String key = list.get(i);
                    if(map.containsKey(key)) {
                        map.put(key, map.get(key) + 1);
                    }
                    else {
                        map.put(key, 1);
                    }
                }
            }

            ArrayList<SetMenu>[] menuCandidate = new ArrayList[11];
            for(int i = 0; i <= 10; i++) menuCandidate[i] = new ArrayList();
            for(String key : map.keySet()) {
                int cnt = map.get(key);
                if(cnt >= 2) {
                    menuCandidate[key.length()].add(new SetMenu(key, cnt));
                    //System.out.println(key.length());
                }
            }

            ArrayList<String> selectedMenu = new ArrayList();
            for(int n : course) {
                ArrayList<SetMenu> mList = menuCandidate[n];
                Collections.sort(mList, (SetMenu m1, SetMenu m2) -> m2.cnt - m1.cnt);
                ArrayList<SetMenu> menus = new ArrayList();
                for(int i = 0; i < mList.size(); i++) {
                    SetMenu m = mList.get(i);
                    if(menus.size() == 0) menus.add(m);
                    else {
                        if(menus.get(0).cnt == m.cnt) {
                            menus.add(m);
                        }
                        else if(menus.get(0).cnt < m.cnt) {
                            menus = new ArrayList();
                            menus.add(m);
                        }
                        else {
                            break;
                        }
                    }
                }
                for(int i = 0 ; i < menus.size(); i++) {
                    selectedMenu.add(menus.get(i).comb);
                }
            }
            Collections.sort(selectedMenu);
            answer = new String[selectedMenu.size()];
            // for(int i = 0 ; i < selectedMenu.size(); i++) {
            //         System.out.println(selectedMenu.get(i));
            // }
            for(int i = 0; i < answer.length ; i++) {
                answer[i] = selectedMenu.get(i);
            }

            return answer;
        }

        class SetMenu {
            String comb;
            int cnt;
            SetMenu(String comb, int cnt) {
                this.comb = comb;
                this.cnt = cnt;
            }
        }
    }
}
