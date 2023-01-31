package com.example.algorithm;

import java.util.*;
public class Lv2_다리를지나는트럭 {
    class Solution {

        class Truck {
            int time, weight;
            Truck(int time, int weight) {
                this.time = time;
                this.weight = weight;
            }
        }

        public int solution(int bridge_length, int weight, int[] truck_weights) {
            int answer = 0;

            Queue<Integer> stayQ = new LinkedList();
            Queue<Truck> bridgeQ = new LinkedList();

            for(int i : truck_weights) stayQ.add(i);

            int time = 0;
            int curWeight = 0;
            while(true) {
                if(bridgeQ.isEmpty() && stayQ.isEmpty()) {
                    break;
                }
                if(!bridgeQ.isEmpty() && time >= bridgeQ.peek().time + bridge_length) {
                    curWeight -= bridgeQ.poll().weight;
                }
                if(!stayQ.isEmpty() && curWeight + stayQ.peek() <= weight) {
                    int w = stayQ.poll();
                    curWeight += w;
                    bridgeQ.add(new Truck(time, w));
                }
                time++;
            }

            answer = time;
            return answer;
        }
    }
}
