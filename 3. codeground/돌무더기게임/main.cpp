#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f(ll s,ll e,vector<ll> &a,vector<vector<ll>> &left,vector<vector<ll>> &right,ll x){
  return min(left[s][x],right[x][e]);
}

ll oo=1000000000000000LL;

ll solve(){
  ll n;
  scanf("%lld",&n);
  vector<ll> a(n+2);
  vector<vector<ll>> dp(n+2,vector<ll>(n+2));
  vector<vector<ll>> left(n+2,vector<ll>(n+2,oo));
  vector<vector<ll>> right(n+2,vector<ll>(n+2,oo));
  vector<vector<ll>> memo(n+2,vector<ll>(n+2));
  for(ll i=1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  for(ll i=1;i<=n;i++){
    dp[i][i]=a[i];
    left[i][i]=a[i];
    right[i][i]=a[i];
    left[i][i+1]=dp[i][i]+a[i+1];
    right[i-1][i]=dp[i][i]+a[i-1];
  }

  for(ll gap=2;gap<=n;gap++){
    for(ll s=1;s+gap-1<=n;s++){
      ll e=s+gap-1;
      ll ans=0;
//      for(ll i=s;i<=e;i++){
//        if(ans<f(s,e,a,left,right,i)){
//           ans=f(s,e,a,left,right,i);
//           memo[s][e]=i;
//        }
//      }
//      printf("==>s: %lld e: %lld\n",s,e);
//      for(ll i=s;i<=e;i++){
//        printf("%lld ",left[s][i]);
//      }
//      printf("\n");
//      for(ll i=s;i<=e;i++){
//        printf("%lld ",right[i][e]);
//      }
//      printf("\n");

      for(ll k=s;k<=e;k++){
        ans=max(ans,min(left[s][k],right[k][e]));
      }
//      ll lef=s,rig=e;
//      while(lef<=rig){
//        ll mid=(lef+rig)/2;
//        if(left[s][mid]>=right[mid][e]) rig=mid-1;
//        else lef=mid+1;
//      }
//      ll k=max(s,min(e,rig+1));
//      ans=min(left[s][k],right[k][e]);
//
//      k=max(s,min(e,rig));
//      ans=max(ans,min(left[s][k],right[k][e]));
//
//      k=max(s,min(e,rig-1));
//      ans=max(ans,min(left[s][k],right[k][e]));

     // printf("s:%lld e:%lld ans:%lld,rig: %lld",s,e,ans,rig);
      dp[s][e]=ans;
      left[s][e+1]=dp[s][e]+a[e+1];
      right[s-1][e]=dp[s][e]+a[s-1];
    }
  }

  return dp[1][n];
}

int main(){
  setbuf(stdout, NULL);
  freopen("input.txt","r",stdin);
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    printf("%lld\n",solve());
  }
  return 0;
}
