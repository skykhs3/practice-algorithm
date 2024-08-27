#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll getParent(ll x,vector<ll> &p){
  if(p[x]==x) return x;
  else return p[x]=getParent(p[x],p);
}

void solve(){
  ll n,m;

  scanf("%lld%lld",&n,&m);
  vector<ll> p(2*n+1);
  for(ll i=1;i<=2*n;i++) p[i]=i;

  for(ll i=1;i<=m;i++){
    ll y,x;
    scanf("%lld%lld",&x,&y);
    ll p1=getParent(x,p);
    ll p2=getParent(y+n,p);
    if(p1!=p2){
      p[p1]=p2;
    }
    p1=getParent(x+n,p);
    p2=getParent(y,p);
    if(p1!=p2){
      p[p1]=p2;
    }
  }

  for(ll i=1;i<=n;i++){
    ll p1=getParent(i+n,p);
    ll p2=getParent(i,p);
    if(p1==p2){
      printf("NO");
      return;
    }
  }
  printf("YES");
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
   solve();
   printf("\n");
  }
}