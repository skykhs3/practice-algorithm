#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Comparator{
  const vector<ll> &group;
  int t;
  Comparator(const vector<ll> &_group,ll _t): group(_group), t(_t){};
  bool operator ()(ll indexA, ll indexB){
    if(group[indexA]!=group[indexB]) return group[indexA]<group[indexB];
    else return group[indexA+t] < group[indexB+t];
  }
};

vector<ll> getSA(string s,int n){
  vector<ll> group(n+1);
  vector<ll> suffixArray(n);
  for(ll i=0;i<n;i++){
    group[i]=s[i], suffixArray[i]=i;
  }
  group[n]=-1;
  ll t=1;
  while(t<n){
    Comparator compareUsing2T(group,t);
    sort(suffixArray.begin(),suffixArray.end(),compareUsing2T);
    t*=2;
    if(t>=n) break;
    vector<ll> newGroup(n+1);
    newGroup[n]=-1;
    newGroup[suffixArray[0]]=0;
    for(ll i=1;i<n;i++){
      if(compareUsing2T(suffixArray[i-1],suffixArray[i]))
        newGroup[suffixArray[i]]=newGroup[suffixArray[i-1]]+1;
      else
        newGroup[suffixArray[i]]=newGroup[suffixArray[i-1]];
    }
    group=newGroup;
  }
  return suffixArray;
}

vector<ll> getLCP(string s,vector<ll> &suffixArray, ll n){
  vector<ll> iSA(n);
  vector<ll> LCP(n);

  for(ll i=0;i<n;i++) iSA[suffixArray[i]]=i;
  for(ll i=0,L=0;i<n;i++){
    if(iSA[i]==0) continue;

    while(i+L<n && suffixArray[iSA[i]-1]+L<n && s[i+L]==s[suffixArray[iSA[i]-1]+L]) L++;
    LCP[iSA[i]]=L;
    L=max(L-1,0LL);
  }
  return LCP;
}
int main(){
  freopen("input.txt","r",stdin);
  ll L;
  string s;
  cin>>L;
  cin>>s;
  auto SA=getSA(s,L);
  auto LCP=getLCP(s,SA,L);
  ll ans=0;
  for(ll i=0;i<LCP.size();i++){
    ans=max(ans,LCP[i]);
  }
  printf("%lld",ans);

}
