#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line{
  ll a,b;
  Line(ll x,ll y): a(x),b(y){}
  ll func(ll x) const {return a*x+b;};
};

bool check(Line x,Line y,Line z){
  //return (z.b-y.b)*(x.a-y.a)<=(y.b-x.b)*(y.a-z.a); 위 아래 차이점 조사 필요.
  return (z.b-x.b)*(x.a-y.a)<=(y.b-x.b)*(x.a-z.a);
}

void solve(){
  ll n,ans=0,m,onTime=0;
  scanf("%lld",&n);
  vector<ll> r(n),d(n),time(n-1);

  for(ll i=0;i<n;i++){
    scanf("%lld%lld",&r[i],&d[i]);
    onTime+=d[i]-r[i];
    if(i>0){
      time[i-1]=r[i]-d[i-1];
    }
  }
  scanf("%lld",&m);
  vector<ll> p(m),w(m);
  for(ll i=0;i<m;i++) scanf("%lld",&p[i]);
  for(ll i=0;i<m;i++) scanf("%lld",&w[i]);

  vector<Line> H;
  for(ll i=0;i<m;i++){
    while(H.size()>=2 && check(H[H.size()-2],H.back(),Line(p[i],w[i]))) H.pop_back();
    H.push_back(Line(p[i],w[i]));
  }

  sort(time.begin(),time.end());


  ll current=0;
  for(ll i=0;i<time.size();i++){
    ll x=time[i];
    while(current <H.size()-1 && H[current].func(x)>=H[current+1].func(x)) ++current;
    ans+=H[current].func(x);
  }
  printf("%lld\n",ans+onTime*p[0]);
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
}