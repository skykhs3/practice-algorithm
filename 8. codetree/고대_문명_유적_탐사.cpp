#include <bits/stdc++.h>
#define N 5
using namespace std;
typedef long long ll;
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};

void turnFunc(ll sy,ll sx,vector<vector<ll>> &a){
  ll ey=sy+2;
  ll ex=sx+2;
  auto temp=a;
  for(ll i=sy;i<=ey;i++){
    for(ll j=sx;j<=ex;j++){
      a[sy+j-sx][ey-i+sx]=temp[i][j];
    }
  }
}

ll dfs(ll y,ll x,vector<vector<ll>> &a,ll k){
  ll ans=1;
  a[y][x]=0;
  for(ll i=0;i<4;i++){
    ll ty=y+dy[i];
    ll tx=x+dx[i];
    if(1<=ty && ty<=N && tx<=N && 1<=tx && a[ty][tx]==k){
      ans+=dfs(ty,tx,a,k);
    }
  }
  return ans;
}

ll dfs2(ll y,ll x,vector<vector<ll>> &a,ll k){
  ll ans=1;
  a[y][x]=0;
  for(ll i=0;i<4;i++){
    ll ty=y+dy[i];
    ll tx=x+dx[i];
    if(1<=ty && ty<=N && tx<=N && 1<=tx && a[ty][tx]==k){
      ans+=dfs(ty,tx,a,k);
    }
  }
  return ans;
}

ll determineFunc(vector<vector<ll>> &a){
  ll ans=0;
  auto originA=a;
  for(ll i=1;i<=N;i++){
    for(ll j=1;j<=N;j++){   
      if(originA[i][j]!=0){
        ll res=dfs(i,j,originA,originA[i][j]);
        if(res>=3) ans+=res;
      }
    }
  }

  return ans;
}

void determineFunc2(vector<vector<ll>> &a,vector<ll> &wall, ll &s){
  ll ans=0;
  auto originA=a;
  for(ll i=1;i<=N;i++){
    for(ll j=1;j<=N;j++){   
      if(originA[i][j]!=0){
        ll res=dfs(i,j,originA,originA[i][j]);
        if(res>=3){
          dfs2(i,j,a,a[i][j]);
        }
      }
    }
  }

  // for(ll i=1;i<=N;i++){
  //       for(ll j=1;j<=N;j++){
  //         printf("%lld ",a[i][j]);
  //       }
  //       printf("\n");
  //     }
  //     printf("\n");

  // printf("->%lld\n",s);

  for(ll j=1;j<=N;j++){
    for(ll i=N;i>=1;i--){
      if(a[i][j]==0)
      a[i][j]=wall[s++];
    }
  }

  // for(ll i=1;i<=N;i++){
  //       for(ll j=1;j<=N;j++){
  //         printf("%lld ",a[i][j]);
  //       }
  //       printf("\n");
  //     }
  //     printf("\n");
}


int main(){
  ll turn,m;
  ll ans=0;
  ll s=1;
  cin>>turn>>m;
  vector<vector<ll>> a(6,vector<ll>(6));
  vector<ll> wall(m+1);
  for(ll i=1;i<=N;i++){
    for(ll j=1;j<=N;j++){
      cin>>a[i][j];
    }
  }
  for(ll i=1;i<=m;i++){
    cin>>wall[i];
  }
  for(ll tt=1;tt<=turn;tt++){
    auto originA=a;
    ll t1=-1,t2,t3,t4;
    for(ll i=1;i<=3;i++){
      for(ll j=1;j<=3;j++){
        for(ll k=1;k<=4;k++){
      
          turnFunc(i,j,a);
          if(k<=3){
            ll res=determineFunc(a);
            if(t1<res){
              t1=res;
              t2=k;
              t3=j;
              t4=i;
            }
            else if(t1==res && t2>k){
              t1=res;
              t2=k;
              t3=j;
              t4=i;
            }
            else if(t1==res && t2==k && t3>j){
              t1=res;
              t2=k;
              t3=j;
              t4=i;
            }
            else if(t1==res && t2==k && t3==j && t4>i){
              t1=res;
              t2=k;
              t3=j;
              t4=i;
            }
          }
        }
      }
    }

   // printf("%lld %lld %lld %lld",t1,t2,t3,t4);
    for(ll k=1;k<=t2;k++){
      turnFunc(t4,t3,a);
    }
    ll ans=0;

    // for(ll i=1;i<=N;i++){
    //     for(ll j=1;j<=N;j++){
    //       printf("%lld ",a[i][j]);
    //     }
    //     printf("\n");
    //   }
    //   printf("\n");

    while(true){
      ll res=determineFunc(a);
      if(res<3) break;
      ans+=res;
      determineFunc2(a,wall,s);
      // for(ll i=1;i<=N;i++){
      //   for(ll j=1;j<=N;j++){
      //     printf("%lld ",a[i][j]);
      //   }
      //   printf("\n");
      // }
      // printf("\n");
    }
    if(ans==0) break;
    cout<<ans<< " ";
  }
  
}