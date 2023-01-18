package com.example.algorithm;

import java.util.*;
public class Lv2_파일명정렬 {
    class Solution {

        class File  implements Comparable<File> {

            @Override
            public int compareTo(File f) {
                if (f.head.equals(this.head)) {
                    return this.number - f.number;
                }
                return this.head.compareTo(f.head);
            }
            String head;
            String original;
            int number;
            File(String head, int number, String original) {
                this.head = head;
                this.number = number;
                this.original = original;
            }
        }

        File getFile(String f)  {
            String h = "";
            int n = 0;
            String o = f;
            for(int i = 0 ; i < f.length(); i++) {
                char c = f.charAt(i);
                if(c - '0' >= 0 && c - '0' <= 9) {
                    h = f.substring(0,i).toUpperCase();
                    break;
                }
            }
            for(int i = h.length(); i < f.length(); i++) {
                char c = f.charAt(i);
                if(i == f.length() - 1) {
                    if(c - '0' >= 0 && c - '0' <= 9) {
                        n = Integer.valueOf(f.substring(h.length(), i+1));
                    }
                }
                if(!(c - '0' >= 0 && c - '0' <= 9)) {
                    n = Integer.valueOf(f.substring(h.length(), i));
                    break;
                }
            }
            return new File(h,n,o);
        }

        public String[] solution(String[] files) {
            String[] answer = {};
            ArrayList<File> fileList = new ArrayList();
            for(String f : files) {
                fileList.add(getFile(f));
            }
            Collections.sort(fileList);
            answer = new String[fileList.size()];
            for(int i = 0 ; i < answer.length; i++) {
                answer[i] = fileList.get(i).original;
            }
            return answer;
        }
    }
}
