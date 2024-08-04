#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll oo=300000000000LL;
ll change(ll from,ll to,ll S,ll E){
  if(from==to) return 0;
  if(to==1) return S;
  return E;
}
void solve(){
  ll N,S,E;
  cin>>N>>S>>E;
  vector<vector<vector<ll>>> dp(N+10,vector <vector<ll>> (2,vector<ll>(2,oo)));
  vector<ll> a(N);
  for(ll i=0;i<N;i++) cin>> a[i];
  dp[0][0][0]=change(a[0],0,S,E);
  dp[0][1][1]=change(a[0],1,S,E);
  for(ll i=1;i<N;i++){
    for(ll k=0;k<=1;k++){
      dp[i][0][k]=min(dp[i][0][k],dp[i-1][0][k]+change(a[i],0,S,E));
      dp[i][0][k]=min(dp[i][0][k],dp[i-1][1][k]+change(a[i],0,S,E));
      if(k-1>=0)
        dp[i][1][k]=min(dp[i][1][k],dp[i-1][0][k-1]+change(a[i],1,S,E));
      dp[i][1][k]=min(dp[i][1][k],dp[i-1][1][k]+change(a[i],1,S,E));
    }
   // printf("%lld: %lld %lld %lld %lld\n",i,dp[i][0][0],dp[i][0][1],dp[i][1][0],dp[i][1][1]);
  }
  ll ans=oo;
  for(ll i=0;i<2;i++){
    for(ll j=0;j<2;j++)
      ans=min(ans,dp[N-1][i][j]);
  }
  cout<<ans;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
}