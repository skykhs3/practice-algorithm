#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
  ll N;
  cin>>N;
  vector<string> a(N+10);
  vector<vector<ll>> dp(N+10,vector<ll>(N+10));
  for(ll i=0;i<N;i++){
    cin>>a[i];
    a[i]+="#";
  }
  for(ll i=1;i<=N+1;i++) a[N]+="#";

  ll sum=0,cnt=0;
  for(ll i=N-1;i>=0;i--){
    for(ll j=N-1;j>=0;j--){
      if(a[i][j]=='#'){
        if(a[i+1][j]=='#') dp[i][j]=dp[i+1][j];
        else if(a[i][j+1]=='#') dp[i][j]=dp[i][j+1];
        else if(a[i+1][j+1]=='#') dp[i][j]=dp[i+1][j+1];
        else dp[i][j]=dp[i+1][j+1];
      }
      else{
        if(a[i][j+1]=='.' && a[i+1][j]=='.') dp[i][j]=dp[i+1][j]+dp[i][j+1]-dp[i+1][j+1]+1;
        else if(a[i][j+1]=='.') dp[i][j]=dp[i][j+1]+1;
        else if(a[i+1][j]=='.') dp[i][j]=dp[i+1][j]+1;
        else dp[i][j]=1;
        sum+=dp[i][j]-1;
        cnt++;
      }
    }
  }
  cout<<(cnt)*(cnt-1)/2-sum<<endl;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(NULL);
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
  }
}