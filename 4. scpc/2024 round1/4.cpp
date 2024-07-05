#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
priority_queue<pair<ll,ll>> Q;
ll oo=9999999999L;
ll ans=-1;
void getValue(ll n,vector<ll> &A, vector<ll> &B, vector<ll> &stMLef, vector<ll> &stMRig, ll L, vector<ll> &rigM){
  ll lim =12;
  ll left=0,right =-1;
  //printf("--\n");

  while(!Q.empty()) Q.pop();
  while(true){
    ll mx=-oo;
    mx=max(mx,A[right+1]-B[left]);
    mx=max(mx,left-1<0 ? 0:stMLef[left-1]);
    mx=max(mx,right+2>=n ? 0:stMRig[right+2]);

    while(!Q.empty()){
      auto t=Q.top();
      if (t.second<left) Q.pop();
      else break;
    }
    if(Q.size()>=1){
      auto t=Q.top();
      mx=max(mx,t.first);
    }
 //printf("%lld %lld mx:%lld L:%lld, n:%lld\n",left,right,mx,L,n);
    if(mx>L){ // 실패
      left++;
      if(left>right+1) break;
    } else{ // 성공
   // printf("성공\n");
      if(mx<=L && mx>ans) ans=mx;
      right++;
      if(right==n-1) break;

      Q.push({rigM[right],right});
    }
  }
}

void solve2(vector<ll> &A, vector<ll> &B, ll n,ll m){  

  vector<ll> stM(n);
  vector<ll> lefM(n);
  vector<ll> rigM(n);
  vector<ll> stMLef(n);
  vector<ll> stMRig(n);
  for(ll i=0;i<n;i++){
    stM[i]=abs(A[i]-B[i]);
    if(i>=1) lefM[i]= abs(A[i]-B[i-1]);
    if(i<n-1) rigM[i]=abs(A[i]-B[i+1]);
  }


  stMLef[0]=stM[0];
  for(ll i=1;i<n;i++) stMLef[i]=max(stMLef[i-1],stM[i]);
  stMRig[n-1]=stM[n-1];
  for(ll i=n-2;i>=0;i--) stMRig[i]=max(stMRig[i+1],stM[i]);
  getValue(n,A,B,stMLef,stMRig,m,rigM);

}
void solve(){
  ll n,m;
  scanf("%lld %lld",&n,&m);
  vector<ll> A(n);
  vector<ll> B(n);

  for(ll i=0;i<n;i++) scanf("%lld ",&A[i]);
  for(ll i=0;i<n;i++) scanf("%lld",&B[i]);
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());

  ans=-1;

  solve2(A,B,n,m);
  solve2(B,A,n,m);
  printf("%lld\n",ans);
}
int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
}