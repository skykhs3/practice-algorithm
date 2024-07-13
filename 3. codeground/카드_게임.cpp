#include <bits/stdc++.h>
using namespace std;

void solution() {
    int n, k;
    scanf("%d%d",&n,&k);
    vector<int> a(n + 1), b(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    vector<int> sxY(n+1,1);
    vector<int> sumOfDeckY(n+1);
    vector<int> sumOfZeroY(n+1);
    
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    int ans = 0;

    for (int i = 0; i <= n; i++) {
        int sumOfDeckX=0,sx=1,sumOfZeroX=0; // 0의 갯수.
        for (int j = 0; j <= n; j++) {
          if(i==0 && j==0) dp[i][j]=1;
          else{
            if(j!=0){
              sumOfDeckX+=b[j];
              sumOfZeroX+=1-dp[i][j-1];
              while(sumOfDeckX>k){
                sumOfDeckX-=b[sx];
                sumOfZeroX-=1-dp[i][sx-1];
                sx++;
              }
            }
            if(i!=0){
              sumOfDeckY[j]+=a[i];
              sumOfZeroY[j]+=1-dp[i-1][j];
              while(sumOfDeckY[j]>k){
                sumOfDeckY[j]-=a[sxY[j]];
                sumOfZeroY[j]-=1-dp[sxY[j]-1][j];
                sxY[j]++;
              }
            }
            if(sumOfZeroY[j]!=0 || sumOfZeroX!=0) dp[i][j]=1;
          }
        }
    }

    for(int i=0;i<=n;i++){
      for(int j=0;j<=n;j++)
        if(dp[i][j]) ans++;
    }
    printf("%d %d\n",ans,(n + 1) * (n + 1) - ans );
}

int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d",&T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d\n",i);
        solution();
    }
    return 0;
}
