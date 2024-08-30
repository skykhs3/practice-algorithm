#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct vector2{
  long double x,y;
  explicit vector2(long double _x=0,long double _y=0): x(_x),y(_y){};
  bool operator <(vector2 &rig){
     return y==rig.y ? x<rig.x : y<rig.y;
  }
  vector2 operator - (const vector2 &rhs) const{
    return vector2(x-rhs.x, y-rhs.y);
  }
  vector2 operator - () const{
    return vector2(-x, -y);
  }
  long double dot(const vector2 &rhs){
    return x*rhs.x+y*rhs.y;
  }
  long double norm(){
    return hypot(x,y);
  }
  vector2 normalize(){
    return vector2(x/norm(),y/norm());
  }
};

vector2 standard(0,0);

ll crossProduct(vector2 &v0,vector2 &v1,vector2 &v2){
  return (v1.x-v0.x)*(v2.y-v0.y)-(v2.x-v0.x)*(v1.y-v0.y);
}

ll dist2(vector2 &v0,vector2 &v1){
  return (v1.x-v0.x)*(v1.x-v0.x)+(v1.y-v0.y)*(v1.y-v0.y);
}

bool cmp2(vector2 &lef,vector2 &rig){
  ll d=crossProduct(standard,lef,rig);
  if(d>0) return true;
  if(d<0) return false;
  return dist2(standard,lef)<dist2(standard,rig);
}

bool clockWise(vector2 &v0,vector2 &v1,vector2 &v2){
  ll d=crossProduct(v0,v1,v2);
  if(d<0) return true;
  if(d>0) return false;
  return dist2(v0,v2)>dist2(v0,v1);
}

void diameter(vector<vector2> &p){
  ll n=p.size();
  ll lef=min_element(p.begin(),p.end())-p.begin();
  ll rig=max_element(p.begin(),p.end())-p.begin();

  vector2 calipersA(0,1);
  long double ret=(p[rig]-p[lef]).norm();
  vector<ll> ans={lef,rig};

  vector<vector2> toNext(n);
  for(ll i=0;i<n;i++)
    toNext[i]=(p[(i+1)%n]-p[i]).normalize();

  ll a=lef, b=rig;
  while(a!=rig || b!=lef){
    long double cosThetaA=calipersA.dot(toNext[a]);
    long double cosThetaB=-calipersA.dot(toNext[b]);
    if(cosThetaA>cosThetaB){
      calipersA=toNext[a];
      a=(a+1)%n;
    } else{
      calipersA=-toNext[b];
      b=(b+1)%n;
    }
    if(ret<(p[a]-p[b]).norm()){
      ret=(p[a]-p[b]).norm();
      ans={a,b};
    }
  }
  long double x=p[ans[0]].x-p[ans[1]].x;
  long double y=p[ans[0]].y-p[ans[1]].y;
  cout<<setprecision(20)<<hypot(x,y);
}


void solve(){
  ll n;
  cin>>n;
  vector<vector2> points(n);
  for(ll i=0;i<n;i++){
    cin>>points[i].x>>points[i].y;
  }
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
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt","r",stdin);
  solve();
  return 0;
}
