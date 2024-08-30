#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool dfs(ll v,vector<vector<ll>> &G, vector<ll> &assign, vector<bool> &visit){
  if(visit[v]) return false;
  visit[v]=true;
  for(auto to:G[v]){
    if(assign[to]==-1 || dfs(assign[to],G,assign,visit)){
      assign[to]=v;
      return true;
    }
  }
  return false;
}

ll solve(){
  ll n,m;
  scanf("%lld%lld",&n,&m);
  vector<vector<ll>> G(n);
  for(ll i=0;i<m;i++){
    ll x,y;
    scanf("%lld%lld",&x,&y);
    G[x].push_back(y);
  }
  ll ans=0;
  vector<ll> assign(n,-1);
  for(ll i=0;i<n;i++){
    vector<bool> visit(n);
    if(dfs(i,G,assign,visit)) ans++;
  }
  return ans;
}

int main(){
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("%lld\n",solve());
  }
}
