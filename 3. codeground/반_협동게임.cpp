#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void update(ll v,vector<ll>& seg,ll nn){
  v+=nn-1;
  while(1){
    seg[v]++;
    v=(v-1)/2;
    if(v==0) break;
  }
}

ll query(ll l,ll r, ll s,ll e, ll v, vector<ll>& seg){
  if(r<s || e<l) return 0;
  else if(s<=l && r<=e) return seg[v];
  else{
    ll mid=(l+r)/2,sum=0;
    sum+=query(l,mid,s,e,v*2+1,seg);
    sum+=query(mid+1,r,s,e,v*2+2,seg);
    return sum;
  }
}

void solve(){
  ll n;
  scanf("%lld",&n);
  vector<ll> a(n);
  vector<vector<ll>> indexByA(n+10);
  vector<ll> end(n);
  vector<bool> visited(n);
  for(ll i=0;i<n;i++) scanf("%lld",&a[i]), indexByA[a[i]].push_back(i);
  for(ll i=0;i<n;i++) {
    ll end2=indexByA[a[i]].back(); indexByA[a[i]].pop_back();
    if(i<end2) end[i]=end2;
    else end[i]=-1;
  }

  ll cnt,ans=0;

  ll nn=1;
  while(nn<n) nn*=2;

  vector<ll> seg(2*nn+10);

  for(ll i=0;i<n;i++){
    cnt=0;
    if(end[i]!=-1){
      cnt = end[i]-i+1-query(0,nn-1,i,end[i],0,seg);
      ans+=cnt-1;
      update(i,seg,nn);
      update(end[i],seg,nn);
    }
  }
  printf("%lld",ans);
}
int main(){
  ll T;
  setbuf(stdout, NULL);
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
    printf("\n");
  }
}