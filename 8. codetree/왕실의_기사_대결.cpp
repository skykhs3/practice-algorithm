//한줄 한줄 꼼꼼하고 정확하게.
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> mp(42,vector<int>(42));
vector<vector<int>> knight(42,vector<int>(42));
vector<vector<int>> newKnight(42,vector<int>(42));
vector<int> life(42);
int L,N,Q;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
int ans=0;
vector<vector<bool>> visited(42,vector<bool>(42));

void fillA(int y1,int y2,int x1,int x2,vector<vector<int>> &a,int c){
  for(int i=y1;i<=y2;i++)
    for(int j=x1;j<=x2;j++)
      a[i][j]=c;
}
pair<int,int> findStartPosition(int id,vector<vector<int>> &a){
  for(int i=1;i<=L;i++)
    for(int j=1;j<=L;j++)
      if(a[i][j]==id) return {i,j};
  return {-1,-1};
}
void simul(int y,int x,vector<vector<int>> &a,int targetDir){
  visited[y][x]=true;
  for(int dir=0;dir<4;dir++){
    int ty=y+dy[dir];
    int tx=x+dx[dir];
    if(visited[ty][tx]) continue;
    if(a[ty][tx]==a[y][x] || (a[ty][tx]!=0 && dir==targetDir)){
       simul(ty,tx,a,targetDir);
    }
  }
}
bool check(int dir){
  for(int i=1;i<=L;i++)
    for(int j=1;j<=L;j++)
      if(visited[i][j]){
        if(mp[i+dy[dir]][j+dx[dir]]==2) return false;
      }
  return true;
}
void damage(int dir,int ord){

  for(int i=1;i<=L;i++)
    for(int j=1;j<=L;j++)
      newKnight[i][j]=0;
  
 // cout<<knight[3][1]<<endl;

  for(int i=1;i<=L;i++)
    for(int j=1;j<=L;j++){
      if(knight[i][j]==0) continue;
      if(visited[i][j]){
        if(mp[i+dy[dir]][j+dx[dir]]==1 && knight[i][j]!=ord){
          life[knight[i][j]]--;
        }
        newKnight[i+dy[dir]][j+dx[dir]]=knight[i][j];
      }
      else{
        newKnight[i][j]=knight[i][j];
      }
    }
  for(int i=1;i<=L;i++){
    for(int j=1;j<=L;j++){
      if(life[newKnight[i][j]]<=0)
        newKnight[i][j]=0;
    }
  }
  knight=newKnight;
}
int main(){
  
  cin>>L>>N>>Q;
  for(int i=1;i<=L;i++)
    for(int j=1;j<=L;j++)
      cin>>mp[i][j];
  
  for(int i=0;i<=L+1;i++) mp[0][i]=mp[L+1][i]=mp[i][0]=mp[i][L+1]=2;

  
  for(int i=1;i<=N;i++){
    int r,c,h,w,k;
    cin>>r>>c>>h>>w>>life[i];
    fillA(r,r+h-1,c,c+w-1,knight,i);
  }
  auto originLife=life;


  for(int i=1;i<=Q;i++){
    int id,d;
    cin>>id>>d;
    pair<int,int> pp=findStartPosition(id,knight);
    

    if(pp.first==-1) continue;

    for(int y=1;y<=L;y++)
      for(int x=1;x<=L;x++)
        visited[y][x]=false;
   
    simul(pp.first,pp.second,knight,d);

    bool res=check(d);
    if(res==false) continue;

    damage(d,id);

  }
  for(int i=1;i<=N;i++){
    if(life[i]>0)//기사 생존
     ans+=originLife[i]-life[i];
  }
  cout<<ans;
}