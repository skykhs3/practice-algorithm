#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll f(ll b,ll a,ll dp){
  return b*a+dp;
}
// 틀린 이유를 찾아야해 -> t-1 ,t, i 간에 헷갈린다. 최대한 모듈화 하자.
ll oo=100000LL;
void solve(){
  ll n;
  scanf("%lld",&n);
  vector<ll> a(n+1),b(n+1);
  for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
  for(ll i=1;i<=n;i++) scanf("%lld",&b[i]);
  vector<ll> dp(n+1,oo);
  vector<ll> deq(n+1);
  ll s=1,t=1;
  deq[1]=1;
  dp[1]=0;
  for(ll i=2;i<=n;i++){
    while(s<t && f(b[deq[s]],a[i],dp[deq[s]])>=f(b[deq[s+1]],a[i],dp[deq[s+1]])) s++;
    dp[i]=f(b[deq[s]],a[i],dp[deq[s]]);
    while(s+1<=t &&
          (double)(dp[deq[t-1]]-dp[deq[t]])/(b[deq[t]]-b[deq[t-1]])
          >=(double)(dp[i]-dp[deq[t]])/(b[deq[t]]-b[i])) t--;
    deq[++t]=i;
  }
  printf("%lld",dp[n]);
}
int main(){
  solve();
  return 0;
}
