#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll solve(){
  ll N,K;
  scanf("%lld%lld",&N,&K);
  vector<ll> a(N+1),sum(N+1);
  for(ll i=1;i<=N;i++) scanf("%lld",&a[i]);
  for(ll i=1;i<=N;i++) sum[i]=sum[i-1]+a[i];
  map<ll,ll> Map;
  Map[0]++;
  ll ans=0;
  for(ll i=1;i<=N;i++){
    ans+=Map[sum[i]-K];
    Map[sum[i]]++;
  }
  return ans;
}
int main(){
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n%lld\n",i,solve());
  }
}
