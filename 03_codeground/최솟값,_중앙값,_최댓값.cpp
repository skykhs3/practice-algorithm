#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll oo=100000000000LL;
vector<ll> A(100000+1);
vector<ll> V(10000+1);

void solve(){
  ll M,K,Q,N;
  ll Min,Med,Max;
  ll Best;

  scanf("%lld%lld%lld",&M,&K,&Q);
  scanf("%lld%lld%lld",&Min,&Med,&Max);
  Best=min({Min,Med,Max});
  N=2*M*K+1;

  for(ll i=1;i<=N;i++) scanf("%lld",&A[i]);
  sort(A.begin()+1,A.begin()+1+N);
  vector<ll> ansList;
  for(ll i=1;i<=Q;i++){
    scanf("%lld",&V[i]);
  }

  vector<ll> bestByNumber(100001,oo);
  for(ll i=1;i<=N;i++){
    ll ans=oo;
    if(i==1) {
      ans=min(ans,Min+Best*(M-1));
    }
    if(i==N){
      ans=min(ans,Max+Best*(M-1));
    }
    if(1+K<=i && i<=N-K){
      ans=min(ans,Med+Best*(M-1));
    }
    if(M>=2 && 2<=i && i<=N-2*K){
      ans=min(ans,Min+min(Med,Max)+Best*(M-2));
    }
    if(M>=2 && 1+2*K<=i && i<=N-1){
      ans=min(ans,Max+min(Med,Min)+Best*(M-2));
    }
    bestByNumber[A[i]]=min(bestByNumber[A[i]],ans);
  }

  for(ll i=1;i<=Q;i++){
    if(bestByNumber[V[i]]==oo) printf("-1 ");
    else printf("%lld ",bestByNumber[V[i]]);
  }
}
int main(){
  ll T;
  freopen("input.txt","r",stdin);
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
    printf("\n");
  }
}
