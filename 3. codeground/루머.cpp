#include <bits/stdc++.h>
using namespace std;

int oo=987654321;

void getLefRig(vector<int>& lef, vector<int>& rig, vector<int>& a, int n, int t){
  for(int i=1;i<=n;i++){
    for(int j=i;j>=1 && j>=i-t;j--){
      if(j!=i && a[j]==2) break;
      lef[i]=j;
    }
    for(int j=i;j<=n && j<=i+t;j++){
      if(j!=i && a[j]==2) break;
      rig[i]=j;
    }
  }
}

int canErase2(int k,int t,vector<int>& a, vector<int>& lef,vector<int>& rig){
  if(rig[k]<k+t && a[rig[k]+1]==2) return 1;
  return 0;
}

struct Value{
  int rig;
  int dpVal;
};

void solve(){
  int n;
  scanf("%d",&n);
  vector<int> a(n+5),lef(n+5),rig(n+5);
  vector<vector<int>> dp(n+5,vector<int>(n+5,-oo));
  vector<vector<Value>> maxDp(n+5);
  vector<int> s(n+5,-1);
  vector<int> mx(n+5,-oo);

  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  int s0,t;
  scanf("%d %d\n",&s0,&t);

  getLefRig(lef,rig,a,n,t);

  for(int i=1;i<=n;i++){
    dp[i][0]=0;
    
    for(int j=1;j<=s0 && j<=i;j++){
      if(j==1){
        dp[i][1]=rig[i]-lef[i]+1;
      }
      else{
        for(int k=1;k<i;k++){
          if(rig[k]+2<lef[i]){
            dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-lef[i]+1);
          }
          else if(rig[k]+2==lef[i]){
            dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-lef[i]+1+canErase2(k,t,a,lef,rig)*(lef[i]>i-t?1:0));
          }
          else{
            dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-rig[k]);
          }
        }
      }
    }
  }
  int ans=-oo;
  for(int i=1;i<=n;i++) ans=max(ans,dp[i][s0]);
  printf("%d\n",ans);
}
int main(){
  int t;
  setbuf(stdout, NULL);
  scanf("%d",&t);
  for(int i=1;i<=t;i++){
    printf("Case #%d\n",i);
    solve();
  }
}