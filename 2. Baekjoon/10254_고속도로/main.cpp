#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct vector2{
  ll x,y;
  vector2(int _x=0,int _y=0): x(_x),y(_y){};
  bool operator <(const vector2 &rig)const{
     return y==rig.y ? x<rig.x : y<rig.y;
  }
  vector2 operator - (const vector2 &rhs) const{
    return vector2(x-rhs.x, y-rhs.y);
  }
  vector2 operator - () const{
    return vector2(-x, -y);
  }
  ll dot(const vector2 &rhs){
    return x*rhs.x+y*rhs.y;
  }
  ll normSquare(){
    return x*x+y*y;
  }
};

vector2 standard(0,0);

ll crossProduct(const vector2 &v0,const vector2 &v1,const vector2 &v2){
  return (v1.x-v0.x)*(v2.y-v0.y)-(v2.x-v0.x)*(v1.y-v0.y);
}

ll dist2(const vector2 &v0,const vector2 &v1){
  return (v1.x-v0.x)*(v1.x-v0.x)+(v1.y-v0.y)*(v1.y-v0.y);
}

bool cmp2(const vector2 &lef,const vector2 &rig){
  ll d=crossProduct(standard,lef,rig);
  if(d>0) return true;
  if(d<0) return false;
  return dist2(standard,lef)<dist2(standard,rig);
}

bool clockWise(const vector2 &v0,const vector2 &v1,const vector2 &v2){
  ll d=crossProduct(v0,v1,v2);
  if(d<0) return true;
  if(d>0) return false;
  return dist2(v0,v2)>dist2(v0,v1);
}

void diameter(vector<vector2> &p){
  ll n=p.size(),lef=0,rig=0;
  vector<vector2> toNext(n);

  for(ll i=0;i<n;i++){
    if(p[i]<p[lef]) lef=i;
    if(p[rig]<p[i]) rig=i;
  }

  vector<ll> ans={lef,rig};
  ll ret=(p[rig]-p[lef]).normSquare();

  for(ll i=0;i<n;i++)
    toNext[i]=(p[(i+1)%n]-p[i]);

  for(ll k=0;k<p.size();k++){
    if(crossProduct(vector2(0,0),toNext[lef],toNext[rig])>0) rig=(rig+1)%n;
    else lef=(lef+1)%n;
    if(ret<(p[lef]-p[rig]).normSquare()){
      ans={lef,rig};
      ret=(p[lef]-p[rig]).normSquare();
    }
  }
  printf("%lld %lld %lld %lld\n",p[ans[0]].x,p[ans[0]].y,p[ans[1]].x,p[ans[1]].y);
}


void solve(){
  ll n;
  scanf("%lld",&n);
  vector<vector2> points(n);
  for(ll i=0;i<n;i++) scanf("%lld%lld",&points[i].x,&points[i].y);

  sort(points.begin(),points.end());
  standard=points[0];
  sort(points.begin()+1,points.end(),cmp2);

  vector<vector2> st;
  st.push_back(points[0]);

  for(ll i=1;i<n;i++){
    while(st.size()>=2 && clockWise(st[st.size()-2],st[st.size()-1],points[i])) st.pop_back();
    st.push_back(points[i]);
  }

  diameter(st);
}

int main(){
  freopen("input.txt","r",stdin);
  ll test;
  scanf("%lld",&test);
  for(ll i=1;i<=test;i++) solve();
  return 0;
}
