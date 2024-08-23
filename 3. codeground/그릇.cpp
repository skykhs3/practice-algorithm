#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll MOD=1000000000LL+7;
void solve(){
  ll N,K;
  cin>>N>>K;
  vector<vector<ll>> dp(N+1,vector<ll>(2*N+1));

  dp[2][1]=2;
  for(ll i=3;i<=N;i++){
    for(ll j=1;j<=K && j<=2*i;j++){
      dp[i][j]=2*dp[i-1][j-1]+(i-2)*(j-2>=0?dp[i-1][j-2]:0); // 스케치한 점화식하고 다른 코드를 작성함. 이런 실수를 하다니.
      dp[i][j]%=MOD;
    }
  }
  if(K<=2*N) cout<<dp[N][K];
  else cout<<0;
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