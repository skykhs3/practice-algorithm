#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct edge{
  ll from,to;
  char chr;
};
ll N,M;
vector<edge> originE;
bool imp;
struct edge2{
  ll to,len;
};

struct edge3{
  ll toV,toK,len;
};

ll getFakeV(ll v,char chr){// 1~3N
  if(chr=='A') return v*3-2;
  else if(chr=='B') return v*3-1;
  else return v*3;
}

char getBeforeChr(char chr){
  if(chr=='A') return 'C';
  else if(chr=='B') return 'A';
  else return 'B';
}

ll getKindV(ll v){
  return (v-1)%3;
}

ll dfs(ll v, ll n, vector<vector<ll>> &G, vector<bool> &finished, vector<ll> &d, ll &cnt, stack<ll> &st,vector<ll> &group, ll &gcnt){
  ll p;
  p=d[v]=++cnt;
  st.push(v);
  for(auto to:G[v]){
    if(d[to]==0) p=min(p,dfs(to,n,G,finished,d,cnt,st,group,gcnt));
    else if(!finished[to]) p=min(p,d[to]);
  }
  if(p==d[v]){
    gcnt++;
    while(1){
      ll top=st.top(); st.pop();
      finished[top]=true;
      group[top]=gcnt;
      if(top==v){
        break;
      }
    }
  } 

  return p;
}

void tarjan(ll n, vector<vector<ll>> &V, vector<ll> &group, ll &gcnt){
  vector<bool> finished(n+1);
  vector<ll> d(n+1);
  stack<ll> st;
  ll cnt=0;
  
  
  for(ll i=1;i<=n;i++){
    if(d[i]==0){
      dfs(i,n,V,finished,d,cnt,st,group,gcnt); // 정리 필요.
    }
  }
}

void infinite(){
  vector<vector<ll>> V(N*3+10);
  for(auto edge:originE){
    V[edge.from].push_back(edge.to);
  }

  vector<ll> group(N+10);
  ll groupSize=0;
  vector<vector<ll>> cnt(N+10,vector<ll>(3));
  tarjan(N,V,group,groupSize);

  for(auto edge:originE){
    if(group[edge.from] == group[edge.to]){
      cnt[group[edge.from]][edge.chr-'A']++;
    }
  }

  for(ll i=1;i<=groupSize;i++){
    if(cnt[i][0]>0 && cnt[i][1]>0 && cnt[i][2]>0){
      printf("-1");
      return;
    }
  }

  vector<vector<edge2>> G(N*3+10);
  vector<ll> ind(N*3+10);

  for(auto edge:originE){
    ll g1=group[edge.from];
    ll g2=group[edge.to];
    if(g1!=g2){
      char be=getBeforeChr(edge.chr);
      G[getFakeV(g1,be)].push_back({getFakeV(g2,edge.chr),1});
      ind[getFakeV(g2,edge.chr)]++;

      G[getFakeV(g1,'A')].push_back({getFakeV(g2,'A'),0});
      ind[getFakeV(g2,'A')]++;

      G[getFakeV(g1,'B')].push_back({getFakeV(g2,'B'),0});
      ind[getFakeV(g2,'B')]++;

      G[getFakeV(g1,'C')].push_back({getFakeV(g2,'C'),0});
      ind[getFakeV(g2,'C')]++;
    }
  }

  for(ll i=1;i<=groupSize;i++){
    if(cnt[i][0]>0){
      G[getFakeV(i,'C')].push_back({getFakeV(i,'A'),1});
      ind[getFakeV(i,'A')]++;
    }
    if(cnt[i][1]>0){
      G[getFakeV(i,'A')].push_back({getFakeV(i,'B'),1});
      ind[getFakeV(i,'B')]++;
    }
    if(cnt[i][2]>0){
      G[getFakeV(i,'B')].push_back({getFakeV(i,'C'),1});
      ind[getFakeV(i,'C')]++;
    }
  }

  queue<ll> Q;
  vector<ll> dp(3*N+10);

  for(ll i=1;i<=3*groupSize;i++){
    if(ind[i]==0){
      Q.push(i);
    }
  }

  while(!Q.empty()){
    ll v=Q.front();Q.pop();

    for(ll i=0;i<G[v].size();i++){
      if(dp[G[v][i].to]<dp[v]+G[v][i].len){
        dp[G[v][i].to]=dp[v]+G[v][i].len;
      }

      ind[G[v][i].to]--;

      if(ind[G[v][i].to]==0){
        Q.push(G[v][i].to);
      }
    }
  }
  ll ans=0;
  for(ll i=1;i<=3*groupSize;i++) ans=max(ans,dp[i]);
  printf("%lld",ans);
}

void finite(ll K){
  vector<vector<ll>> V(N*3+10);
  for(auto edge:originE){
    char be=getBeforeChr(edge.chr);
    V[getFakeV(edge.from,be)].push_back(getFakeV(edge.to,edge.chr));
  }
  vector<ll> group(3*N+10);
  ll gCnt=0;
  tarjan(3*N,V,group,gCnt);
  if(gCnt!=3*N){
    printf("-1");
    return;
  }

  vector<vector<vector<edge3>>> G(3*N+10, vector<vector<edge3>>(3, vector<edge3>()));
  vector<vector<ll>> ind(3*N+10,vector<ll>(5));
  vector<vector<ll>> dp(3*N+10,vector<ll>(5));
  for(auto edge: originE){
    char be=getBeforeChr(edge.chr);
    for(ll i=K;i>=0;i--){
      G[getFakeV(edge.from,be)][i].push_back({getFakeV(edge.to,edge.chr),i,1});
      ind[getFakeV(edge.to,edge.chr)][i]++;
    }
    for(ll i=K;i>=1;i--){
      G[getFakeV(edge.from,'A')][i].push_back({getFakeV(edge.to,'A'),i-1,0});
      ind[getFakeV(edge.to,'A')][i-1]++;

      G[getFakeV(edge.from,'B')][i].push_back({getFakeV(edge.to,'B'),i-1,0});
      ind[getFakeV(edge.to,'B')][i-1]++;

      G[getFakeV(edge.from,'C')][i].push_back({getFakeV(edge.to,'C'),i-1,0});
      ind[getFakeV(edge.to,'C')][i-1]++;
    }
  }

  queue<ll> Q;

  for(ll i=1;i<=3*N;i++){
    for(ll j=0;j<=K;j++) if(ind[i][j]==0) Q.push(i),Q.push(j);
  }
  
  while(!Q.empty()){
    ll v=Q.front();Q.pop();
    ll k=Q.front();Q.pop();
    for(auto edge:G[v][k]){
      ll toV=edge.toV,toK=edge.toK,len=edge.len;
      
      if(dp[toV][toK]<dp[v][k]+len) dp[toV][toK]=dp[v][k]+len;
      if(--ind[toV][toK]==0){
        Q.push(toV);
        Q.push(toK);
      }
    }
  }

  ll ans=0;
  for(ll i=1;i<=3*N;i++){
    for(ll j=0;j<=K;j++){
      if(ans<dp[i][j]) ans=dp[i][j];
    }
  }
  printf("%lld",ans);
}

void solve(){
  ll k;
  scanf("%lld%lld%lld",&N,&M,&k);
  originE.resize(M);
  for(ll i=0;i<M;i++){
    ll x,y;
    char z;
    scanf("%lld %lld %c ",&originE[i].from,&originE[i].to,&originE[i].chr);
  }

  if(k==-1){
    infinite();
  }else{
    finite(k);
  }
}
int main(){
  ll T;
  setbuf(stdout, NULL);
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
    printf("\n");
  }
}