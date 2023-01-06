package com.example.algorithm;

import android.os.Build;

import androidx.annotation.RequiresApi;

import java.util.ArrayList;
import java.util.Comparator;

public class Lv2_최솟값만들기 {
    @RequiresApi(api = Build.VERSION_CODES.N)
    public int solution(int[] A, int[] B) {
        int answer = 0;

        ArrayList<Integer> a = new ArrayList();
        ArrayList<Integer> b = new ArrayList();
        for (int i = 0; i < A.length; i++) {
            a.add(A[i]);
            b.add(B[i]);
        }

        a.sort(Comparator.naturalOrder());
        b.sort(Comparator.reverseOrder());

        for (int i = 0; i < a.size(); i++) {
            answer += a.get(i) * b.get(i);
        }

        return answer;
    }
}
