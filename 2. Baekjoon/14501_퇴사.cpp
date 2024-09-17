#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
  ll N;
  cin>>N;
  vector<ll> P(N+2),T(N+2),dp(N+2);

  for(ll i=1;i<=N;i++)
    cin>>T[i]>>P[i];
  
  for(ll i=1;i<=N+1;i++){
    dp[i]=max(dp[i],dp[i-1]);
    if(i+T[i]<=N+1 && dp[i+T[i]]<dp[i]+P[i])
      dp[i+T[i]]=dp[i]+P[i];
  }

  cout<<dp[N+1];
}