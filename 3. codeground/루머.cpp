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

  vector<int> sInCase1(n+5,0),mxDpInCase1(n+5,-oo);
  vector<int> sInCase2(n+5,0),mxDpInCase2(n+5,-oo);

  for(int i=1;i<=n;i++){
    dp[i][0]=0;
    
    for(int j=1;j<=s0 && j<=i;j++){
      if(j==1){
        dp[i][1]=rig[i]-lef[i]+1;
      }
      else{
        while(sInCase1[j]+1<i && rig[sInCase1[j]+1]+2<=lef[i]){
          sInCase1[j]++;
          mxDpInCase1[j]=max(mxDpInCase1[j],dp[sInCase1[j]][j-1]);
        }

        while(sInCase2[j]+1<i && rig[sInCase2[j]+1]+2<lef[i]) sInCase2[j]++;
        if(sInCase2[j]==0 || rig[sInCase2[j]]+2!=lef[i]) mxDpInCase2[j]=-oo;
        while(sInCase2[j]+1<i && rig[sInCase2[j]+1]+2==lef[i]){
          sInCase2[j]++;
          if(canErase2(sInCase2[j],t,a,lef,rig))
            mxDpInCase2[j]=max(mxDpInCase2[j],dp[sInCase2[j]][j-1]+1);
        }

        for(int k=i-1;k>=1;k--){ // 최악이 O(n) 인데 통과하는 이유를 모르겠음.
          if(rig[k]+2>lef[i]) dp[i][j]=max(dp[i][j],dp[k][j-1]+rig[i]-rig[k]);
          else break;
        }

        dp[i][j]=max(dp[i][j],mxDpInCase1[j]+rig[i]-lef[i]+1);
        if(lef[i]>i-t) dp[i][j]=max(dp[i][j],mxDpInCase2[j]+rig[i]-lef[i]+1);
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