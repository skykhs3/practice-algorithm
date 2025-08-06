#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll D,P,Q;
void solve(){
  ll ans= 1e18;
  if(P<Q) swap(P,Q);

  ll R=P*Q/gcd(P,Q);

  for(ll i=0;i<=min(R/P-1,(D+P-1)/P);i++){
    ll rest=D-P*i;
    ll number = P*i+(rest+Q-1)/Q*Q;
    ans=min(ans,number);
  }

  printf("%lld",ans);
}

int main(){
  scanf("%lld %lld %lld",&D,&P,&Q);
  solve();
  return 0;
}