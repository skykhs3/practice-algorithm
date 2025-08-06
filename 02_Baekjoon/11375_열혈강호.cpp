#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
bool dfs(ll v,vector<vector<ll>> &V,vector<bool> &visit,vector<ll> &assign){
  for(auto to:V[v]){
    if(visit[to]) continue;
    visit[to]=true;
    if(assign[to]==0 || dfs(assign[to],V,visit,assign)){
      assign[to]=v;
      return true;
    }
  }
  return false;
}
void maximumBipartiteMatching(vector<vector<ll>> &V,ll n,ll m){
  vector<bool> visit(m+1);
  vector<ll> assign(m+1);
  ll ans=0;
  for(ll i=1;i<=n;i++){
    for(ll j=1;j<=m;j++) visit[j]=false;
    if(dfs(i,V,visit,assign)) ans++;
  }
  printf("%lld",ans);
}
int main(){
  ll n,m;
  vector<vector<ll>> V;
  scanf("%lld%lld",&n,&m);
  V.resize(n+1);
  for(ll i=1;i<=n;i++){
    ll x;
    scanf("%lld",&x);
    V[i].resize(x);
    for(ll j=0;j<x;j++){
      scanf("%lld",&V[i][j]);
    }
  }
  maximumBipartiteMatching(V,n,m);
}
