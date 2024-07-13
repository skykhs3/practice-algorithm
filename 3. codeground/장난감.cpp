#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void getFinalState(vector<ll> &b, ll n){
  ll dummyCnt=0;
  for(int k=0;k<2;k++){
    for(ll i=n-1;i>=0;i--){
      b[i]+=dummyCnt;
      if(b[i]>=1){
        dummyCnt=b[i]-1;
        b[i]=1;
      }
    }
  }
}

void kmp(vector<ll> &b, ll n){
  ll matched=0;
  vector<ll> pi(2*n);
  for(ll i=1;i<2*n;i++){
    while(matched>0 && b[matched] != b[i]) matched=pi[matched-1];
    if(b[matched]==b[i]){
      pi[i]=++matched;
      if(matched==n){
        printf("%lld\n",i-matched+1);
        break;
      }
    }
  }
}

void solve(){
  ll n, sum=0;
  scanf("%lld",&n);
  
  vector<ll> a(n),b(2*n);
  for(int i=0;i<n;i++) scanf("%lld",&a[i]),sum+=a[i],b[i]=a[i];
  if(sum>=n){
    printf("1\n"); 
    return;
  }

  getFinalState(b,n);

  for(ll i=0;i<n;i++) b[i+n]=b[i];

  kmp(b,n);
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
  return 0;
}