#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main(){
  ll N,B,C;
  cin>>N;
  vector<ll> A(N+1);
  for(int i=1;i<=N;i++) cin>>A[i];
  cin>>B>>C;
  ll ans=0;

  for(ll i=1;i<=N;i++){
    ans++;
    if(A[i]>B) ans+=(A[i]-B+C-1)/C;
  }
  cout<<ans;
  return 0;
}