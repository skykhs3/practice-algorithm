#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll getIdx(ll y,ll x,ll m){
  return (y-1)*m+x;
}
struct Edge{
  ll to,cap,rev;
};
void addEdge(ll from,ll to,ll cap,vector<vector<Edge>> &G){
  G[from].push_back({to,cap,G[to].size()});
  G[to].push_back({from,0,G[from].size()-1});
}

ll dy[4]={0,1,0,-1};
ll dx[4]={1,0,-1,0};
ll oo=999999999LL;

void bfs(ll s,vector<ll> &level,vector<vector<Edge>> &G){
  queue<ll> Q;
  fill(level.begin(),level.end(),-1);
  level[s]=0;
  Q.push(s);
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
ll dfs(ll v,ll t,ll f, vector<ll> &iter,vector<vector<Edge>> &G,vector<ll> &level){
  //printf("v:%lld\n",v);
  if(v==t) return f;
  for(ll &i=iter[v];i<G[v].size();i++){
    auto &edge=G[v][i];
    if(edge.cap>0 && level[edge.to]>level[v]){
      ll d=dfs(edge.to,t,min(f,edge.cap),iter,G,level);
      if(d>0){
        edge.cap-=d;
        G[edge.to][edge.rev].cap+=d;
        return d;
      }
    }
  }
  return 0;
}
ll maxFlow(ll s,ll t,ll n,vector<vector<Edge>> &G){
  vector<ll> level(n+1);
  vector<ll> iter(n+1);
  ll flow=0;
  for(;;){
    bfs(s,level,G);
    if(level[t]==-1) break;
    ll f;
    fill(iter.begin(),iter.end(),0);
    while((f=dfs(s,t,oo,iter,G,level))>0){
     // printf("%lld\n",f);
      flow+=f;
    }
  }
  return flow==oo?-1:flow;
}
int main(){
  freopen("input.txt","r",stdin);
  ll N,M;
  ll s,t;
  string st[110];
  cin>>N>>M;
  vector<vector<Edge>> G(2*N*M+10);
  for(ll i=1;i<=N;i++){
    string temp;
    cin>>temp;
    st[i]=" "+temp;
  }
  for(ll i=1;i<=N;i++){
    for(ll j=1;j<=M;j++){
      if(st[i][j]=='K'){
        s=getIdx(i,j,M);
        addEdge(s,s+N*M,oo,G);
      }
      else if(st[i][j]=='H'){
        t=getIdx(i,j,M);
        addEdge(t,t+N*M,oo,G);
      }
      else if(st[i][j]=='.'){
        ll idx=getIdx(i,j,M);
        addEdge(idx,idx+N*M,1,G);
      }
      for(ll k=0;k<4;k++){
        ll ty=i+dy[k];
        ll tx=j+dx[k];
        if(1<=ty && ty<=N && 1<=tx && tx<=M){
          addEdge(getIdx(i,j,M)+N*M,getIdx(ty,tx,M),oo,G);
        }
      }
    }
  }
  printf("%lld",maxFlow(s,t+N*M,2*N*M,G));

  return 0;
}
