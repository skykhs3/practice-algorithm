#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve(){
  ll R;
  cin>>R;
  ll sum=0;
  for(ll i=-R+1;i<R;i++){
    ll l=0,r=R;
    while(l<=r){
      ll mid=(l+r)/2;
      if(mid*mid+i*i<R*R) l=mid+1;
      else r=mid-1;
    }
    sum+=2*l-1;
  }
  cout<<sum;
}
int main(){
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
}