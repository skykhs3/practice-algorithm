#include <bits/stdc++.h>
using namespace std;

struct Dice{
  int a,b,c,d,e,f;
};

int dy[5]={0,0,0,-1,1},dx[5]={0,1,-1,0,0};
Dice move(int dir,Dice dice){
  int a,b,c,e,d,f;
  a=dice.a;
  b=dice.b;
  c=dice.c;
  d=dice.d;
  e=dice.e;
  f=dice.f;
  if(dir==1)
    return {d,a,c,f,e,b};
  else if(dir==2)
    return {b,f,c,a,e,d};
  else if(dir==3)
    return {c,b,f,d,a,e};
  else
    return {e,b,a,d,f,c};
}

int main(){
  Dice status={0,0,0,0,0,0};
  int N,M,y,x,K;
  cin>>N>>M>>y>>x>>K;
  y++,x++;
  vector<vector<int>> map(N+1,vector<int>(M+1));
  for(int i=1;i<=N;i++)
    for(int j=1;j<=M;j++)
      cin>>map[i][j];
  
  for(int i=1;i<=K;i++){
    int dir;
    cin>>dir;
    int ty=y+dy[dir];
    int tx=x+dx[dir];
    if(1<=ty && ty<=N && 1<=tx && tx<=M){
      Dice newStatus=move(dir,status);
      if(map[ty][tx]==0){
        map[ty][tx]=newStatus.f;
      }
      else{
        newStatus.f=map[ty][tx];
        map[ty][tx]=0;
      }
      y=ty;
      x=tx;
      status=newStatus;
      cout<<status.a<<endl;
    }
  }
  return 0;
}