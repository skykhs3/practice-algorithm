#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll getS(ll n,ll i,string &s){
  if('0'<=s[i%n] && s[i%n]<='9') return s[i%n]-'0';
  else return s[i%n]-'A'+10;
}
void solve(){
  ll n,m;
  string s;
  cin>>n>>m;
  cin>>s;
  vector<ll> ans;
  for(ll i=0;i<n/4;i++){
    ll ans1=0,ans2=0,ans3=0,ans4=0;
    for(ll j=i;j<i+(n/4);j++){
      ans1=ans1*16+getS(n,j,s);
      ans2=ans2*16+getS(n,j+(n/4),s);
      ans3=ans3*16+getS(n,j+(n/4)*2,s);
      ans4=ans4*16+getS(n,j+(n/4)*3,s);
    }

    ans.push_back(ans1);
    ans.push_back(ans2);
    ans.push_back(ans3);
    ans.push_back(ans4);
  }
  sort(ans.begin(),ans.end());
  ans.resize(unique(ans.begin(),ans.end())-ans.begin());
  cout<<ans[ans.size()-m]<<endl;
}
int main(){
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"#"<<i<<" ";    solve();
  }
}