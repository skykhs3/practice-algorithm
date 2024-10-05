#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};
ll oo=987654321;

void determine(ll n,vector<vector<ll>> &a,ll dir, ll y,ll x, ll val, vector<vector<vector<ll>>> &d, deque<ll> &Q, vector<vector<pair<ll,ll> >> &wom){
  if(1<=y && y<=n && 1<=x && x<=n){
    ll ty,tx,tdir;
    bool col=false;
    if(a[y][x]==0){
      ty=y+dy[dir];
      tx=x+dx[dir];
      tdir=dir;
    }
    else if(a[y][x]==1){
      if(dir==0 || dir==3)
        tdir=(dir+2)%4;
      else if(dir==2)
        tdir=3;
      else if(dir==1)
        tdir=0;
      
      ty=y+dy[tdir];
      tx=x+dx[tdir];
      col=true;
    }
    else if(a[y][x]==2){
      if(dir==0 || dir==1)
        tdir=(dir+2)%4;
      else if(dir==2)
        tdir=1;
      else if(dir==3)
        tdir=0;

      ty=y+dy[tdir];
      tx=x+dx[tdir];
      col=true;
    }
    else if(a[y][x]==3){
      if(dir==1 || dir==2)
        tdir=(dir+2)%4;
      else if(dir==0)
        tdir=1;
      else if(dir==3)
        tdir=2;

      ty=y+dy[tdir];
      tx=x+dx[tdir];
      col=true;
    }
    else if(a[y][x]==4){
      if(dir==2 || dir==3)
        tdir=(dir+2)%4;
      else if(dir==1)
        tdir=2;
      else if(dir==0)
        tdir=3;
      
      ty=y+dy[tdir];
      tx=x+dx[tdir];
      col=true;
    }
    else if(a[y][x]==5){
      tdir=(dir+2)%4;

      ty=y+dy[tdir];
      tx=x+dx[tdir];
      col=true;
    }
    else if(a[y][x]>=6 && a[y][x]<=10){
      ll yy,xx;
      if(wom[a[y][x]][0].first==y && wom[a[y][x]][0].second==x){
        yy=wom[a[y][x]][1].first;
        xx=wom[a[y][x]][1].second;
      }
      else{
        yy=wom[a[y][x]][0].first;
        xx=wom[a[y][x]][0].second;
      }
      ty=yy+dy[dir];
      tx=xx+dx[dir];
      tdir=dir;

    } else{
      return;
    }
    
    if(d[tdir][ty][tx]>val+(col?1:0)){
      d[tdir][ty][tx]=val+(col?1:0);
      if(col==false){
        Q.push_front(tx);
        Q.push_front(ty);
        Q.push_front(tdir);
      } else{
        Q.push_back(tdir);
        Q.push_back(ty);
        Q.push_back(tx);
      }
    }
  } else{
    ll ty=y+dy[(dir+2)%4];
    ll tx=x+dx[(dir+2)%4];
    ll tdir=(dir+2)%4;
    ll tval=val+1;
    if(d[tdir][ty][tx]>tval){
      d[tdir][ty][tx]=tval;
      Q.push_back(tdir);
      Q.push_back(ty);
      Q.push_back(tx);
    }
  }
}

ll solve(){
  ll n;
  cin>>n;
  vector<vector<ll>> a(n+2,vector<ll>(n+2));
  vector<vector<pair<ll,ll> >> wom(11); 
  deque<ll> Q;

  for(ll i=1;i<=n;i++)
    for(ll j=1;j<=n;j++){
      cin>>a[i][j];
      if(a[i][j]>=6 && a[i][j]<=10){
        wom[a[i][j]].push_back({i,j});
      }
    }

  ll ans=0;
  for(ll i=1;i<=n;i++){
    for(ll j=1;j<=n;j++){
      if(a[i][j]!=0) continue;
      vector<vector<vector<ll>>> d(4,vector<vector<ll>>(n+2,vector<ll>(n+2,oo)));
      Q.clear();
      for(ll k=0;k<4;k++){
        ll ty=i+dy[k];
        ll tx=j+dx[k];
        determine(n,a,k,ty,tx,0,d,Q,wom);
      }
      
      while(!Q.empty()){
        ll dir=Q.front();Q.pop_front();
        ll yy=Q.front();Q.pop_front();
        ll xx=Q.front();Q.pop_front();
        if(ans<d[dir][yy][xx]) ans=d[dir][yy][xx];
        //printf("%lld %lld %lld %lld\n",dir,yy,xx,d[dir][yy][xx]);
        determine(n,a,dir,yy,xx,d[dir][yy][xx],d,Q,wom);
      }
      
      
    }
  }
  
  return ans;
}
int main(){
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++)
    cout<<"#"<<i<<" "<<solve()<<endl;
}