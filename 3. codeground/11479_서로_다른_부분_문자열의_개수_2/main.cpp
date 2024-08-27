#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll MAX_VALUE_TO_HANDLE_ASCII = 300;
void countingSort(vector<ll> &suffixArray, vector<ll> &group, ll t){
  ll n=suffixArray.size();
  ll maxi=max(MAX_VALUE_TO_HANDLE_ASCII,n+1);
  vector<ll> c(maxi);
  for(ll i=0;i<n;i++) c[i+t<n?group[i+t]:0]++;
  for(ll i=1;i<maxi;i++) c[i]+=c[i-1];

  vector<ll> temp(n);
  for(ll i=n-1;i>=0;i--) temp[--c[suffixArray[i]+t<n?group[suffixArray[i]+t]:0]]=suffixArray[i];
  suffixArray=temp;
}

struct SortHelper {
  vector<ll> &group;
  ll t;
  SortHelper(vector<ll> &_group, ll _t):group(_group), t(_t){};
  bool operator () (ll indexA, ll indexB){
    if(group[indexA]!=group[indexB]) return group[indexA]<group[indexB];
    return group[indexA+t]<group[indexB+t];
  }
};

void print(vector<ll> SA){
  for(auto num:SA){
    printf("%lld ",num);
  }
  printf("\n");
}
vector<ll> getSA(string s){
  ll n=s.size();
  vector<ll> group(n+1);
  vector<ll> SA(n);
  for(ll i=0;i<n;i++) group[i]=s[i],SA[i]=i;
  ll t=1;
  group[n]=0;
  while(t<n){

    SortHelper cmp(group,t);
    //countingSort(SA,group,t); countingSort(SA,group,0);
    sort(SA.begin(),SA.end());
    t*=2;
    if(t>=n) break;

    vector<ll> newGroup(n+1);
    newGroup[SA[0]]=1;
    newGroup[n]=0;

    for(ll i=1;i<n;i++){
      if(cmp(SA[i-1],SA[i])){
        newGroup[SA[i]]=newGroup[SA[i-1]]+1;
      }
      else
        newGroup[SA[i]]=newGroup[SA[i-1]];
    }

    group=newGroup;
  }
  return SA;
}

vector<ll> getLCP(vector<ll> &SA,string s){
  ll n=SA.size();
  vector<ll> iSA(n),LCP(n);
  for(ll i=0;i<n;i++) iSA[SA[i]]=i;

  for(ll i=0,L=0;i<n;i++){
    if(iSA[i]==0) continue;
    while(i+L<n && SA[iSA[i]-1]+L<n && s[i+L]==s[SA[iSA[i]-1]+L])L++;
    LCP[iSA[i]]=L;
   // printf("L:%lld\n",L);
    L=max(L-1,0LL);
  }

  return LCP;
}

int main(){
  freopen("input.txt","r",stdin);
  string s;
  cin>>s;
  auto SA=getSA(s);
  auto LCP=getLCP(SA,s);
  ll n=s.size();
  ll ans=n*(n+1)/2;

  for(auto num:LCP){
    //printf("%lld ",num);
    ans-=num;
  }
  printf("%lld",ans);
}
