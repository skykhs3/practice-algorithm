#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Line{
  ll to,cap,rev;
};
void bfs(ll s,vector<ll> &level,vector<vector<Line>> &G){
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

ll dfs(ll v,ll t,ll cap,vector<ll> &iter,vector<vector<Line>> &G,vector<ll> &level){
  if(v==t) return cap;

  for(ll &i=iter[v];i<G[v].size();i++){
    auto &e=G[v][i];
    ll f;
    if(e.cap>0 && level[e.to]>level[v] && (f=dfs(e.to,t,min(cap,e.cap),iter,G,level))>0){
      e.cap-=f;
      G[e.to][e.rev].cap+=f;
      return f;
    }
  }
  return 0;
}

const ll oo=999999999999LL;

ll maxFlow(ll s,ll t,ll n,vector<vector<Line>> &G){
  vector<ll> level(n+1);
  ll flow=0;

  for(;;){
    fill(level.begin(),level.end(),-1);
    bfs(s,level,G);
    if(level[t]==-1) return flow;
    vector<ll> iter(n+1);
    ll f;
    while((f=dfs(s,t,oo,iter,G,level))>0){
      flow+=f;
    }
  }
  return 0;
}

void addLine(ll u,ll v,ll cap,vector<vector<Line>> &G){
  G[u].push_back({v,cap,G[v].size()});
  G[v].push_back({u,0,G[u].size()-1});
}

int main(){
  ll n,m,k;
  scanf("%lld%lld%lld",&n,&m,&k);
  vector<vector<Line>> G(5+n+m+1);
  for(ll i=1;i<=n;i++){
    ll ord;
    scanf("%lld",&ord);
    for(ll j=1;j<=ord;j++){
      ll x;
      scanf("%lld",&x);
      addLine(2+i,2+n+x,1,G);
    }
  }
  addLine(1,2,n,G);
  addLine(1,4+n+m,k,G);
  for(ll i=1;i<=n;i++){
    addLine(2,2+i,1,G);
    addLine(4+n+m,2+i,1,G);
  }
  for(ll i=1;i<=m;i++){
    addLine(2+n+i,2+n+m+1,1,G);
  }
  printf("%lld",maxFlow(1,3+n+m,4+n+m,G));
  return 0;
}
