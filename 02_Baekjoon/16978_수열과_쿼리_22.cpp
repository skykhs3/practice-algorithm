#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Query{
  ll k,i,j,index,ans;
  bool operator < (const Query right){
    return k<right.k;
  }
};

struct Query2{
  ll i,v;
};
void update(vector<ll> &seg,ll v,ll val,ll nn){
  v+=nn-1;
  seg[v]=val;
  v/=2;
  while(v!=0){
    seg[v]=seg[v*2]+seg[v*2+1];
    v/=2;
  }
}
ll getSum(vector<ll> &seg,ll lef,ll rig,ll v,ll s,ll e){
  if(s<=lef && rig<=e) return seg[v];
  if(rig<s || e<lef) return 0;
  ll mid=(lef+rig)/2;
  return getSum(seg,lef,mid,v*2,s,e)+getSum(seg,mid+1,rig,v*2+1,s,e);
}
bool cmpIndex(Query &lef,Query &rig){
  return lef.index<rig.index;
}
int main(){
  //freopen("input1.txt","r",stdin);
  ll n,m;
  scanf("%lld",&n);
  vector<ll> a(n+1);
  for(ll i=1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  scanf("%lld",&m);
  vector<Query> two;
  vector<Query2> one;
  for(ll i=1;i<=m;i++){
    ll order;
    scanf("%lld",&order);
    if(order==1){
      ll y,z;
      scanf("%lld%lld",&y,&z);
      one.push_back({y,z});
    }
    else{
      ll y,z,k;
      scanf("%lld%lld%lld",&y,&z,&k);
      two.push_back({y,z,k,i,0});
    }
  }

  ll nn=1;
  while(nn<n)nn*=2;
  vector<ll> seg(nn*2+10);
  for(ll i=1;i<=n;i++){
    update(seg,i,a[i],nn);
  }
  sort(two.begin(),two.end());
  ll s=0;
  while(s<two.size() && two[s].k<=0){
    two[s].ans=getSum(seg,1,nn,1,two[s].i,two[s].j);
    s++;
  }

  ll index=0;
  for(auto query:one){
      index++;
    update(seg,query.i,query.v,nn);
    while(s<two.size() && two[s].k<=index){
      two[s].ans=getSum(seg,1,nn,1,two[s].i,two[s].j);
      s++;
    }
  }
      sort(two.begin(),two.end(),cmpIndex);

  for(auto query:two){
    printf("%lld\n",query.ans);
  }
}
