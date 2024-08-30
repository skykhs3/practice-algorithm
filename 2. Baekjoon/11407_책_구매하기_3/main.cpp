#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll oo=999999999LL;

struct Edge{
  ll to,cap,cost,rev;
};

void addEdge(ll from,ll to,ll cap,ll cost,vector<vector<Edge>> &G){
  G[from].push_back({to,cap,cost,G[to].size()});
  G[to].push_back({from,0,-cost,G[from].size()-1});
}

void spfa(ll s,ll t,ll n,vector<vector<Edge>> &G,vector<ll> &dist,vector<ll> &prevv,vector<ll> &previ){
  queue<ll> Q;
  vector<ll> popCnt(n+1);
  vector<bool> inque(n+1);
  fill(dist.begin(),dist.end(),oo);
  dist[s]=0;
  inque[s]=true;
  Q.push(s);
  while(!Q.empty()){
    ll v=Q.front();Q.pop();
    inque[v]=false;
    popCnt[v]++;
    if(popCnt[v]>=n){
      break;
    }
    for(ll i=0;i<G[v].size();i++){
      auto &edge=G[v][i];
      if(edge.cap>0 && dist[v]+edge.cost<dist[edge.to]){
        dist[edge.to]=dist[v]+edge.cost;
        prevv[edge.to]=v;
        previ[edge.to]=i;
        if(!inque[edge.to]){
          inque[edge.to]=true;
          Q.push(edge.to);
        }
      }
    }
  }
}

void minCostMaxFlow(ll s,ll t,ll n,vector<vector<Edge>> &G){
  vector<ll> prevv(n+1),previ(n+1),dist(n+1);
  ll flow=0,cost=0;
  for(;;){
    spfa(s,t,n,G,dist,prevv,previ);
    if(dist[t]==oo){
        break;
    }
    ll d=oo;
    for(ll v=t;v!=s;v=prevv[v]){
      d=min(d,G[prevv[v]][previ[v]].cap);
    }

    flow+=dist[t]*d;
    cost+=d;
    for(ll v=t;v!=s;v=prevv[v]){
      G[prevv[v]][previ[v]].cap-=d;
      G[v][G[prevv[v]][previ[v]].rev].cap+=d;
    }
  }
  printf("%lld\n%lld",cost,flow);
}

int main(){
  freopen("input.txt","r",stdin);
  ll n,m;
  scanf("%lld%lld",&n,&m);
  vector<vector<Edge>> G(5+m+n);
  vector<ll> a(n+1);
  vector<ll> b(m+1);
  vector<vector<ll>> c(m+1,vector<ll>(n+1));
  vector<vector<ll>> d(m+1,vector<ll>(n+1));
  for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
  for(ll i=1;i<=m;i++) scanf("%lld",&b[i]);
  for(ll i=1;i<=m;i++)
    for(ll j=1;j<=n;j++)
      scanf("%lld",&c[i][j]);

  for(ll i=1;i<=m;i++)
    for(ll j=1;j<=n;j++)
      scanf("%lld",&d[i][j]);

  for(ll i=1;i<=m;i++)
    for(ll j=1;j<=n;j++)
      addEdge(1+i,1+m+j,c[i][j],d[i][j],G);

  for(ll i=1;i<=m;i++)
    addEdge(1,1+i,b[i],0,G);

  for(ll i=1;i<=n;i++)
    addEdge(1+m+i,2+m+n,a[i],0,G);

  minCostMaxFlow(1,2+m+n,2+m+n,G);
  return 0;
}
