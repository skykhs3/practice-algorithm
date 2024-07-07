#include <bits/stdc++.h>
using namespace std;

int getSum(int s, int e, vector<int>& sumA) {
    if (s == 0) return sumA[e];
    else return sumA[e] - sumA[s - 1];
}

int getAB(int y1, int x1, int y2, int x2, vector<vector<int>>& sumAB) {
    if (y1 > y2 || x1 > x2) return 0;
    int sum = sumAB[y2][x2];
    sum += (y1 > 0 && x1 > 0) ? sumAB[y1 - 1][x1 - 1] : 0;
    sum -= (y1 > 0) ? sumAB[y1 - 1][x2] : 0;
    sum -= (x1 > 0) ? sumAB[y2][x1 - 1] : 0;
    return sum;
}

void update(int y, int x, vector<vector<int>>& sumAB, int aij) {
    sumAB[y][x] = aij;
    sumAB[y][x] += (y > 0) ? sumAB[y - 1][x] : 0;
    sumAB[y][x] += (x > 0) ? sumAB[y][x - 1] : 0;
    sumAB[y][x] -= (y > 0 && x > 0) ? sumAB[y - 1][x - 1] : 0;
}
vector<vector<int>> sumAB(3000+1,vector<int>(3000+1));

void solution() {
    int n, k;
    scanf("%d%d",&n,&k);
    vector<int> a(n + 1), b(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    vector<int> sxY(n+1,1);
    vector<int> sumOfDeckY(n+1);
    vector<int> sumOfDpY(n+1);
    
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);

    int ans = 0;
    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
        sumAB[i][j]=sumAB[i-1][j]+sumAB[i][j-1]-sumAB[i-1][j-1];
      }
    }

    for (int i = 0; i <= n; i++) {
        int sumOfDeckX=0,sx=1,sumOfDpX=0; // 0의 갯수.
        for (int j = 0; j <= n; j++) {
          if(i==0 && j==0) dp[i][j]=1;
          else{
            if(j!=0){
              sumOfDeckX+=b[j];
              sumOfDpX+=1-dp[i][j-1];
              while(sumOfDeckX>k){
                sumOfDeckX-=b[sx];
                sumOfDpX-=1-dp[i][sx-1];
                sx++;
              }
            }
            if(i!=0){
              sumOfDeckY[j]+=a[i];
              sumOfDpY[j]+=1-dp[i-1][j];
              while(sumOfDeckY[j]>k){
                sumOfDeckY[j]-=a[sxY[j]];
                sumOfDpY[j]-=1-dp[sxY[j]-1][j];
                sxY[j]++;
              }
            }
            if(sumOfDpY[j]!=0 || sumOfDpX!=0) dp[i][j]=1;
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
