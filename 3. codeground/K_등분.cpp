#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll mod=1000000007;
vector<ll> fact(500005);
void getFact(){
  fact[0]=1;
  for(ll i=1;i<500005;i++){
    fact[i]=fact[i-1]*i%mod;
  }
}
ll pow2(ll n,ll k){
  if(k==0) return 1;
  if(k==1) return n;
  else{
    ll temp=pow2(n,k/2);
    if(k%2==0) return temp*temp%mod;
    else return (temp*temp%mod)*n%mod;
  }
}

ll getCombi(ll n,ll r){
  if(n<r) return 0;
  return fact[n]*pow2(fact[r],mod-2)%mod*pow2(fact[n-r],mod-2)%mod;
}
void solve(){
  ll N,K;
  scanf("%lld%lld",&N,&K);
  vector<ll> a(N);
  vector<ll> sum(N);
  vector<ll> count(N+10);
  vector<ll> countSum(N+10);
  for(ll i=0;i<N;i++){
    scanf("%lld",&a[i]);
    if(i>0) sum[i]+=sum[i-1];
    sum[i]+=a[i];
  }
  if(sum[N-1]%K!=0){
    printf("0\n");
    return;
  }
  ll L=sum[N-1]/K;
  if(L==0){
    ll zeroCnt=0;
    for(ll i=0;i<N;i++) if(sum[i]==0) zeroCnt++;
    printf("%lld\n",getCombi(zeroCnt-1,K-1));
    return;
  }
  count[0]=1;
  countSum[0]=1;
  for(ll i=0;i<N;i++){
    if(sum[i]%L==0 && sum[i]/L>=1){
      count[sum[i]/L]=countSum[sum[i]/L-1]%mod;
      countSum[sum[i]/L]+=count[sum[i]/L];
      countSum[sum[i]/L]%=mod;
    }
  }
  printf("%lld\n",count[K]);
}
int main(){
  getFact();
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
}