#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll oo=100000000000LL;
vector<ll> A(100000+1);
vector<ll> V(10000+1);
ll M,K,Q,N;
ll Min,Med,Max;
ll mm;

void three(){
  
  for(ll i=1;i<=Q;i++){
    ll mn=oo;
    for(ll j=1;j<=3;j++){
      if(A[i]==V[j]){
        if(j==1){
          mn=min(mn,Min);
        }
        else if(j==2){
          mn=min(mn,Med);
        }
        else{
          mn=min(mn,Max);
        }
      }
    }
    if(mn==oo) printf("-1 ");
    else printf("%lld ",mn);
  }
}

void solve(){
  scanf("%lld%lld%lld",&M,&K,&Q);
  scanf("%lld%lld%lld",&Min,&Med,&Max);
  mm=min({Min,Med,Max});
  N=2*M*K+1;

  

  for(ll i=1;i<=N;i++) scanf("%lld",&A[i]);
  sort(A.begin()+1,A.begin()+1+N);
  vector<ll> an;
  for(ll i=1;i<=Q;i++){
    scanf("%lld",&V[i]);
  }
  // if(M==2 && K==1){
  //   three();
  //   return;
  // }

  for(ll i=1;i<=Q;i++){
  
    ll index1=lower_bound(A.begin()+1,A.begin()+1+N,V[i])-A.begin();
    ll index2=upper_bound(A.begin()+1,A.begin()+1+N,V[i])-A.begin();
    ll ans=oo;
    if(index1<index2){
      if((index1-1)%K!=0){
        index1+=K-(index1-1)%K;
      }

      for(ll j=index1;j<=min(index2-1,index1+K);j+=K){
        printf("%lld %lld\n",V[i],j);
        ll x=j-1;
        ll y=N-j;
        if(x%K==0 && y%K==0 && x/K%2==y/K%2 ){
          ll a=x/K%2,b=x/K/2,c=y/K/2;
          ll temp = Med*a;
          if(b==0){

          }
          else{
            temp+=mm*(b-1)+Max;
          }
          if(c==0) {

          } else{
            temp+=mm*(c-1)+Min;
          }
          ans=min(ans,temp);
        }
      }
    }
    an.push_back(ans==oo?-1:ans);
  }

  for(ll i=0;i<an.size();i++)
    printf("%lld ",an[i]);
}
int main(){
  ll T;
 // setbuf(stdout, NULL); 오히려 이것 때문에 자주 출력해서 시간 초과가 날수 있다.
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
    printf("\n");
  }
}