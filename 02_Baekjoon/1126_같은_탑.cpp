#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll oo=987654321LL;
int main()
{
//  freopen("input.txt","r",stdin);
  ll N;
  scanf("%lld",&N);
  vector<ll> a(N+1);
  vector<vector<ll>> dp(N+1,vector<ll>(500000*2+10));
  for(ll i=1;i<=N;i++){
    scanf("%lld",&a[i]);
  }
  sort(a.begin()+1,a.end());
  ll buffer=500000;
  for(ll i=0;i<=buffer*2;i++)
    for(ll j=0;j<=N;j++) dp[j][i]=-oo;
  dp[0][buffer]=0;

  for(ll i=1;i<=N;i++){
      for(ll j=0;j<=buffer*2;j++){
        dp[i][j]=max(dp[i][j],dp[i-1][j]);
        if(j+a[i]<=2*buffer && dp[i-1][j]+a[i]>dp[i][j+a[i]]){
          dp[i][j+a[i]]=dp[i-1][j]+a[i];
        }
        if(j-a[i]>=0 && dp[i-1][j]>dp[i][j-a[i]]){
          dp[i][j-a[i]]=dp[i-1][j];
        }
      }
  }
//  printf("%lld\n",dp[7][-27+buffer]);
  if(dp[N][buffer]<=0) printf("-1");
  else printf("%lld",dp[N][buffer]);
}
