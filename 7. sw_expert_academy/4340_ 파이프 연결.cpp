// TODO: backtracking 줄이는 법을 모르겠음. TLE
#include <bits/stdc++.h>
using namespace std;
int dy[4]={0,1,0,-1},dx[4]={1,0,-1,0};
int ans;

void dfs(int n, vector<vector<int>> &a, int dir,int y,int x,vector<vector<bool>> &visit,int lev){
  if(lev+n-x+n-y>=ans) return;

  if(y==n && x==n && dir==0){
    ans=min(ans,lev);
    return;
  }

  int ty=y+dy[dir];
  int tx=x+dx[dir];

  if(1<=ty && ty<=n && 1<=tx && tx<=n && a[ty][tx]!=0 && !visit[ty][tx]){
    if(a[ty][tx]<3){
      visit[ty][tx]=true;
      dfs(n,a,dir,ty,tx,visit,lev+1);
      visit[ty][tx]=false;
    } else{
      visit[ty][tx]=true;
      dfs(n,a,(dir+1)%4,ty,tx,visit,lev+1);
      dfs(n,a,(dir+3)%4,ty,tx,visit,lev+1);
      visit[ty][tx]=false;
    }
  }
}
void solve(){
  int n;
  cin>>n;
  vector<vector<int>> a(n+1,vector<int>(n+1));

  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      cin>>a[n-i+1][n-j+1];

  vector<vector<bool>> visit(n+1,vector<bool>(n+1));
  ans=n*n;

  if(a[1][1]!=0){
    if(a[1][1]==1 || a[1][1]==2){
      visit[1][1]=true;
      dfs(n,a,0,1,1,visit,1);
      visit[1][1]=false;
    }
    else{
      visit[1][1]=true;
      dfs(n,a,1,1,1,visit,1);
      visit[1][1]=false;
    }
  }

  cout<<ans<<"\n";
}
int main(){
  int T;
  cin>>T;
  for(int i=1;i<=T;i++){
    cout<<"#"<<i<<" ";
    solve();
  }
}