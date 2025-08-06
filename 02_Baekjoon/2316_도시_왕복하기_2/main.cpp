#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Line{
  ll to,cap,rev;
};

const ll oo=1000;

void addEdge(ll u,ll v,ll cap,vector<vector<Line>> &G){
  G[u].push_back({v,cap,G[v].size()});
  G[v].push_back({u,0,G[u].size()-1});
}

void bfs(ll s,vector<ll> &level, vector<vector<Line>> &G){
  fill(level.begin(),level.end(),-1);
  queue<ll> Q;
  level[s]=0;
  Q.push(s);
  while(!Q.empty()){
    ll v=Q.front();Q.pop();
    for(auto e:G[v]){
      if(e.cap>0 && level[e.to]==-1){
        level[e.to]=level[v]+1;
        Q.push(e.to);
      }
    }
  }
}

ll dfs(ll v,ll t,ll f,vector<vector<Line>> &G,vector<ll> &level, vector<ll> &iter){
  if(v==t) return f;
  for(ll &i=iter[v];i<G[v].size();i++){
    auto &e=G[v][i];
    if(e.cap>0 && level[e.to]>level[v]){
      ll d=dfs(e.to,t,min(f,e.cap),G,level,iter);
      if(d>0){
        e.cap-=d;
        G[e.to][e.rev].cap+=d;
        return d;
      }
    }
  }
  return 0;
}

ll maxFlow(ll s,ll t,vector<vector<Line>> &G,ll n){
  ll flow=0;
  vector<ll> level(n+1);
  while(1){
    bfs(s,level,G);
    if(level[t]<0) return flow;

    ll f;
    vector<ll> iter(n+1);
    while((f=dfs(s,t,oo,G,level,iter))>0) flow+=f;
  }
  return flow;
}

int main(){
  freopen("input.txt","r",stdin);
  ll n,p;
  scanf("%lld%lld",&n,&p);
  vector<vector<Line>> G(2*n+1);
  for(ll i=1;i<=p;i++){
    ll x,y;
    scanf("%lld%lld",&x,&y);
    addEdge(x+n,y,oo,G);
    addEdge(y+n,x,oo,G);
  }
  for(ll i=1;i<=n;i++){
    addEdge(i,i+n,1,G);
  }
  printf("%lld",maxFlow(1+n,2,G,2*n));
}
