#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(){
  ll n,m;
  map<pair<ll,ll>,ll> M;
  scanf("%lld%lld\n",&n,&m);
  for(ll i=1;i<=m;i++){
    ll x,y;
    scanf("%lld%lld\n",&x,&y);
    if(x>y) swap(x,y);
    M[{x,y}]++;
  }
  vector<bool> visit(n+1);
  for(auto comp:M){
    if(comp.second>=2){
      visit[comp.first.first]=true;
      visit[comp.first.second]=true;
    }
  }
  ll ans=0;
  for(ll i=1;i<=n;i++) if(!visit[i]) ans++;
  return ans;
}

int main(){
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n%lld\n",i,solve());
  }
  return 0;
}
