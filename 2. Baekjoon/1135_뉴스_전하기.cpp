#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dfs(ll v,vector<vector<ll>> &G){
  vector<ll> childAns;
  for(auto child:G[v]){
    childAns.push_back(dfs(child,G));
  }
  sort(childAns.begin(),childAns.end());

  ll ans=0;
  for(ll i=childAns.size()-1;i>=0;i--){
    ll idx=childAns.size()-i;
    ans=max(ans,childAns[i]+idx);
  }
  return ans;
}
int main(){
  ll n,root;

  scanf("%lld",&n);
  vector<ll> a(n),parent(n);
  vector<vector<ll>> G(n);
  for(ll i=0;i<n;i++){
    scanf("%lld",&parent[i]);
    if(parent[i]==-1){
      root=i;
    }
    else{
      G[parent[i]].push_back(i);
    }
  }
  printf("%lld",dfs(root,G));
}