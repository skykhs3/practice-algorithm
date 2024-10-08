#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
struct Point{
  int y,x;
};
int N,M,K;
vector<vector<int>> mp(12,vector<int>(12));

int dy[4]={-1,1,0,0};
int dx[4]={0,0,1,-1};
int oo=987654321;
int ans=0;

vector<vector<vector<int>>> runner(12,vector<vector<int>>(12,vector<int>(0)));

void input(){
  int y,x;
  cin>>N>>M>>K;
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      cin>>mp[i][j];

  for(int i=0;i<=N+1;i++) mp[i][0]=mp[i][N+1]=mp[0][i]=mp[N+1][0]=oo;

  for(int i=1;i<=M;i++){
    cin>>y>>x;
    runner[y][x].push_back(i);
  }
  
  cin>>y>>x;
  mp[y][x]=-1;
}
void movePerson(){
  Point exit;
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      if(mp[i][j]==-1)
        exit={i,j};
  
  vector<vector<vector<int>>> newRunner(12,vector<vector<int>>(12,vector<int>(0)));
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      for(int k=0;k<runner[i][j].size();k++){
        int id=runner[i][j][k];
        int mn=abs(i-exit.y)+abs(j-exit.x);
        int mndir=-1;
  
        for(int dir=0;dir<4;dir++){
          int ty=i+dy[dir];
          int tx=j+dx[dir];
          if(mp[ty][tx]>=1) continue;
         
          if(mn>abs(ty-exit.y)+abs(tx-exit.x) 
          || (mn==abs(ty-exit.y)+abs(tx-exit.x) && mndir>dir )){
            mn=abs(ty-exit.y)+abs(tx-exit.x);
            mndir=dir;
         
          }
        }
        if(mndir!=-1){
          int ty=i+dy[mndir];
          int tx=j+dx[mndir];
          newRunner[ty][tx].push_back(id);
          ans++;
        } else{
          newRunner[i][j].push_back(id);
        }
      }
  
  runner=newRunner;
}
void turnPerson(){
  // 탈출 추가
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      if(mp[i][j]==-1){
        runner[i][j].clear();
      }

  int mnSize=oo,mnR,mnC;
  for(int sz=1;sz<=N;sz++){
    for(int i=1;i<=N-sz+1;i++)
      for(int j=1;j<=N-sz+1;j++){
        //point
        bool flag1=false,flag2=false;
        for(int k=i;k<i+sz;k++){
          for(int l=j;l<j+sz;l++){
            if(mp[k][l]==-1) flag1=true;
            if(runner[k][l].size()>0) flag2=true;
          }
        }
        if(flag1 && flag2){
          if(mnSize!=sz){
            if(mnSize>sz){
              mnSize=sz;mnR=i;mnC=j;
            }
          }
          else if(mnR!=i){
            if(mnR>i){
              mnSize=sz;mnR=i;mnC=j;
            }
          }
          else if(mnC!=j){
            if(mnC>j){
              mnSize=sz;mnR=i;mnC=j;
            }
          }
        }
      }
  }
  
  // newRunner, newMap

  vector<vector<int>> newMap=mp;
  auto newRunner=runner;

  if(mnSize!=oo){
    for(int i=mnR;i<mnR+mnSize;i++)
      for(int j=mnC;j<mnC+mnSize;j++){
        newMap[j-mnC+mnR][mnC+mnSize-1-(i-mnR)]=mp[i][j]>0 ? mp[i][j]-1:mp[i][j];
        newRunner[j-mnC+mnR][mnC+mnSize-1-(i-mnR)]=runner[i][j];
      }
  }
  mp=newMap;
  runner=newRunner;

  // for(int i=1;i<=N;i++,printf("\n"))
  //   for(int j=1;j<=N;j++)
  //     printf("%d ",mp[i][j]);
}
bool check(){
  int sum=0;
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      sum+=runner[i][j].size();
  return sum==0;
}
void output(){
  Point exit;
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      if(mp[i][j]==-1)
        exit={i,j};
  cout<<ans<<endl<<exit.y<<" "<<exit.x;
}
void process(){

  for(int i=1;i<=K;i++){
    movePerson();
   // cerr<<i<<endl;
   bool res=check();
    if(res){
      output();
      return;
    }
    turnPerson();
   // cerr<<i<<endl;
    res=check();
    if(res){
      output();
      return;
    }
  }
  output();
}
int main(){
  input();
  process();

  return 0;
}