package com.example.algorithm;

public class Lv2_다음큰숫자 {
    public int getBinaryOneCount(int n) {
        String binary = Integer.toBinaryString(n);
        int cnt = 0;
        for(int i = 0 ; i < binary.length(); i++){
            if(binary.charAt(i) == '1') {
                cnt++;
            }
        }
        return cnt;
    }

    public int solution(int n) {
        int answer = 0;
        int nCount = getBinaryOneCount(n);
        int ans = n+1;
        while(true) {
            System.out.println(ans);
            int ansCount = getBinaryOneCount(ans);
            if (nCount == ansCount) {
                answer = ans;
                break;
            }
            ans++;
        }


        return answer;
    }
}
