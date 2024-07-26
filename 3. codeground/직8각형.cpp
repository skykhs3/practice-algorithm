#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll oo=99999999999999999LL;

ll getX(vector<ll> &per,vector<ll> &x,ll x0,ll K){
  return abs(x0-x[per[0]])+abs(x0-x[per[1]])+abs(x0+K-x[per[2]])+abs(x0+2*K-x[per[3]])+
  abs(x0+3*K-x[per[4]])+abs(x0+3*K-x[per[5]])+abs(x0+2*K-x[per[6]])+abs(x0+K-x[per[7]]);
}

ll getMiddleX(vector<ll> &per,vector<ll> &x,ll K){
  vector<ll> temp={x[per[0]],x[per[1]],-K+x[per[2]],-2*K+x[per[3]],-3*K+x[per[4]],-3*K+x[per[5]],-2*K+x[per[6]],-K+x[per[7]]};
  sort(temp.begin(),temp.end());
  return temp[4];
}

ll getY(vector<ll> &per,vector<ll> &y,ll y0,ll K){
  return abs(y0-y[per[0]])+abs(y0+K-y[per[1]])+abs(y0+2*K-y[per[2]])+abs(y0+2*K-y[per[3]])+
  abs(y0+K-y[per[4]])+abs(y0-y[per[5]])+abs(y0-K-y[per[6]])+abs(y0-K-y[per[7]]);
}

ll getMiddleY(vector<ll> &per,vector<ll> &y,ll K){
  vector<ll> temp={y[per[0]],-K+y[per[1]],-2*K+y[per[2]],-2*K+y[per[3]],-K+y[per[4]],y[per[5]],K+y[per[6]],K+y[per[7]]};
  sort(temp.begin(),temp.end());
  return temp[4];
}

void solve(){
  vector<ll> per(8),x(8),y(8);
  ll K;
  cin>>K;
  for(ll i=0;i<8;i++){
    per[i]=i;
    cin>>x[i];
    cin>>y[i];
  }
  ll ans=oo;

  do{
    ll x0,y0;
    x0=getMiddleX(per,x,K);
    y0=getMiddleY(per,y,K);

    ll hapX=getX(per,x,x0,K);

    ll hapY=getY(per,y,y0,K);
    
    ans=min(hapX+hapY,ans);
  }while(next_permutation(per.begin(),per.end()));


  cout<<ans;
}

int main(){
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
  return 0;
}