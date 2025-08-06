#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll oo=999999999999LL;
void solution(){
  ll n,a,b;
  scanf("%lld %lld %lld",&n,&a,&b);
  vector<ll> dp(n+10,-oo);
  dp[0]=0;
  for(int i=1;i<=n;i++){
    if(i-a>=0 && dp[i]<dp[i-a]+1) dp[i]=dp[i-a]+1;
    if(i-b>=0 && dp[i]<dp[i-b]+1) dp[i]=dp[i-b]+1;
  }
  printf("%lld\n",dp[n]);
}
int main(){
  ll t;
  scanf("%lld",&t);
  for(ll i=0;i<t;i++){
    printf("Case #%lld\n",i+1);
    solution();
  }
  return 0;
}