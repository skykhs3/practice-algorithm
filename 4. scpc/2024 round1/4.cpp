#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
priority_queue<pair<ll,ll>> Q;
ll oo=9999999999L;
ll ans=-1;
void twoPointer(ll n,vector<ll> &A, vector<ll> &B, vector<ll> &maxStFromLef, vector<ll> &maxStFromRig, ll L, vector<ll> &rigM){
  ll left=0,right =-1;
  while(!Q.empty()) Q.pop();

  while(true){
    ll maxF=-oo;
    maxF=max(maxF,A[right+1]-B[left]);
    maxF=max(maxF,left-1<0 ? 0:maxStFromLef[left-1]);
    maxF=max(maxF,right+2>=n ? 0:maxStFromRig[right+2]);

    while(!Q.empty()){
      auto t=Q.top();
      if (t.second<left) Q.pop();
      else break;
    }

    if(!Q.empty()){
      auto t=Q.top();
      maxF=max(maxF,t.first);
    }

    if(maxF>L){
      left++;
      if(left>right+1) break;
    } else{
      if(maxF > ans) ans=maxF;
      right++;
      if(right==n-1) break;

      Q.push({rigM[right],right});
    }
  }
}

void preProcessing(vector<ll> &A, vector<ll> &B, ll n,ll m){  
  vector<ll> stM(n); // |a_i-b_i|
  vector<ll> lefM(n); // |a_i-b_(i-1)|
  vector<ll> rigM(n); // |a_i-b_(i+1)| 
  vector<ll> maxStFromLef(n);
  vector<ll> maxStFromRig(n);
  
  for(ll i=0;i<n;i++){
    stM[i]=abs(A[i]-B[i]);
    if(i>=1) lefM[i]=abs(A[i]-B[i-1]);
    if(i<n-1) rigM[i]=abs(A[i]-B[i+1]);
  }

  maxStFromLef[0]=stM[0];
  for(ll i=1;i<n;i++) maxStFromLef[i]=max(maxStFromLef[i-1],stM[i]);
  maxStFromRig[n-1]=stM[n-1];

  for(ll i=n-2;i>=0;i--) maxStFromRig[i]=max(maxStFromRig[i+1],stM[i]);

  twoPointer(n,A,B,maxStFromLef,maxStFromRig,m,rigM);
}

void solution(){
  ll n,m;
  scanf("%lld %lld",&n,&m);
  vector<ll> A(n);
  vector<ll> B(n);

  for(ll i=0;i<n;i++) scanf("%lld ",&A[i]);
  for(ll i=0;i<n;i++) scanf("%lld",&B[i]);
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());

  ans=-1;

  preProcessing(A,B,n,m);
  preProcessing(B,A,n,m);
  printf("%lld\n",ans);
}

int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solution();
  }
}