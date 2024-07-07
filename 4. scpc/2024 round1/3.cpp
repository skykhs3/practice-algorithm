#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans,sv;
void dfs(ll v,vector<bool> &visited,vector<vector<ll>> &V,vector<ll> &st){
  visited[v]=true;
  ++ans;
  if(st[1]==v) sv=ans;
  for(auto to:V[v]){
    if(v==st[0] && to==st[1]) continue;
    if(v==st[1] && to==st[0]) continue;
    if(!visited[to]) dfs(to,visited,V,st);
  }
}
void solution(){
  ll n;

  scanf("%lld",&n);
  vector<ll> ind(n+10);
  vector<vector<ll>> V(n+10);
  vector<ll> st;
  vector<bool> visited(n+10);
  for(ll i=1;i<=n+1;i++){
    ll x,y;
    scanf("%lld %lld",&x,&y);
    ind[x]++;
    ind[y]++;
    V[x].push_back(y);
    V[y].push_back(x);
  }
  for(ll i=1;i<=n;i++){
    if(ind[i]==3) st.push_back(i);
  }
  ans=0;
  dfs(st[0],visited,V,st);
  ll a=sv-1,b=n-a;
  printf("%lld\n",a*(a-1)/2+b*(b-1)/2);
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solution();
  }
}