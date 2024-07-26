#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll getCntLeft(ll index, vector<ll> &cntLeftA){
  if(index<0) return 0;
  return cntLeftA[index];
}
ll getCntRight(ll index,bool type, vector<ll> &cntRightA, vector<ll> &cntRightB){
  if(index>=cntRightA.size()) return 0;
  else if(type) return cntRightA[index];
  else return cntRightB[index];
}

vector<ll> getPartialMatch(string &s){
  int M=(ll)s.size(),matched=0;
  vector<ll> pi(M,0);
  for(ll i=1;i<s.size();i++){
    while(matched>0 && s[matched]!=s[i]) matched=pi[matched-1];
    if(s[matched]==s[i]){
      ++matched;
      pi[i]=matched;
    }
  }
  return pi;
}

void solve(){
  ll n,m;
  string x,y;

  cin>> n >> m>> x>>y;
  vector<ll> cntLeftA(n);
  vector<ll> cntRightA(n);
  vector<ll> cntRightB(n);

  // 전환
  if(y[0]=='b'){
    for(ll i=0;i<n;i++)
      if(x[i]=='a') x[i]='b';
      else x[i]='a';
    
    for(ll i=0;i<m;i++)
      if(y[i]=='a') y[i]='b';
      else y[i]='a';
  }

  // 전처리
  for(ll i=0;i<n;i++){
    cntLeftA[i]=(i>=1 ? cntLeftA[i-1]:0)+(x[i]=='a');
  }
  for(ll i=n-1;i>=0;i--){
    cntRightA[i]=(i<n-1 ? cntRightA[i+1]:0)+(x[i]=='a');
    cntRightB[i]=(i<n-1 ? cntRightB[i+1]:0)+(x[i]=='b');
  }


  //kmp 할 거 찾기
  string commonString="";
  ll s=m,e=m-1;
  for(ll i=1;i<m;i++){
    if(y[i]!=y[i-1]){ s=i; break;}
  }
  for(ll i=m-2;i>=0;i--){
    if(y[i]!=y[i+1]){ e=i; break;}
  }
  if(s<=e) commonString=y.substr(s,e-s+1);
  bool isType1= y[m-1]=='a';
  ll cntLeft=s;
  ll cntRight=m-1-e;
  if(commonString==""){
    for(ll i=0;i<=n;i++){
      ll a=getCntLeft(i-1,cntLeftA);
      ll b=getCntRight(i,isType1, cntRightA,cntRightB);

      if(a>=cntLeft && b>=cntRight){
        cout<<"YES";
        return;
      }
    }
  } else{
    string nst=commonString+"#"+x;
    auto pi=getPartialMatch(nst);

    for(ll i=commonString.size()+1;i<nst.size();i++){
      ll realIndex=i-(commonString.size()+1);
      if(pi[i]==commonString.size()){
        ll a=getCntLeft(realIndex-commonString.size(),cntLeftA);
        ll b=getCntRight(realIndex+1,isType1, cntRightA,cntRightB);
        
        if(a>=cntLeft && b>=cntRight){
          cout<<"YES";
          return;
        }
      }
    }
  }

  cout<<"NO";
}
int main(){
  ll T;
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(NULL);
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
}