#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Line {
	ll a, b;
	Line(ll a1, ll b1) :a(a1), b(b1) {}
};

ll f(Line x, ll v){
  return x.a*v+x.b;
}

double cross(Line lef, Line rig){
  return (double)(rig.b-lef.b)/(lef.a-rig.a);
}

void solve(){
  freopen("input1.txt","r",stdin);
  ll n;
  scanf("%lld",&n);
  vector<ll> a(n+1),b(n+1);
  for(ll i=1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  for(ll i=1;i<=n;i++){
    scanf("%lld",&b[i]);
  }
  vector<ll> dp(n+1);
  vector<Line> deq;
  ll s=0,t=0;
  deq.push_back(Line(b[1],0));

  for(ll i=2;i<=n;i++){
    while(s+1<=t && f(deq[s],a[i])>=f(deq[s+1],a[i])) s++;
    dp[i]=f(deq[s],a[i]);

    while(s+1<=t && cross(deq[t-1],deq[t])>=cross(deq[t],Line(b[i],dp[i]))){
      deq.pop_back(); t--;
    }
    deq.push_back(Line(b[i],dp[i]));
    t++;
  }
  printf("%lld",dp[n]);
}
int main(){
  solve();
  return 0;
}
