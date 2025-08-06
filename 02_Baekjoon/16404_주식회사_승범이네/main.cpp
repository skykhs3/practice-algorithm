#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll st[100002],ed[100002];

vector<vector<ll> > G(100002,vector<ll>());

void dfs(ll v, ll &cnt){
  st[v]=++cnt;
  for(auto to:G[v]){
    dfs(to,cnt);
  }
  ed[v]=++cnt;
}
void query(vector<ll> &seg,ll lef,ll rig,ll v,ll s,ll e,ll w){
  if(s<=lef && rig<=e) seg[v]+=w;
  else if(rig<s || e<lef) return;
  else{
    ll mid=(lef+rig)/2;
    query(seg,lef,mid,v*2,s,e,w);
    query(seg,mid+1,rig,v*2+1,s,e,w);
  }
}
ll get(vector<ll> &seg,ll v,ll nn){
  ll ans=0;
  v+=nn-1;
  while(v!=0){
    ans+=seg[v];
    v/=2;
  }
  return ans;
}
int main(){
  freopen("input.txt","r",stdin);
  ll n,m,root;
  scanf("%lld%lld",&n,&m);
  for(ll i=1;i<=n;i++){
    ll x;
    scanf("%lld",&x);
    if(x==-1) root=i;
    else G[x].push_back(i);
  }
  ll cnt=0;
  dfs(root,cnt);

  ll nn=1;
  while(nn<cnt) nn*=2;
  vector<ll> seg(nn*2+2);
  for(ll i=1;i<=m;i++){
    ll k;
    scanf("%lld",&k);
    if(k==1){
      ll emp,w;
      scanf("%lld%lld",&emp,&w);
      query(seg,1,nn,1,st[emp],ed[emp],w);
    }
    else{
      ll emp;
      scanf("%lld",&emp);
      printf("%lld\n",get(seg,st[emp],nn));
    }
  }
}
