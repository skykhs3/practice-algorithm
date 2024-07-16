// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// string s;
// ll power3[200001];
// ll MOD=524287;
// ll prime=2;
// bool check(ll sz){
//   ll sum=0;
//   vector<vector<ll>> memo(MOD); 
//   for(ll i=0;i<sz;i++){
//     sum=sum*prime+s[i];
//     sum=(sum%MOD+MOD)%MOD;
//   }
//   memo[sum].push_back(0);

//   for(ll i=sz;i<s.size();i++){
//     sum=(sum-power3[sz-1]*s[i-sz])*prime+s[i];
//     sum=(sum%MOD+MOD)%MOD;

//     for(auto start:memo[sum]){
//       ll flag=0;
//       for(ll j=start,k=i-sz+1;j<start+sz;j++,k++){
//         if(s[j]!=s[k]){
//           flag=1;
//           break;
//         }
//       }
//       if(flag==0) return true;
//     }
//     memo[sum].push_back(i-sz+1);
//   }
//   return false;
// }
// int main(){
//   ll n;
//   cin>>n;
//   cin>>s;
//   power3[0]=1;
//   for(ll i=1;i<=200000;i++) power3[i]=power3[i-1]*prime%MOD;

//   ll lef=1,rig=s.size()-1;
//   while(lef<=rig){
//     ll mid=(lef+rig)/2;
//     bool result=check(mid);
//     if(result) lef=mid+1;
//     else rig=mid-1;
//   }
//   printf("%lld",lef-1);
// }
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ll power3[200001];
ll MOD=524287;
ll prime=2;
bool check(ll sz){
  ll sum=0;
  multimap<ll,ll> mp;
  for(ll i=0;i<sz;i++){
    sum=sum*prime+s[i];
    sum=(sum%MOD+MOD)%MOD;
  }
  mp.insert({sum,0});

  for(ll i=sz;i<s.size();i++){
    sum=(sum-power3[sz-1]*s[i-sz])*prime+s[i];
    sum=(sum%MOD+MOD)%MOD;

    auto range=mp.equal_range(sum);
    for(auto it= range.first;it!=range.second;it++){
      ll flag=0;
      for(ll j=it->second,k=i-sz+1;j<it->second+sz;j++,k++){
        if(s[j]!=s[k]){
          flag=1;
          break;
        }
      }
      if(flag==0) return true;
    }
    mp.insert({sum,i-sz+1});
  }
  return false;
}
int main(){
  ll n;
  cin>>n;
  cin>>s;
  power3[0]=1;
  for(ll i=1;i<=200000;i++) power3[i]=power3[i-1]*prime%MOD;

  ll lef=1,rig=s.size()-1;
  while(lef<=rig){
    ll mid=(lef+rig)/2;
    bool result=check(mid);
    if(result) lef=mid+1;
    else rig=mid-1;
  }
  printf("%lld",lef-1);
}