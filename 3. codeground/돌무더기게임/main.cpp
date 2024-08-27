#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll solve(){
  ll n;
  scanf("%lld",&n);
  vector<ll> a(n+1);
  vector<vector<ll>> dp(n+2,vector<ll>(n+2));
  for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
  for(ll i=1;i<=n;i++) dp[i][i]=a[i];

  for(ll gap=2;gap<=n;gap++){
    for(ll s=1;s+gap-1<=n;s++){
      ll e=s+gap-1;
      for(ll k=s;k<=e;k++){
        if(dp[s][e]<a[k]+min(dp[s][k-1],dp[k+1][e])) dp[s][e]=a[k]+min(dp[s][k-1],dp[k+1][e]);
      }
    }
  }

  for(ll i=1;i<=n;i++){
    for(ll j=1;j<=n;j++){
      printf("%3lld ",dp[i][j]);
    }
    printf("\n");
  }

  return dp[1][n];
}

int main(){
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    printf("%lld\n",solve());
  }
  return 0;
}
