package com.example.algorithm;

import java.util.*;
public class Lv2_스킬트리 {
    class Solution {
        public int solution(String skill, String[] skill_trees) {
            int answer = 0;
            Map<Character, Character> skillOrderMap = new HashMap();
            for(int i = 0; i < skill.length(); i++) {
                char c = skill.charAt(i);
                if(i==0) {
                    skillOrderMap.put(c, '0');
                } else {
                    skillOrderMap.put(c, skill.charAt(i-1));
                }
            }
            Map<Character, Boolean> getSkillMap = new HashMap();
            for(String curSkill : skill_trees) {
                boolean isAnswer = true;
                for(int i = 0 ; i < curSkill.length(); i++) {
                    char c = curSkill.charAt(i);

                    if(!skillOrderMap.containsKey(c)) {
                        continue;
                    }
                    else {
                        char prevSkill = skillOrderMap.get(c);
                        if(prevSkill == '0') {
                            getSkillMap.put(c, true);
                        } else {
                            if (!getSkillMap.containsKey(prevSkill)) {
                                isAnswer = false;
                                break;
                            }
                            else {
                                System.out.println(c + " " + prevSkill);
                                getSkillMap.put(c, true);
                            }
                        }
                    }
                }


                if(isAnswer) answer++;
                getSkillMap.clear();
            }
            return answer;
        }
    }
}
