#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iostream>
typedef long long ll;
using namespace std;

struct Cell{
  ll time;
  ll life;
};

int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};

map<pair<ll,ll>,Cell> cell,originCell;
ll solve(){
  ll n,m,endOfTime;
  scanf("%lld%lld%lld",&n,&m,&endOfTime);
  vector<vector<ll>> a(n+1,vector<ll>(m+1));
  cell.clear();

  for(ll i=1;i<=n;i++)
    for(ll j=1;j<=m;j++){
      scanf("%lld",&a[i][j]);
      if(a[i][j]!=0) cell[make_pair(i,j)]={a[i][j],a[i][j]};
    }
  
  for(ll currentTime=1;currentTime<=endOfTime;currentTime++){
    for(auto& it:cell) cell[it.first].time--;

    if(currentTime==endOfTime){
      ll ans=0;
      for(auto it:cell){
        ll life=it.second.life;
        ll time=it.second.time;
        if(time>-life) ans++;
      }
      return ans;
    }
    

    originCell=cell;

    for(auto it:originCell){
      ll y=it.first.first;
      ll x=it.first.second;
      ll time=it.second.time;
      ll life=it.second.life;

      if(life>0 && time>-life && time<=0){
        for(ll k=0;k<4;k++){
          ll ty=y+dy[k];
          ll tx=x+dx[k];
          if(cell.find({ty,tx})==cell.end()){
            cell[{ty,tx}]={life+1,life};
          } else if(cell[{ty,tx}].life<life && cell[{ty,tx}].life+1==cell[{ty,tx}].time){
            cell[{ty,tx}]={life+1,life};
          }
        }
      }
    }
  }

  return 0;
}

int main(){
  ll test;
  scanf("%lld",&test);
  for(ll i=1;i<=test;i++){
    printf("#%lld %lld\n",i,solve());
  }
  return 0;
}