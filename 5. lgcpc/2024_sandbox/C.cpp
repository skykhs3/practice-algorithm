#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll s,e;
vector<ll> A(1000),B(1000);
ll MOD=1000000007;

int main(){
  scanf("%lld%lld",&s,&e);
  A[0]=B[0]=1;
  A[1]=B[1]=26;
  for(ll i=2;i<=28;i++){
    A[i]=29*A[i-1]-146*(i>=4? A[i-3]:0)-27*(i>=3? A[i-3]:0);
    B[i]=26*A[i-1]-146*(i>=4? A[i-3]:0);
    A[i]=(A[i]%MOD +MOD)%MOD;
    B[i]=(B[i]%MOD +MOD)%MOD;
    printf("%lld %lld %lld\n",i,A[i],B[i]);
  }
  printf("%lld",B[28]);
}