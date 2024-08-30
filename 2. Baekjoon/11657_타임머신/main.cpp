// SPFA algorithm
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Edge{
  ll to,dist;
};
ll oo=99999999999LL;
int main(){
  ll n,m;
  scanf("%lld%lld",&n,&m);
  vector<vector<Edge>> G(n+1);
  for(ll i=1;i<=m;i++){
    ll x,y,z;
    scanf("%lld%lld%lld",&x,&y,&z);
    G[x].push_back({y,z});
  }
  vector<ll> dist(n+1,oo),popCnt(n+1);
  vector<bool> inq(n+1);
  queue<ll> Q;
  dist[1]=0;
  Q.push(1);
  inq[1]=true;
  while(!Q.empty()){
    ll v=Q.front();Q.pop();
    inq[v]=false;
    popCnt[v]++;

    if(popCnt[v]>=n){
      printf("-1");
      return 0;
    }

    for(auto edge:G[v]){
      if(dist[edge.to]>dist[v]+edge.dist){
        dist[edge.to]=dist[v]+edge.dist;

        if(!inq[edge.to]){
          Q.push(edge.to);
          inq[edge.to]=true;
        }
      }
    }
  }
  for(ll i=2;i<=n;i++){
    printf("%lld\n",dist[i]==oo?-1:dist[i]);
  }
  return 0;
}
