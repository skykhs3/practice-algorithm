#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Point{
  ll y,x;
};
bool cmp(Point l,Point r){
  return l.y<r.y || (l.y==r.y && l.x<r.x);
}

ll getOddPoint(vector<Point> &a, ll n){
  ll meme1=-1,cnt;
  cnt=0;
  for(ll i=0;i<n;i++){
    if(i>0 && a[i].y!=a[i-1].y){
      if(cnt%2==1){
      //  printf("meme %lld\n",a[i-1].y);
        meme1=a[i-1].y;
      }
      cnt=1;
    } else{
      cnt++;
    }
 //  printf("cnt%lld, %lld %lld\n",cnt, a[i].y,a[i].x);
  }
  
  if(cnt%2==1){
    meme1=a[n-1].y;
   // printf("meme %lld\n",a[i-1].y);
  }
  return meme1;
}

ll getSize(vector<Point> &a, ll n, ll y1,ll x1){
  ll beforeX,sum=0,cnt=0;
  for(ll i=0;i<n;i++){
    if(a[i].y==y1 && a[i].x==x1) continue;

    cnt++;
    if(i>0 && a[i].y!=a[i-1].y){
      cnt=1;
    }
    if(cnt%2==0){
      sum+=a[i].x-beforeX;
    }
    beforeX=a[i].x;
  }
  return sum;
}

void solve(){
  int n;
  scanf("%lld",&n);
  vector<Point> a(n);
  vector<Point> b(n);
  for(ll i=0;i<n;i++){
    scanf("%lld%lld",&a[i].y,&a[i].x);
    b[i].y=a[i].x,b[i].x=a[i].y;
  }

  sort(a.begin(),a.end(),cmp);
  sort(b.begin(),b.end(),cmp);

  ll y1=getOddPoint(a,n);
  ll x1=getOddPoint(b,n);

  ll width=getSize(a,n,y1,x1);
  ll height=getSize(b,n,x1,y1);
 // printf("%lld %lld, %lld %lld\n",width,height,y1,x1);

  printf("%lld\n",width+height);
}

int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
}