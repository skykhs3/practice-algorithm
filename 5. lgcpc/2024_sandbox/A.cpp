#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Edge{
  ll s,e,val;
  bool operator <(const Edge &right)const{
    return val<right.val;
  }
};

ll getParent(vector<ll> &p, ll v){
  if(p[v]==v) return p[v];
  else return p[v]=getParent(p,p[v]);
}

void solve(ll N,ll M,vector<Edge> &e){
  vector<ll> p(N+1);
  for(ll i=1;i<=N;i++) p[i]=i;
  ll ans=0,cnt=0,minVal=-1;
  for(auto edge:e){
    ll p1=getParent(p,edge.s);
    ll p2=getParent(p,edge.e);
    if(p1!=p2){
      p[p1]=p2;
      ans+=edge.val;
      cnt++;
      if(minVal==-1) minVal=edge.val;
    }
  }
 // printf("%lld %lld\n",ans,cnt);
  if(cnt!=N-1){
    printf("0 ");
  }else{
    printf("%lld ",ans);
    vector<Edge> newEdge;
    for(auto edge:e){
      if(edge.val!=minVal){
        newEdge.push_back(edge);
      }
    }
    e=newEdge;
  }
}
int main(){
  ll N,M,K;
  scanf("%lld %lld %lld",&N,&M,&K);
  vector<Edge> e(M);
  
  for(ll i=0;i<M;i++){
    scanf("%lld%lld",&e[i].s,&e[i].e);
    e[i].val=i+1;
  }
  sort(e.begin(),e.end());
  for(ll i=1;i<=K;i++){
    solve(N,M-i+1,e);
  }
}