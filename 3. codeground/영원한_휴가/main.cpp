#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void dfs(ll v, vector<vector<ll>> &G, vector<bool> &visit,vector<ll> &vs){
  visit[v]=true;
  for(auto to:G[v])
    if(!visit[to])
      dfs(to,G,visit,vs);
  vs.push_back(v);
}

void rdfs(ll v, vector<vector<ll>> &rG, vector<bool> &visit,vector<ll> &comp){
  comp.push_back(v);
  visit[v]=true;
  for(auto to:rG[v])
    if(!visit[to])
      rdfs(to,rG,visit,comp);
}

ll solve(){
  ll n,m;
  scanf("%lld%lld",&n,&m);
  vector<vector<ll>> G(n+1,vector<ll>());
  vector<vector<ll>> rG(n+1,vector<ll>());
  for(ll i=1;i<=m;i++){
    ll x,y;
    scanf("%lld%lld",&x,&y);
    G[x].push_back(y);
    rG[y].push_back(x);
  }

  //scc
  vector<ll> vs;
  vector<bool> visit(n+1);
  for(ll i=1;i<=n;i++)
    if(!visit[i])
      dfs(i,G,visit,vs);

  fill(visit.begin(),visit.end(),false);
  vector<vector<ll>> scc;
  for(ll i=vs.size()-1;i>=0;i--){
    ll v=vs[i];
    if(!visit[v]){
      vector<ll> comp;
      rdfs(v,rG,visit,comp);
      scc.push_back(comp);
    }
  }

  //preProcessing
  vector<ll> parent(n+1);
  ll currentMaxSize=0;
  for(ll i=0;i<scc.size();i++){
    currentMaxSize=max(currentMaxSize,(ll)scc[i].size());
    for(auto v:scc[i]){
      parent[v]=i;
    }
  }

  vector<vector<ll>> sccG(scc.size(),vector<ll>());
  vector<ll> sccInd(scc.size());
  for(ll i=1;i<=n;i++)
    for(auto to:G[i])
      if(parent[i]!=parent[to])
        sccG[parent[i]].push_back(parent[to]), sccInd[parent[to]]++;

  // 위상정렬
  vector<vector<ll>> pathCnt(scc.size(),vector<ll>(scc.size()));
  queue<ll> Q;

  for(ll i=0;i<scc.size();i++){
    if(sccInd[i]==0){
      Q.push(i);
      pathCnt[i][i]=1;
    }
  }

  while(!Q.empty()){
    ll v=Q.front();Q.pop();
    for(auto to:sccG[v]){
      for(ll i=0;i<scc.size();i++){
        pathCnt[i][to]+=pathCnt[i][v];
       pathCnt[i][to]=min(2LL,pathCnt[i][to]);
      }
      if(--sccInd[to]==0){
        Q.push(to);
        pathCnt[to][to]=1;
      }
    }
  }

  ll ans=0;
  for(ll i=1;i<=n;i++){
    for(auto to:G[i]){
      if(parent[i]!=parent[to] && pathCnt[parent[i]][parent[to]]>=2){
        ll newSize=scc[parent[i]].size()+scc[parent[to]].size();

        for(ll k=0;k<scc.size();k++)
          if(k!=parent[i] && k!=parent[to] && pathCnt[parent[i]][k]>=1 && pathCnt[k][parent[to]]>=1){
            newSize+=scc[k].size();
          }
      //  printf("->%lld %lld\n",newSize,currentMaxSize);
        if(newSize>currentMaxSize) ans+=newSize;
      }
    }
  }

  return ans;
}
int main(){
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n%lld\n",i,solve());
  }
  return 0;
}
