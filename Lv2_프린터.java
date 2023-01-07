package com.example.algorithm;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

public class Lv2_프린터 {
    class Doc {
        int prio;
        int num;

        Doc(int p, int n) {
            this.prio = p;
            this.num = n;
        }
    }

    public int solution(int[] priorities, int location) {
        int answer = 0;
        Queue<Doc> q = new LinkedList();
        for (int i = 0; i < priorities.length; i++) {
            q.offer(new Doc(priorities[i], i));
        }
        int cnt = 1;
        while (!q.isEmpty()) {
            Doc cur = q.poll();
            boolean isFirst = true;
            Iterator<Doc> it = q.iterator();
            while (it.hasNext()) {
                Doc next = it.next();
                if (cur.prio < next.prio) {
                    isFirst = false;
                    break;
                }
            }
            if (!isFirst) {
                q.offer(cur);
            } else {
                if (cur.num == location) {
                    answer = cnt;
                    break;
                }
                cnt++;
            }
        }
        return answer;
    }
}
