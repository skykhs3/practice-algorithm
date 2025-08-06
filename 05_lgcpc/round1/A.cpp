#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string solve(string &S,ll lef,ll rig){
  if(lef>rig) return "";

  bool flag=false;
  for(ll i=lef;i<=rig;i++){
    if(!('0'<=S[i] && S[i]<='9')) flag=true;
  }
  if(flag==false){
    string tmp="";
    for(ll i=lef;i<=rig;i++) tmp+=S[i];
    return tmp;
  }

  string lefTmp="";
  for(ll i=lef;i<=rig;i++){
    if(S[i]=='('){
      ll sum=0;
      for(ll j=lef;j<S.size();j++){
        if(S[j]=='(') sum++;
        else if(S[j]==')'){
          sum--;
          if(sum==0){
            lefTmp+="(";
            lefTmp+=solve(S,i+1,j-1);
            lefTmp+=")";
            i=j;
            break;
          }
        }
      }
    }

   else if('0'<=S[i] && S[i]<='9'){
      ll j=i;
      for(j=i;j<=rig;j++){
        if('0'<=S[j] && S[j]<='9') lefTmp+=S[j];
        else break;
      }
      i=j-1;
    }

    else if(S[i]=='*'){
      lefTmp+='*';
    }

    else if(S[i]=='+'){
      return "("+lefTmp+")"+"+"+"("+solve(S,i+1,rig)+")";
    }
  }
  return lefTmp;
}
int main(){
  ll N,P;
  string S;
  cin>>N>>P;
  cin>>S;
  string ans=solve(S,0,N-1);
  cout<<ans.size()<<endl;
  cout<<ans;
}