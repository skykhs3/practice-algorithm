#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void update(vector<ll> &seg,ll v){
  while(1){
    seg[v]++;
    if(v==0) break;
    v=(v-1)/2;
  }
}

ll query(ll lef,ll rig,ll s,ll e, ll v,vector<ll>& seg){
  if(rig<s || e<lef) return 0;
  if(s<=lef && rig<=e){
    return seg[v];
  } 
  else{
   // cerr<<lef<< " " <<rig<<endl;
    ll mid=(lef+rig)/2;
    ll sum=0;
      sum+=query(lef,mid,s,e,v*2+1,seg);
  
      sum+=query(mid+1,rig,s,e,v*2+2,seg);
    return sum;
  }
}
void solve(){
  ll N,K;
  scanf("%lld%lld",&N,&K);
  vector<ll> W(N+1);
  vector<ll> C(N+1);
  vector<ll> sumA(N+1);
  vector<ll> sortedSum(N+1);
  vector<ll> sumC(N+1);
  for(ll i=1;i<=N;i++){
    scanf("%lld",&C[i]);
    if(C[i]==1) sumC[i]=sumC[i-1]+1;
    else sumC[i]=sumC[i-1]-1;
  }
  for(ll i=1;i<=N;i++){
    scanf("%lld",&W[i]);
  }


  for(ll i=1;i<=N;i++){
    sumA[i]=sumA[i-1]+(C[i]==1 ? W[i]:-W[i]);
  }

  vector<vector<ll>> dae(2*N+10),sortedDae(2*N+10);
  dae[N].push_back(0);
  sortedDae[N].push_back(0);
  for(ll i=1;i<=N;i++){
    dae[sumC[i]+N].push_back(sumA[i]);
    sortedDae[sumC[i]+N].push_back(sumA[i]);
  }
  ll ans=0;
  for(ll k=0;k<2*N+10;k++){

    sort(sortedDae[k].begin(),sortedDae[k].end());


    ll nn=1;
    while(nn<dae[k].size()+1) nn*=2;

    vector<ll> seg(nn*2+10);
    // ll pi=lower_bound(sortedDae[k].begin(),sortedDae[k].end(),0)-sortedSum.begin();
    // update(seg,pi+nn-1);
    
    for(ll i=0;i<sortedDae[k].size();i++){
    //  cerr<<i<<endl;
      ll s=lower_bound(sortedDae[k].begin(),sortedDae[k].end(),dae[k][i]-K)-sortedDae[k].begin();
      ll e=upper_bound(sortedDae[k].begin(),sortedDae[k].end(),dae[k][i]+K)-sortedDae[k].begin()-1;
      ll sum=query(0,nn-1,s,e,0,seg);
      
      ans+=sum;
      ll pi=lower_bound(sortedDae[k].begin(),sortedDae[k].end(),dae[k][i])-sortedDae[k].begin();
      update(seg,pi+nn-1);
    }
  }
  printf("%lld",ans);
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    solve();
    printf("\n");
  }
}