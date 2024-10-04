#include <stdio.h>
#include <vector>
#include <queue>
typedef long long ll;
using namespace std;
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};
int best;
void gravity(ll n,ll m,vector<vector<ll>> &a){
  for(ll j=1;j<=m;j++){
    vector<ll> b(n+1,0);
    ll cnt=n;

    for(ll i=n;i>=1;i--)
      if(a[i][j]!=0)
        b[cnt--]=a[i][j];
    
    for(ll i=n;i>=1;i--)
      a[i][j]=b[i];
  }
}

void drop(ll n,ll m,vector<vector<ll>> &a, ll x){
  queue<ll> Q;
  vector<vector<bool>> visited(n+1,vector<bool>(m+1));
  for(ll i=1;i<=n;i++){
    if(a[i][x]!=0){
      for(ll k=0;k<4;k++){
        ll ty=i,tx=x;
        for(ll l=1;l<a[i][x];l++){
          ty+=dy[k];
          tx+=dx[k];
          if(1<=ty && ty<=n && 1<=tx && tx<=m){
            Q.push(ty);
            Q.push(tx);
            Q.push(a[ty][tx]);
            a[ty][tx]=0;
            visited[ty][tx]=true;
          }
          else break;
        }

      }
      a[i][x]=0;
      visited[i][x]=true;
      break;
    }
  }

  while(!Q.empty()){
    ll y=Q.front();Q.pop();
    ll x=Q.front();Q.pop();
    ll domain=Q.front();Q.pop();

    for(ll k=0;k<4;k++){
      ll ty=y;
      ll tx=x;
      for(ll l=1;l<domain;l++){
        ty+=dy[k];
        tx+=dx[k];
        if(1<=ty && ty<=n && 1<=tx && tx<=m){
          if(a[ty][tx]!=0 && visited[ty][tx]==false){
            Q.push(ty);
            Q.push(tx);
            Q.push(a[ty][tx]);
            a[ty][tx]=0;
            visited[ty][tx]=true;
          }
        }
        else break;
      }
    }
  }

}

ll getResidual(ll n,ll m,vector<vector<ll>> &a){
  ll cnt=0;
  for(ll i=1;i<=n;i++)
    for(ll j=1;j<=m;j++)
      if(a[i][j]!=0)
        cnt++;
  return cnt;
}

void print(ll lev,ll n,ll m,vector<vector<ll>> &a){
  for(ll i=1;i<=n;i++,printf("\n"))
    for(ll j=1;j<=m;j++)
      printf("%lld ",a[i][j]);
  printf("\n");
}

void process(ll lev,ll depth, ll n,ll m,vector<vector<ll>> &a){
  // print(lev,n,m,a);
  if(lev>depth){
    ll temp=getResidual(n,m,a);
    if(best>temp)
      best=temp;
  } else{
    vector<vector<ll>> b=a;
    for(ll j=1;j<=m;j++){
      drop(n,m,a,j);
      gravity(n,m,a);
      process(lev+1,depth,n,m,a);
      a=b;
    }
  }
}

void solve(){
  ll numOfBall, n,m;

  scanf("%lld%lld%lld",&numOfBall,&m,&n);
  best=n*m;
  vector<vector<ll>> a(n+1,vector<ll>(m+1));
  for(ll i=1;i<=n;i++)
    for(ll j=1;j<=m;j++)
      scanf("%lld",&a[i][j]);

  process(1,numOfBall,n,m,a);

  printf("%d\n",best);
}

int main(){
  ll test;
  scanf("%lld",&test);
  for(ll i=1;i<=test;i++){
    printf("#%lld ",i);
    solve();
  }
}