#include <stdio.h>
#include <vector>
using namespace std;

typedef long long ll;
ll dp[50][2]={{1,0},{0,1}};
int main(){
  for(int i=2;i<=40;i++){
    dp[i][0]=dp[i-1][0]+dp[i-2][0];
    dp[i][1]=dp[i-1][1]+dp[i-2][1];
  }
  ll n;
  scanf("%lld",&n);
  for(int i=0;i<n;i++){
    int y;
    scanf("%d",&y);
    printf("%lld %lld\n",dp[y][0],dp[y][1]);
  }
}