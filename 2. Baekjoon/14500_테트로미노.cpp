#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[501][501];
bool vis[501][501];
int dy[4]={0,1,0,-1},dx[4]={1,0,-1,0};
int dfs(int y,int x,int lev,int sum){
  if(lev>=4) return sum;
  int ans=0;
  for(int i=0;i<4;i++){
    int ty=y+dy[i];
    int tx=x+dx[i];
    if(1<=ty && ty<=n && 1<=tx && tx<=m && vis[ty][tx]==false){
      vis[ty][tx]=true;
      ans=max(ans,dfs(ty,tx,lev+1,sum+a[ty][tx]));
      vis[ty][tx]=false;
    }
  }
  return ans;
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      scanf("%d",&a[i][j]);
  int ans=0;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
      vis[i][j]=true;
      ans=max(ans,dfs(i,j,1,a[i][j]));
      vis[i][j]=false;

      vector<int> s;
      for(int k=0;k<4;k++){
        int ty=i+dy[k],tx=j+dx[k];
        if(1<=ty && ty<=n && 1<=tx && tx<=m) s.push_back(a[ty][tx]);
      }
      sort(s.begin(),s.end());
      if(s.size()>=3){
        int sum=s[s.size()-1]+s[s.size()-2]+s[s.size()-3]+a[i][j];
        ans=max(ans,sum);
      }
    }
  printf("%d",ans);
  return 0;
}