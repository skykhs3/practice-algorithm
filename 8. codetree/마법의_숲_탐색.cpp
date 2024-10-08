#include <iostream>
#include <vector>
using namespace std;
int R,C,K;
struct Input{
  int c,d;
};
struct Gol{
  int y,x,d;
};

int dy[4]={-1,0,1,0},dx[4]={0,1,0,-1};
vector<vector<int>> mp(80,vector<int>(80));
vector<vector<bool>> visited(80,vector<bool>(80));
vector<Gol> gols(1001);
vector<Input> inputs(1001);
vector<pair<int,int>> down ={{2,0},{1,1},{1,-1}};
vector<pair<int,int>> left2={{-1,-1},{0,-2},{1,-2},{1,-1},{2,-1}};
vector<pair<int,int>> right2={{-1,1},{0,2},{1,2},{1,1},{2,1}};


void input(){
  cin>>R>>C>>K;
  for(int i=1;i<=K;i++)
    cin>>inputs[i].c>>inputs[i].d;
}
bool checkDown(int y,int x,int dir, vector<pair<int,int>> &test,int siz){
  bool error=false;
  for(int i=0;i<siz;i++){
    int ty=y+test[i].first;
    int tx=x+test[i].second;
    if(ty<=0 || (1<=ty && ty<=R && 1<=tx && tx<=C && mp[ty][tx]==0)){
      ;
    } else{
      error=true;
    }
  }
  return !error;
}
void fill(int y,int x,int target){
  for(int dir=0;dir<4;dir++){
    int ty=y+dy[dir];
    int tx=x+dx[dir];
    if(1<=ty && ty<=R && 1<=tx && tx<=C)
      mp[ty][tx]=target;
  }
  if(1<=y && y<=R && 1<=x && x<=C)
    mp[y][x]=target;
}
void print(){
  for(int i=1;i<=R;i++,printf("\n"))
    for(int j=1;j<=C;j++)
      printf("%d ",mp[i][j]);
  printf("\n");
}
void dfs(int y,int x){
  visited[y][x]=true;
  int id=mp[y][x];
  for(int i=0;i<4;i++){
    int ty=y+dy[i];
    int tx=x+dx[i];
    if(1<=ty && ty<=R && 1<=tx && tx<=C && !visited[ty][tx]){
      if(mp[y][x]==mp[ty][tx]){
        dfs(ty,tx);
      }
      if(y==gols[id].y+dy[gols[id].d] && x==gols[id].x+dx[gols[id].d] && mp[ty][tx] != mp[y][x] && mp[ty][tx]>0){
        dfs(ty,tx);
      }
    }
  }
}
void process(){
  int ans=0;
  for(int i=1;i<=K;i++){
    int initY=-1;
    int initX=inputs[i].c;
    int initDir=inputs[i].d;
    gols[i]={initY,initX,initDir};
    while(1){
      if(checkDown(gols[i].y,gols[i].x,gols[i].d,down,3)){

        fill(gols[i].y,gols[i].x,0);
        fill(gols[i].y+1,gols[i].x,i);
        gols[i]={gols[i].y+1,gols[i].x,gols[i].d};
      }
      else if(checkDown(gols[i].y,gols[i].x,gols[i].d,left2,5)){
        fill(gols[i].y,gols[i].x,0);
        fill(gols[i].y+1,gols[i].x-1,i);
        gols[i]={gols[i].y+1,gols[i].x-1,(gols[i].d+3)%4};
      }
      else if(checkDown(gols[i].y,gols[i].x,gols[i].d,right2,5)){
        fill(gols[i].y,gols[i].x,0);
        fill(gols[i].y+1,gols[i].x+1,i);
        gols[i]={gols[i].y+1,gols[i].x+1,(gols[i].d+1)%4};
      } else{
        break;
      }
    }
    if(gols[i].y<=1){
      for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
          mp[i][j]=0;
      continue;
    }
   //print();

    for(int i=1;i<=R;i++)
      for(int j=1;j<=C;j++)
        visited[i][j]=false;
    dfs(gols[i].y,gols[i].x);

    bool flag=false;

    for(int i=R;i>=1;i--){
      for(int j=1;j<=C;j++)
        if(visited[i][j]){
        // cout<<i<<endl;
         ans+=i;
          flag=true;
          break;
        }
      if(flag) break;
    }
  }
  cout<<ans;
}
int main(){
  input();
  process();
}