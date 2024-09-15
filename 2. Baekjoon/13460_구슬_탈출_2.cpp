#include <bits/stdc++.h>
using namespace std;

string mp[20];
int dp[11][11][11][11];

struct point{
  int y,x;
};

int oo=987654321;
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};
queue<point> Q;

point moveBall(int dir,point red,point blue){
  int yy=red.y;
  int xx=red.x;
  while(1){
    int ty=yy+dy[dir];
    int tx=xx+dx[dir];
    if(mp[ty][tx]=='#') return {yy,xx}; 
    else if(mp[ty][tx]=='O') return {-1,-1};
    else if(ty==blue.y && tx==blue.x) return {yy,xx};
    yy=ty;
    xx=tx;
  }
}

int main(){
  int n,m;
  int ans=oo;
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cin>>mp[i];
    mp[i]=" "+mp[i];
  }
  point red,blue;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(mp[i][j]=='B') blue={i,j},mp[i][j]='.';
      if(mp[i][j]=='R') red={i,j},mp[i][j]='.';
    }
  }

  for(int i=0;i<11;i++)
    for(int j=0;j<11;j++)
      for(int k=0;k<11;k++)
        for(int l=0;l<11;l++)
          dp[i][j][k][l]=oo;

  dp[red.y][red.x][blue.y][blue.x]=0;
  Q.push({red.y,red.x});
  Q.push({blue.y,blue.x});

  while(!Q.empty()){
    point red=Q.front();Q.pop();
    point blue=Q.front();Q.pop();

    for(int dir=0;dir<4;dir++){
      point newRed,newBlue;
      
      if(dir==0){
        if(red.x<blue.x){
          newBlue=moveBall(dir,blue,red);
          newRed=moveBall(dir,red,newBlue);
        }
        else{
          newRed=moveBall(dir,red,blue);
          newBlue=moveBall(dir,blue,newRed);
        }
      }
      else if(dir==1){
        if(red.y<blue.y){
          newBlue=moveBall(dir,blue,red);
          newRed=moveBall(dir,red,newBlue);
        }
        else{
          newRed=moveBall(dir,red,blue);
          newBlue=moveBall(dir,blue,newRed);
        }
      }
      else if(dir==2){
        if(red.x<blue.x){
          newRed=moveBall(dir,red,blue);
          newBlue=moveBall(dir,blue,newRed);
        }
        else{
          newBlue=moveBall(dir,blue,red);
          newRed=moveBall(dir,red,newBlue);
        }
      }
      else{
        if(red.y<blue.y){
          newRed=moveBall(dir,red,blue);
          newBlue=moveBall(dir,blue,newRed);
        }
        else{
          newBlue=moveBall(dir,blue,red);
          newRed=moveBall(dir,red,newBlue);
        }
      }
      if(newBlue.y==-1 && newBlue.x==-1){
        continue;
      }
      if(newRed.y==-1 && newRed.x==-1){
        ans = min(ans,dp[red.y][red.x][blue.y][blue.x]+1);
        continue;
      }
      if(dp[newRed.y][newRed.x][newBlue.y][newBlue.x]>dp[red.y][red.x][blue.y][blue.x]+1){
        dp[newRed.y][newRed.x][newBlue.y][newBlue.x]=dp[red.y][red.x][blue.y][blue.x]+1;
        Q.push(newRed);
        Q.push(newBlue);
      }
    }
  }

  if(ans>10) cout<<-1;
  else cout<<ans;

  return 0;
}