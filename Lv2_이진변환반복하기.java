package com.example.algorithm;

public class Lv2_이진변환반복하기 {

    public int[] solution(String s) {
        int[] answer = new int[2];
        int cnt = 0;
        int removed = 0;

        while(true ) {
            String q = "1";
            if(s == q) {
                System.out.println("same");
                break;
            }
            else {
                System.out.print("s : ");
                System.out.println(s);
            }
            if(s.equals(q)) {
                System.out.println("hihi");
            }
            String removedString = "";
            for(int i = 0 ; i < s.length(); i++) {
                char c = s.charAt(i);
                if(c != '0') { removedString += c; }
                else { removed++; }
            }
            int length = removedString.length();
            String newString = "";
            while(length != 0) {
                newString = (length % 2) + newString;
                length = length / 2;
            }
            cnt++;
            s = newString;
        }
        answer[0] = cnt;
        answer[1] = removed;
        System.out.println(answer[0]);
        System.out.println(answer[1]);
        return answer;
    }
}

/*
length = 4
1. newString = 0, length = 2
2. newString = 00 length = 1
3.

 */
