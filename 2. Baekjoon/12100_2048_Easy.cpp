#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dy[4]={0,1,0,-1},dx[4]={1,0,-1,0};
void process(int dir, int n, int i,int j,vector<vector<ll>> &a,vector<vector<bool>> &check){
  int yy=i,xx=j;
  while(1){
    int ty=yy+dy[dir];
    int tx=xx+dx[dir];
    if(!(0<=ty && ty<n && 0<=tx && tx<n)){
      int temp=a[i][j];
      a[i][j]=0;
      a[yy][xx]=temp;
      break;
    }
    if(a[ty][tx]!=0){
      int temp=a[i][j];
      a[i][j]=0;
      
      if(a[ty][tx]==temp && check[ty][tx]==false){
        a[ty][tx]*=2;
        check[ty][tx]=true;
      } else{
        a[yy][xx]=temp;
      }
      break;
    }
    yy=ty;
    xx=tx;
  }
}
void move(int dir, int n,vector<vector<ll>> &a){
  vector<vector<bool>> check(n,vector<bool>(n));
  if(dir==0){
    for(int j=n-1;j>=0;j--)
      for(int i=0;i<n;i++)
        process(dir,n,i,j,a,check);
  }
  else if(dir==1){
    for(int i=n-1;i>=0;i--)
      for(int j=0;j<n;j++)
        process(dir,n,i,j,a,check);
  }
  else if(dir==2){
    for(int j=0;j<n;j++)
      for(int i=0;i<n;i++)
        process(dir,n,i,j,a,check);
  }
  else{
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        process(dir,n,i,j,a,check);
  }

}
ll print(int n,vector<vector<ll>> &a){
  ll ans=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      ans=max(ans,a[i][j]);
  }
  return ans;
}
int main(){
  int n;
  scanf("%d",&n);
  vector<vector<ll>> a(n,vector<ll>(n));
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      scanf("%lld",&a[i][j]);
  ll ans=0;
  for(int i1=0;i1<4;i1++){
    for(int i2=0;i2<4;i2++)
      for(int i3=0;i3<4;i3++)
        for(int i4=0;i4<4;i4++)
          for(int i5=0;i5<5;i5++){
            auto b=a;
            move(i1,n,b);
            move(i2,n,b);
            move(i3,n,b);
            move(i4,n,b);
            move(i5,n,b);
            ans=max(ans,print(n,b));
          }
  }
  printf("%lld",ans);
  return 0;
}