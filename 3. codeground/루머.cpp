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

  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  int s0,t;
  scanf("%d %d\n",&s0,&t);

  getLefRig(lef,rig,a,n,t);

  vector<int> s(n+5,-1),mxDp(n+5,-oo);
  vector<int> s2(n+5,-1),mxDp2(n+5,-oo);

  for(int i=1;i<=n;i++){
    dp[i][0]=0;
    
    for(int j=1;j<=s0 && j<=i;j++){
      if(j==1){
        dp[i][1]=rig[i]-lef[i]+1;
      }
      else{
        while(s[j]+1<i && rig[s[j]+1]+2<=lef[i]){
          s[j]++;
          mxDp[j]=max(mxDp[j],dp[s[j]][j-1]);
        }

        while(s2[j]+1<i && rig[s2[j]+1]+2<lef[i]){
          s2[j]++;
          mxDp2[j]=-oo;
        }
        while(s2[j]+1<i && rig[s2[j]+1]+2==lef[i]){
          s2[j]++;
          if(canErase2(s2[j],t,a,lef,rig))
            mxDp2[j]=max(mxDp2[j],dp[s2[j]][j-1]+1);
        }
        for(int k=1;k<i;k++){
          // if(rig[k]+2<lef[i]){
          //   dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-lef[i]+1);
          // }
          // else if(rig[k]+2==lef[i]){
          //   dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-lef[i]+1+canErase2(k,t,a,lef,rig)*(lef[i]>i-t?1:0));
          // }
          if(rig[k]+2>lef[i]){
            dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-rig[k]);
          }
        }
      }
      dp[i][j]=max(dp[i][j],mxDp[j]+rig[i]-lef[i]+1);
      if(lef[i]>i-t) dp[i][j]=max(dp[i][j],mxDp2[j]+rig[i]-lef[i]+1);
      //printf("%d %d %d-> %d/%d %d/%d\n",i,j,dp[i][j],mxDp[j],s[j],mxDp2[j],s2[j]);
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