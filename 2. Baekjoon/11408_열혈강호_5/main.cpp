#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;

struct Edge{
  ll to,cap,cost,rev;
};

ll oo=999999999999LL;

void addEdge(ll from, ll to,ll cap,ll cost,vector<vector<Edge>> &G){
  G[from].push_back({to,cap,cost,G[to].size()});
  G[to].push_back({from,0,-cost,G[from].size()-1});
}

void minCostFlow(ll s,ll t,ll n,vector<vector<Edge>> &G){
  vector<ll> h(n+1),dist(n+1),prevv(n+1),preve(n+1);
  ll flow=0,cost=0;

  for(;;){
    priority_queue<P,vector<P>,greater<P>> que;
    fill(dist.begin(),dist.end(),oo);
    dist[s]=0;
    que.push(P(0,s));

    while(!que.empty()){
      P p=que.top();que.pop();
      ll v=p.second;
     // printf("v:%lld %lld\n",v,p.first);
      if(dist[v]<p.first)continue;
      for(ll i=0;i<G[v].size();i++){
        Edge &e=G[v][i];
        if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
          dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
          prevv[e.to]=v;
          preve[e.to]=i;
          que.push(P(dist[e.to],e.to));
        }
      }
    }

    if(dist[t]==oo) break;
    for(ll i=1;i<=n;i++) h[i]+=dist[i];
    ll d=oo;
    for(ll v=t;v!=s;v=prevv[v])
      d=min(d,G[prevv[v]][preve[v]].cap);

    flow+=d;
    cost+=d*h[t];
    for(ll v=t;v!=s;v=prevv[v]){
      Edge &e=G[prevv[v]][preve[v]];
      e.cap-=d;
      G[v][e.rev].cap+=d;
    }
  }
  printf("%lld\n%lld",flow,cost);
}

int main(){
  freopen("input.txt","r",stdin);
  ll n,m;
  scanf("%lld%lld",&n,&m);
  vector<vector<Edge>> G(5+n+m);
  for(ll i=1;i<=n;i++){
    ll num;
    scanf("%lld",&num);
    for(ll j=1;j<=num;j++){
      ll work,cost;
      scanf("%lld%lld\n",&work,&cost);
      addEdge(1+i,1+n+work,1,cost,G);
    }
    addEdge(1,1+i,1,0,G);
  }
  for(ll i=1;i<=m;i++)
    addEdge(1+n+i,1+n+m+1,1,0,G);
  minCostFlow(1,2+n+m,2+n+m,G);
}
