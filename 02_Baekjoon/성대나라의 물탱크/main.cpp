#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

void dfs(ll v,vector<vector<ll>> &G,vector<bool> &visit,vector<ll> &st,vector<ll> &ed, ll &cnt, vector<ll> &dep, ll lev){
  visit[v]=true;
  st[v]=++cnt;
  dep[v]=lev;
  for(auto to:G[v]){
    if(!visit[to]) dfs(to,G,visit,st,ed,cnt,dep,lev+1);
  }
  ed[v]=++cnt;
}
void update(vector<ll> &seg,ll v,ll nn){
  v+=nn-1;
  while(v!=0){
    seg[v]++;
    v/=2;
  }
}
ll query(vector<ll> &seg,ll lef,ll rig,ll v,ll s,ll e){
  if(s<=lef && rig<=e) return seg[v];
  if(rig<s || e<lef) return 0;
  ll mid=(lef+rig)/2;
  return query(seg,lef,mid,v*2,s,e)+query(seg,mid+1,rig,v*2+1,s,e);
}
int main(){
  freopen("input.txt","r",stdin);

  ll n,c;
  scanf("%lld%lld",&n,&c);
  vector<vector<ll>> G(n+1,vector<ll>());
  for(ll i=1;i<n;i++){
    ll x,y;
    scanf("%lld%lld",&x,&y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  // printf("AAA");
  vector<bool> visit(n+1);
  vector<ll> st(n+1);
  vector<ll> ed(n+1);
  vector<ll> dep(n+1);
  ll cnt=0;
  dfs(c,G,visit,st,ed,cnt,dep,1);


  ll nn=1,m;
  while(nn<cnt) nn*=2;
  vector<ll> seg(nn*2+10);
  scanf("%lld",&m);
  for(ll i=1;i<=m;i++){
    ll o,A;
    scanf("%lld%lld",&o,&A);
    if(o==1){
      update(seg,st[A],nn);;
    }
    else{
      printf("%lld\n",query(seg,1,nn,1,st[A],ed[A])*dep[A]);
    }
  }
  return 0;
}
