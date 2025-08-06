#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll oo=1000000005;
struct Ans{
  ll op,i,j;
};

void process(ll n, ll mnL,ll mnR,ll mxL,ll mxR, ll mid, vector<ll> &a){
  ll mx=a[mxL];
  ll mn=a[mnL];
  printf("2\n");
  if(mnR<=mid && mxR<=mid){
    if(mnR<mxR){
      printf("2 %lld %lld\n",mxR,n);
      printf("1 %lld %lld\n",1,mid);
    }
    else{
      printf("1 %lld %lld\n",mnR,n);
      printf("2 %lld %lld\n",1,mid);
    }
  }
  else if(mnL>mid && mxL>mid){
    if(mnL<mxL){
      printf("1 %lld %lld\n",1,mnL);
      printf("2 %lld %lld\n",mid+1,n);
    }
    else{
      printf("2 %lld %lld\n",1,mxL);
      printf("1 %lld %lld\n",mid+1,n);
    }
  } else if(mxR<=mid){
    printf("2 %lld %lld\n",1,mid);
    printf("1 %lld %lld\n",mid+1,n);
  } else if(mnR<=mid){
    printf("1 %lld %lld\n",1,mid);
    printf("2 %lld %lld\n",mid+1,n);
  } else if(mnL>mid){
    printf("2 %lld %lld\n",1,mid);
    printf("1 %lld %lld\n",mid+1,n);
  } else if(mxL>mid){
    printf("1 %lld %lld\n",1,mid);
    printf("2 %lld %lld\n",mid+1,n);
  } else{
    printf("1 %lld %lld\n",1,mid);
    printf("2 %lld %lld\n",mid+1,n);
  }
}

void two(ll n, vector<ll> &a,ll mn,ll mx){
  ll mnR,mxR,mnL,mxL;
  for(ll i=1;i<=n;i++){
    if(a[i]==mn) mnR=i;
    if(a[i]==mx) mxR=i;
  }
  for(ll i=n;i>=1;i--){
    if(a[i]==mn) mnL=i;
    if(a[i]==mx) mxL=i;
  }
  process(n,mnL,mnR,mxL,mxR,n/2,a);
}

bool isValidate(ll n,ll a,ll b){
  if(n%2==0 && a==n/2 &&b==n/2) return true;
  if(n%2==1){
    ll mid=n/2;
    if(a==mid && b==mid+1) return true;
    if(a==mid+1 && b==mid) return true;
  }
  return false;
}

bool wh(ll n, vector<ll>& sumL,vector<ll>& sumR, ll l,ll r,ll pr){
  while(1){
    ll hap=sumL[l-1]+sumR[r+1]+r-l+1;
    if(isValidate(n,hap,n-hap)){
      printf("1\n%lld %lld %lld\n",pr,l,r);
      return true;
    }
    if(l>1) l--;
    else if(r<n) r++;
    else{
      break;
    }
  }
  return false;
}

bool one(ll n, vector<ll> &a, vector<ll>&mnSumL,vector<ll>&mnSumR,vector<ll>&mxSumL,vector<ll>&mxSumR,ll l,ll r,ll mn,ll mx){
  if(l==-1){ // 내부에 아무것도 없는 경우.
    bool flag1=false,flag2=false;
    
    for(ll i=1;i<=n;i++){
      if(a[i]==mn && flag1==false){
        if(wh(n, mnSumL,mnSumR, i,i,1)) return true;
        flag1=true;
      }
      if(a[i]==mx && flag2==false){
        if(wh(n,mxSumL,mxSumR,i,i,2)) return true;
        flag2=true;
      }
    }
  }
  else{ // 내부에 mn,mx 아님 값 둘 중 뭐라도 있는 경우.
    bool flag1=false,flag2=false;
    for(ll i=l;i<=r;i++){
      if(a[i]==mn) flag1=true;
      if(a[i]==mx) flag2=true;
    }
    if(flag1==true){
      if(wh(n,mnSumL,mnSumR,l,r,1)) return true;
    }

    if(flag1==false){
      
      ll otherL=-1;
      for(ll i=l-1;i>=1;i--)
        if(a[i]==mn){
          otherL=i;
          break;
        }
      
      if(otherL!=-1 && wh(n,mnSumL,mnSumR,otherL,r,1)) return true;

      otherL=-1;
      for(ll i=r+1;i<=n;i++)
        if(a[i]==mn){
          otherL=i; break;
        }

      if(otherL!=-1 && wh(n,mnSumL,mnSumR,l,otherL,1)) return true;
    }
 
    if(flag2==true){
      if(wh(n,mxSumL,mxSumR,l,r,2)) return true;
    }

    if(flag2==false){
      ll otherL=-1;
      for(ll i=l-1;i>=1;i--)
        if(a[i]==mx){
          otherL=i;
          break;
        }
      if(otherL!=-1 && wh(n,mxSumL,mxSumR,otherL,r,2)) return true;

      otherL=-1;
      for(ll i=r+1;i<=n;i++){
        if(a[i]==mx){
          otherL=i;
          break;
        }
      }
      if(otherL!=-1 && wh(n,mxSumL,mxSumR,l,otherL,2)) return true;
    }
  }

  return false;
}

void solve(){
  ll n;
  scanf("%lld",&n);
  vector<ll> a(n+1);
  for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);

  //전처리
  ll mx=-oo,mn=oo;
  vector<ll> mnSumL(n+2),mnSumR(n+2),mxSumL(n+2),mxSumR(n+2);
  for(ll i=1;i<=n;i++){
    if(mx<a[i]) mx=a[i];
    if(mn>a[i]) mn=a[i];
  }

  ll l=-1,r=-1;
  
  for(ll i=1;i<=n;i++){
    if(a[i]!=mx && a[i]!=mn) r=i;
    mnSumL[i]=mnSumL[i-1]+(a[i]==mn?1:0);
    mxSumL[i]=mxSumL[i-1]+(a[i]==mx?1:0);
  }
  
  for(ll i=n;i>=1;i--){
    if(a[i]!=mx && a[i]!=mn) l=i;
    mnSumR[i]=mnSumR[i+1]+(a[i]==mn?1:0);
    mxSumR[i]=mxSumR[i+1]+(a[i]==mx?1:0);
  }

  if(mn==mx || isValidate(n,mnSumL[n],mxSumL[n])){
    printf("0\n");
    return;
  }

  if(one(n,a,mnSumL,mnSumR,mxSumL,mxSumR,l,r,mn,mx)){
    return;
  }
  two(n,a,mn,mx);
}

int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
    fflush(stdout);
  }
}