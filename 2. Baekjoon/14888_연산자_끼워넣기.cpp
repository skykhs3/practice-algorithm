#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll oo=100000000000000LL;
ll ansMin=oo,ansMax=-oo;
void dfs(ll N, int lev,vector<ll> &a,ll A,ll B,ll C,ll D, ll sum){
  if(lev>=N){
    ansMax=max(ansMax,sum);
    ansMin=min(ansMin,sum);
  } else{
    if(A>=1) dfs(N,lev+1,a,A-1,B,C,D,sum+a[lev+1]);
    if(B>=1) dfs(N,lev+1,a,A,B-1,C,D,sum-a[lev+1]);
    if(C>=1) dfs(N,lev+1,a,A,B,C-1,D,sum*a[lev+1]);
    if(D>=1) dfs(N,lev+1,a,A,B,C,D-1,sum/a[lev+1]);
  }
}
int main(){
  ll N;
  cin>>N;
  vector<ll> a(N+1);
  ll A,B,C,D;
  for(int i=1;i<=N;i++) cin>>a[i];
  cin>>A>>B>>C>>D;
  dfs(N,1,a,A,B,C,D,a[1]);
  cout<<ansMax<<endl<<ansMin;
  return 0;
}