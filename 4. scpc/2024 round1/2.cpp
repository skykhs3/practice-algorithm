#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solution(){
  ll i,ans=0,n;
  scanf("%lld",&n);
  vector<ll> a(n);
  for(i=0;i<n;i++){
    scanf("%lld",&a[i]);
  }
  sort(a.begin(),a.end());
  for(i=0;i<n/4;i++){
    ans-=a[i];
  }
  for(i=n/4*3;i<n;i++){
    ans+=a[i];
  }
  printf("%lld\n",ans*2);
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solution();
  }
}