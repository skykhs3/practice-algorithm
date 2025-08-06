#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll oo=99999999999LL;
ll sparseGaroTableMin[300][10][300];
ll sparseGaroTableMax[300][10][300];
ll sparseSeroTableMin[300][10][300];
ll sparseSeroTableMax[300][10][300];
ll n;
struct minMax{
  ll min,max;
};

long long highestPowerOf2(long long n) {
    if (n <= 0) return 0; // There is an assumption that n is positive, but additional safeguards
    return 1LL << (63 - __builtin_clzll(n));
}

minMax getValueGaro(ll index, ll s,ll e){
  ll t=__builtin_ctzll(highestPowerOf2(e-s+1));
  return {min(sparseGaroTableMin[index][t][s],sparseGaroTableMin[index][t][e-(1LL<<t)+1]),max(sparseGaroTableMax[index][t][s],sparseGaroTableMax[index][t][e-(1LL<<t)+1])};
}

minMax getValueSero(ll index, ll s,ll e){
  ll t=__builtin_ctzll(highestPowerOf2(e-s+1));
  return {min(sparseSeroTableMin[index][t][s],sparseSeroTableMin[index][t][e-(1LL<<t)+1]),max(sparseSeroTableMax[index][t][s],sparseSeroTableMax[index][t][e-(1LL<<t)+1])};
}

void buildSparseTables(vector<vector<ll>> &a){
  for(ll i=1;i<=n;i++)
    for(ll k=0,t=1;t<=n;t*=2,k++)
      for(ll j=1;j+t-1<=n;j++)
        if(k==0) sparseGaroTableMin[i][k][j]=sparseGaroTableMax[i][k][j]=a[i][j];
        else{
          sparseGaroTableMin[i][k][j]=min(sparseGaroTableMin[i][k-1][j],sparseGaroTableMin[i][k-1][j+t/2]);
          sparseGaroTableMax[i][k][j]=max(sparseGaroTableMax[i][k-1][j],sparseGaroTableMax[i][k-1][j+t/2]);
        }

  for(ll j=1;j<=n;j++)
    for(ll k=0,t=1;t<=n;t*=2,k++)
      for(ll i=1;i+t-1<=n;i++)
        if(k==0) sparseSeroTableMin[j][k][i]=sparseSeroTableMax[j][k][i]=a[i][j];
        else{
          sparseSeroTableMin[j][k][i]=min(sparseSeroTableMin[j][k-1][i],sparseSeroTableMin[j][k-1][i+t/2]);
          sparseSeroTableMax[j][k][i]=max(sparseSeroTableMax[j][k-1][i],sparseSeroTableMax[j][k-1][i+t/2]);
        }
}

ll mainProcess(ll startY,ll startX, vector<vector<ll>> &a){
  ll y1,y2,x1,x2;
  ll currentMax;
  ll ans=0;
  y1=y2=startY;
  x1=x2=startX;
  currentMax=a[startY][startX];
  while(1){
    if(currentMax-a[startY][startX]+1==(y2-y1+1)*(x2-x1+1)) ans++;

    ll mx=oo,dir=-1;
    if(y1>1){
      auto minMax=getValueGaro(y1-1,x1,x2);
      if(minMax.min>=a[startY][startX] && minMax.max<mx) mx=minMax.max, dir=3;
    }
    if(y2<n){
      auto minMax=getValueGaro(y2+1,x1,x2);
      if(minMax.min>=a[startY][startX] && minMax.max<mx) mx=minMax.max, dir=1;
    }
    if(x1>1){
      auto minMax=getValueSero(x1-1,y1,y2);
      if(minMax.min>=a[startY][startX] && minMax.max<mx) mx=minMax.max, dir=2;
    }
    if(x2<n){
      auto minMax=getValueSero(x2+1,y1,y2);
      if(minMax.min>=a[startY][startX] && minMax.max<mx) mx=minMax.max, dir=0;
    }
    
    if(dir==-1) break;

    currentMax=max(currentMax,mx);
    if(dir==0) x2++;
    if(dir==1) y2++;
    if(dir==2) x1--;
    if(dir==3) y1--;
  }
  return ans;
}

void solve(){
  scanf("%lld",&n);

  vector<vector<ll>> a(n+1,vector<ll>(n+1)), mn(n+1,vector<ll>(n+1)),mx(n+1,vector<ll>(n+1));
  for(ll i=1;i<=n;i++)
    for(ll j=1;j<=n;j++)
      scanf("%lld",&a[i][j]);

  buildSparseTables(a);
  
  //-----
  ll ans=0;
  for(ll i=1;i<=n;i++){
    for(ll j=1;j<=n;j++){
      ll temp=mainProcess(i,j,a);
      ans+=temp;
    }
  }

  cout<<ans;
}
int main(){
  ll T;
  cin>> T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
  return 0;
}