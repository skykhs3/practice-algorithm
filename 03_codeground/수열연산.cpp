#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
  ll n,k;
  scanf("%lld%lld",&n,&k);

  vector<ll> a(n+10);
  vector<ll> lefMax(n+10),sumLef(n+10);
  vector<ll> rigMax(n+10),sumRig(n+10);
  ll mx=0;

  for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
  for(ll i=1;i<=n;i++) a[i]= max(k-a[i],0LL), mx=max(a[i],mx);
  for(ll i=1;i<=n;i++) lefMax[i]=max(lefMax[i-1],a[i]),sumLef[i]=sumLef[i-1]+lefMax[i];
  
  for(ll i=n-1;i>=0;i--) rigMax[i]=max(rigMax[i+1],a[i+1]),sumRig[i]=sumRig[i+1]+rigMax[i];
  ll ans=sumLef[0]+sumRig[0];
  for(ll i=1;i<=n;i++){
    ans=min(ans,sumLef[i]+sumRig[i]);
  }
  printf("%lld %lld\n",mx,ans);
}
int main(){
  ll t;
  scanf("%lld",&t);
  for(ll i=1;i<=t;i++){
    printf("Case #%lld\n",i);
    solve();
  }
  return 0;
}