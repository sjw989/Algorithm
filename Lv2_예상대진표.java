package com.example.algorithm;

public class Lv2_예상대진표 {
    /*
              3,4                              11,12
       3,4.          5,6.            11,12               15,16
   1,2    3,4    5,6     7,8     9,10.    11,12.    13,14.    15,16
   */
    public int solution(int n, int a, int b)
    {
//         int answer = 0;
//         Queue<Integer> q = new LinkedList();
//         for(int i = 1; i <= n ; i++){
//             q.offer(i);
//         }
//         answer = 1;
//         while(q.size() != 1) {
//             for(int i = 0 ; i < n / Math.pow(2,answer); i++) {
//                 int f = q.poll();
//                 int s = q.poll();

//                 if( (f == a && s == b) || (f == b && s == a))  { //정답인 경우
//                     return answer;
//                 }
//                 if(f == a || f == b) {
//                     q.offer(f);
//                 }
//                 else if( s==a || s == b) {
//                     q.offer(s);
//                 }
//                 else {
//                     q.offer(f);
//                 }
//             }
//             answer++;
//         }


//         return answer;
        return Integer.toBinaryString((a-1)^(b-1)).length();
    }
}
