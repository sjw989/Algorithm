#include <iostream>
#include <string>
#include <vector>
#define MAX_VALUE 150
using namespace std;

int dp[MAX_VALUE + 1][MAX_VALUE + 1]; // row = 알고력, col = 코딩력

void init(int alp, int cop) {
    for(int i = 0; i <= MAX_VALUE; i++){
        for(int j = 0;  j <= MAX_VALUE; j++){
            if(i <= alp && j <= cop) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = 987654321;
            }
        }
    }
    
    
}

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;
    int MAX_ALP, MAX_COP = 0;
    
    for(vector<int> prob : problems) {
        MAX_ALP = max(MAX_ALP,prob[0]);
        MAX_COP = max(MAX_COP,prob[1]);
    }
    
    init(alp,cop);
    
    if(MAX_ALP <= alp && MAX_COP <= cop) { return 0;}
    if(alp >= MAX_ALP) {alp = MAX_ALP;}
    if(cop >= MAX_COP) {cop = MAX_COP;}
    
    for(int i = alp; i <= MAX_ALP ; i ++){
        for(int j =cop; j <= MAX_COP; j++) {
            
            if( j + 1 <= MAX_COP ) {
                dp[i][j+1] = min(dp[i][j+1], dp[i][j] + 1);    
            }
            
            if( i + 1 <= MAX_ALP ) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);    
            }
            
            int cnt = 0;
            for(vector<int> prob : problems) {
                if( prob[0] <= i && prob[1] <= j ) {
                    cnt++;
                    int nextALP = min(i+prob[2], MAX_ALP);
                    int nextCOP = min(j+prob[3], MAX_COP);
                    dp[nextALP][nextCOP] = min(dp[nextALP][nextCOP], dp[i][j] + prob[4]);
                }
            }
            
            if(cnt == problems.size()) {
                return dp[MAX_ALP][MAX_COP];
            }        
        }
    }
}