#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct point{
  ll x;
  double p;
};
bool cmp(point &l,point &r){
  return l.x<r.x;
}

void preProcess(ll N, vector<point>& points, vector<double> &a){
  double sum=0;
  for(ll i=1;i<=N;i++) sum+=points[i].x*points[i].p;
  a[0]=sum;

  for(ll i=1;i<=N;i++) sum-=2*points[i].x*points[i].p,a[i]=sum;
}

void preProcess2(ll N, vector<point>&points, vector<double> &b){
  double sum=0;
  for(ll i=1;i<=N;i++) sum+=points[i].p;
  b[0]=sum;
  for(ll i=1;i<=N;i++) sum-=2*points[i].p, b[i]=sum;
}

void solve(){
  ll N;
  scanf("%lld",&N);
  vector<point> x(N+1);
  vector<point> y(N+1);
  for(int i=1;i<=N;i++){
    scanf("%lld%lld",&x[i].x,&y[i].x);
  }
  for(int i=1;i<=N;i++){
    scanf("%lf",&x[i].p);
    y[i].p=x[i].p;
  }
  sort(x.begin()+1,x.end(),cmp);
  sort(y.begin()+1,y.end(),cmp);

  vector<double> aX(N+1),bX(N+1),aY(N+1),bY(N+1);
  preProcess(N,x,aX);
  preProcess2(N,x,bX);
  preProcess(N,y,aY);
  preProcess2(N,y,bY);

  ll Q;
  scanf("%lld",&Q);
  for(ll i=0;i<Q;i++){
    ll v,w;
    double sum=0;
    scanf("%lld%lld",&v,&w);
    ll l=1, r=N;
    
    while(l<=r){
      ll mid=(l+r)/2;
      if(x[mid].x>=v) r=mid-1;
      else l=mid+1;
    }

    sum+=aX[r]-bX[r]*v;

    // printf("%lld %lld\n",l,r);

    l=1, r=N;
    while(l<=r){
      ll mid=(l+r)/2;
      if(y[mid].x>=w) r=mid-1;
      else l=mid+1;
    }

    sum+=aY[r]-bY[r]*w;
    printf("%lf\n",sum);
  }
 
}

int main(){

  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
}