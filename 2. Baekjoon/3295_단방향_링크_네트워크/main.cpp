#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge{
  ll to,cap,rev;
};

void addEdge(ll from,ll to,ll cap,vector<vector<Edge>> &G){
  G[from].push_back({to,cap,G[to].size()});
  G[to].push_back({from,0,G[from].size()-1});
}

void bfs(ll s,vector<vector<Edge>> &G,vector<ll> &level){
  queue<ll> Q;
  fill(level.begin(),level.end(),-1);

  Q.push(s);
  level[s]=0;
  while(!Q.empty()){
    ll v=Q.front();Q.pop();
    for(auto edge:G[v]){
      if(edge.cap>0 && level[edge.to]==-1){
        level[edge.to]=level[v]+1;
        Q.push(edge.to);
      }
    }
  }
}

ll dfs(ll v,ll t,ll f,vector<vector<Edge>> &G,vector<ll> &level, vector<ll> &iter){
  if(v==t) return f;
  for(ll &i=iter[v];i<G[v].size();i++){
    Edge &edge=G[v][i];
    if(edge.cap>0 && level[edge.to]>level[v]){
      ll d=dfs(edge.to,t,min(f,edge.cap),G,level,iter);
      if(d>0){
        edge.cap-=d;
        G[edge.to][edge.rev].cap+=d;
        return d;
      }
    }
  }
  return 0;
}

ll oo=99999999999LL;

ll maxFlow(ll s,ll t,ll n,vector<vector<Edge>> &G){
  ll flow=0;
  vector<ll> iter(n+1),level(n+1);
  for(;;){
    bfs(s,G,level);
    if(level[t]==-1) break;
    ll f;
    fill(iter.begin(),iter.end(),0);
    while((f=dfs(s,t,oo,G,level,iter))>0){
      flow+=f;
    }
  }
  return flow;
}

ll solve(){
  ll n,m;
  scanf("%lld%lld",&n,&m);
  vector<vector<Edge>> G(n*2+5);
  for(ll i=0;i<m;i++){
    ll x,y;
    scanf("%lld%lld",&x,&y);
    x++,y++;
    addEdge(x+1,1+n+y,1,G);
  }
  for(ll i=1;i<=n;i++){
    addEdge(1,i+1,1,G);
    addEdge(1+n+i,2+2*n,1,G);
  }

  return maxFlow(1,2+2*n,2+2*n,G);
}

int main(){
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("%lld\n",solve());
  }
}
