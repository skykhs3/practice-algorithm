#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct point{
  ll v,index;
  bool operator < (point r){
    return v<r.v || (v==r.v && index<r.index);
  }
};

void solve(){
  ll n;
  scanf("%lld",&n);
  vector<ll> p(n);
  vector<point> v(n);
  for(int i=0;i<n;i++){
    scanf("%lld",&p[i]);
  }
  for(int i=0;i<n;i++){
    scanf("%lld",&v[i].v);
    v[i].index=i;
  }
  sort(v.begin(),v.end());
  
  ll ans=0;
  for(int i=0;i<n;i++) ans+=abs(p[v[i].index]-p[i]);
  printf("%lld\n",ans);
}
int main(){
  ll T;
  setbuf(stdout, NULL);
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
}